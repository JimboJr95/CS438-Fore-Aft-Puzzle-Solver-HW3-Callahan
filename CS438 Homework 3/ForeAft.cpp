//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.cpp
// Due Date:	22 February 2018
//
// Description:
//		This program is meant to solve a fore aft puzzle given a board size (example: https://www.cheesygames.com/foreaft/ )
//		It implements and A* search to solve. It may also use BFS and DFS, but these will only solve for small boards.
//

#include "stdafx.h"
#include "ForeAft.h"
#include "Heap.h"
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <list>

using namespace std;

// Constructor
ForeAft::ForeAft()
{
	nodesVisited = 0;
	expRowBlue = 0;
	expRowRed = 0;
	expColBlue = 0;
	expColRed = 0;
	solution = 0;
	open = new Heap();
}

// Destructor
ForeAft::~ForeAft()
{
	delete root;
	delete open;
}


// Utility functions
// Handles the execution of everything from this class
void ForeAft::run() {
	int inputI, quit = 4, boardSizeI, validNumFinal = 5;
	string inputS, boardSizeS;

	while (true)
	{
	begin:;
		cout << "Select a search method:\n";
		cout << "\t1. Best First Search\n";
		cout << "\t2. Breadth First Search (BFS)\n";
		cout << "\t3. Depth First Search (DFS)\n";
		cout << "\t4. Exit\n";
		cin >> inputS;
		
		// Validate that the entered value is an int
		try{
			inputI = stoi(inputS);
		}catch (exception e) {
			cout << "Please select a value from 1 to 4\n\n";
			goto begin;
		}

		if (!validNumber(inputI, 1, 4))
		{
			cout << "Please enter a valid number from 1 to 4\n";
			goto begin;
		}

		// If the user selects to quit
		if (inputI == quit)
			break;


	board:;
		// Get board size
		if (inputI == 1){
			cout << "Enter board size for A* (5 - 13): ";
			cin >> boardSizeS;
		}
		else if (inputI == 2){
			cout << "Enter board size for BFS (5): ";
			cin >> boardSizeS;
		}
		else if (inputI == 3) {
			cout << "Enter board size for DFS (5): ";
			cin >> boardSizeS;
		}

		// Validate that the entered value is an int
		try {
			boardSizeI = stoi(boardSizeS);
		}
		catch (exception e) {
			cout << "\nInvalid value, enter a valid board size\n\n";
			goto board;
		}

		// Set largest allowed value for the given algorithm
		if (inputI == 1)
			validNumFinal = 13;
		else if (inputI == 2)
			validNumFinal = 5;
		else if (inputI == 3)
			validNumFinal = 5;

		if (!validNumber(boardSizeI, 5, validNumFinal))
		{
			cout << "\nInvalid value, enter a valid board size\n\n";
			goto board;
		}

		// Make sure it is an odd number
		if (boardSizeI % 2 == 0)
			boardSize = boardSizeI - 1;
		else
			boardSize = boardSizeI;

		// Initialize the root node
		root = new node(boardSize);
		root->parent = NULL;
		root->f = 0;
		root->g = 0;
		root->h = 0;
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				if (i == boardSize / 2 && j == boardSize / 2) {
					root->arr[i][j] = blank;
					root->blankR = i;
					root->blankC = j;
				}
				else if ((i / (boardSize / 2 + 1)) == 0 && (j / (boardSize / 2 + 1)) == 0)
					root->arr[i][j] = red;
				else if ((i / (boardSize / 2)) >= 1 && (j / (boardSize / 2)) >= 1)
					root->arr[i][j] = blue;
			}
		}

		getNum(root);

		for (int i = boardSize - 1; i >= 0; i--)
			for (int j = boardSize - 1; j >= 0; j--)
				solution = solution * 3 + root->arr[i][j];

		// Perform selected search on selected size
		if (inputI == 1)
			AStar();
		else if (inputI == 2)
			BFS();
		else
			DFS();
		
		// Reset variables as needed
		nodesVisited = 0;
		solution = 0;
	}
}

void ForeAft::AStar() {
	bool moveable = false;
	ofstream out;
	current = root;
	startTimer();

	// If the root is the solution (should never happen)
	if (solutionFound(root))
		return;

	while (true) {
		if (makeMove(UP, aStar))
			break;
		if (makeMove(UP2, aStar))
			break;
		if (makeMove(DOWN, aStar))
			break;
		if (makeMove(DOWN2, aStar))
			break;
		if (makeMove(LEFT, aStar))
			break;
		if (makeMove(LEFT2, aStar))
			break;
		if (makeMove(RIGHT, aStar))
			break;
		if (makeMove(RIGHT2, aStar))
			break;

		open->sort();

		if (!open->isEmpty())
		{
			current = open->getFront();
			open->popFront();
			//printBoard(current);
			//cout << "current f (above): " << current->f << endl << endl;
		}
		else {
			std::cout << "Ran out of explorable nodes.\nNo solution found.\n";
			break;
		}
	}

	printSolutionToFile(out, "best" + to_string(boardSize) + ".out");
	endTimer();

	delete open;

	open = new Heap();
	found.clear();
}

// Uses Breadth First Search (only for 5x5 board)
void ForeAft::BFS() {
	bool moveable = false;
	ofstream out;
	current = root;
	startTimer();

	// If the root is the solution (should never happen)
	if (solutionFound(root))
		return;

	while (true) {
		if (makeMove(UP, bfs))
			break;
		if (makeMove(UP2, bfs))
			break;
		if (makeMove(DOWN, bfs))
			break;
		if (makeMove(DOWN2, bfs))
			break;
		if (makeMove(LEFT, bfs))
			break;
		if (makeMove(LEFT2, bfs))
			break;
		if (makeMove(RIGHT, bfs))
			break;
		if (makeMove(RIGHT2, bfs))
			break;

		if (!openList.empty())
		{
			current = openList.front();
			closedList.emplace_back(openList.front());
			openList.pop_front();
		}
		else {
			std::cout << "Ran out of explorable nodes.\nNo solution found.\n";
			break;
		}
	}

	printSolutionToFile(out, "bfs" + to_string(boardSize) + ".out");
	endTimer();
	found.clear();
	openList.clear();
	closedList.clear();
}

// Uses Depth First Search
void ForeAft::DFS() {
	bool moveable = false;
	ofstream out;
	current = root;
	startTimer();

	// If the root is the solution (should never happen)
	if (solutionFound(root))
		return;

	while (true) {
		if (makeMove(UP, dfs))
			break;
		if (makeMove(UP2, dfs))
			break;
		if (makeMove(DOWN, dfs))
			break;
		if (makeMove(DOWN2, dfs))
			break;
		if (makeMove(LEFT, dfs))
			break;
		if (makeMove(LEFT2, dfs))
			break;
		if (makeMove(RIGHT, dfs))
			break;
		if (makeMove(RIGHT2, dfs))
			break;

		if (!openList.empty())
		{
			current = openList.front();
			closedList.emplace_back(openList.front());
			openList.pop_front();
		}
		else {
			std::cout << "Ran out of explorable nodes.\nNo solution found.\n";
			break;
		}
	}

	printSolutionToFile(out, "dfs" + to_string(boardSize) + ".out");
	endTimer();
	found.clear();
	openList.clear();
	closedList.clear();
}

// This function takes a direction (typedef int, ForeAft.h) and depending on the direction passed in will try to make that move.
// Possible directions are listed in the ForeAft.h file (ex: UP, DOWN, etc.)
// It returns true if the solution has been found
bool ForeAft::makeMove(direction d, algorithm a) {
	node *n;
	bool moveable = false;
	n = new node(current, boardSize);
	n->parent = current;

	switch (d) {
	case UP:
		moveable = moveBlankUpOne(n);
		break;
	case UP2:
		moveable = moveBlankUpTwo(n);
		break;
	case DOWN:
		moveable = moveBlankDownOne(n);
		break;
	case DOWN2:
		moveable = moveBlankDownTwo(n);
		break;
	case LEFT:
		moveable = moveBlankLeftOne(n);
		break;
	case LEFT2:
		moveable = moveBlankLeftOne(n);
		break;
	case RIGHT:
		moveable = moveBlankRightOne(n);
		break;
	case RIGHT2:
		moveable = moveBlankRightOne(n);
		break;
	}

	// If there was a move to be made on the board
	if (moveable)
	{
		getNum(n); // get the number for the board and determine if it is unique
		if ( found.find(n->num) != found.end() )
			delete n;
		else {
			// Add the board to the found list if it is unique
			found.emplace(n->num);

			// If we found the solution
			if (solutionFound(n)) {
				current = n;
				return true;
			}
			else {
				switch (a)
				{
				case aStar:
					n->h = heuristic(n);
					n->g = n->parent->g++;
					n->f = n->g + n->h;
					open->add(n);
					break;
				case bfs:
					openList.emplace_back(n);
					break;
				case dfs:
					openList.emplace_front(n);
					break;
				default:
					break;
				}
				
			}
		}
	}
	else
		delete n;

	return false;
}


// This function calculates the h (heuristic) value for a given node
// It bases the value off of if the node is on its correct side or not and gives bonuses to the boards that have completed rows
// The row completion bonus is only given if each previous row has been filled with the porper color
float ForeAft::heuristic(node *n) {
	float tmp = 0, a;
	int t = 0, rcb = 0, rcr = 0, divB = 1, divR = 1;

	// This goes over the top half of the board and adds distances for the red values
	for (int i = 0; i <= boardSize/2; i++)
	{
		for (int j = 0; j <= boardSize/2; j++)
		{
			// If it is red
			if (n->arr[i][j] == red) {
				tmp += manhattanDistance(i, boardSize, j, boardSize);
			}
			else {
				rcb++;
			}
		}

		if (rcb == boardSize / 2 + 2) {
			divB++;
			rcb = 0;
		}
		else
			rcb = 99;
	}

	// This goes over the bottom half of the board and adds distances for the blue values
	for (int i = boardSize-1; i >= boardSize/2; i--)
	{
		for (int j = boardSize-1; j >= boardSize/2; j--)
		{
			if (i >= boardSize / 2 && j >= boardSize / 2)
			{
				// If it is blue
				if (n->arr[i][j] == blue) {
					tmp += manhattanDistance(i, 0, j, 0);
				}
				else {
					rcr++;
				}
			}
		}

		if (rcr == boardSize / 2 + 2) {
			divR++;
			rcr = 0;
		}
		else
			rcr = 99;
	}

	// This gets the heuristic value and then divides by two numbers
	a = tmp * C;
	a = a / divR; // # of red rows completed
	a = a / divB; // # of blue rows completed

	return a;
}

// Mantatten distance for heuristic calculation
int ForeAft::manhattanDistance(int row1, int row2, int col1, int col2) {
	return(abs(row1 - row2) + abs(col1 - col2));
}



/////// Functions for making moves in node 2d array ///////
bool ForeAft::moveBlankUpOne(node *n) {
	if (n->blankR - 1 >= 0 && n->arr[n->blankR - 1][n->blankC] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR - 1][n->blankC];
		n->arr[n->blankR - 1][n->blankC] = blank;
		--n->blankR;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankUpTwo(node *n) {
	if (n->blankR - 2 >= 0 && n->arr[n->blankR - 2][n->blankC] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR - 2][n->blankC];
		n->arr[n->blankR - 2][n->blankC] = blank;
		n->blankR -= 2;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankDownOne(node *n) {
	if (n->blankR + 1 < boardSize && n->arr[n->blankR + 1][n->blankC] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR + 1][n->blankC];
		n->arr[n->blankR + 1][n->blankC] = blank;
		++n->blankR;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankDownTwo(node *n) {
	if (n->blankR + 2 < boardSize && n->arr[n->blankR + 2][n->blankC] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR + 2][n->blankC];
		n->arr[n->blankR + 2][n->blankC] = blank;
		n->blankR += 2;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankLeftOne(node *n) {
	if (n->blankC - 1 >= 0 && n->arr[n->blankR][n->blankC - 1] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR][n->blankC - 1];
		n->arr[n->blankR][n->blankC - 1] = blank;
		--n->blankC;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankLeftTwo(node *n) {
	if (n->blankC - 2 >= 0 && n->arr[n->blankR][n->blankC - 2] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR][n->blankC - 2];
		n->arr[n->blankR][n->blankC - 2] = blank;
		n->blankC -= 2;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankRightOne(node *n) {
	if (n->blankC + 1 < boardSize && n->arr[n->blankR][n->blankC + 1] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR][n->blankC + 1];
		n->arr[n->blankR][n->blankC + 1] = blank;
		++n->blankC;
		return true;
	}

	return false;
}

bool ForeAft::moveBlankRightTwo(node *n) {
	if (n->blankC + 2 < boardSize && n->arr[n->blankR][n->blankC + 2] != invalid)
	{
		n->arr[n->blankR][n->blankC] = n->arr[n->blankR][n->blankC + 2];
		n->arr[n->blankR][n->blankC + 2] = blank;
		n->blankC += 2;
		return true;
	}

	return false;
}



/////// Variaous board utilities ///////

// Copy board from source to target
void ForeAft::copyNode(node *source, node *target) {
	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			target->arr[i][j] = source->arr[i][j];
	
	target->blankR = source->blankR;
	target->blankC = source->blankC;
}

// Checks to make sure the number input by the user is valid
bool ForeAft::validNumber(int num, int beginRange, int endRange) {
	if(num >= beginRange && num <= endRange)	
		return true;
	
	return false;
}

// Print board to the command line
void ForeAft::printBoard(node *n) {
	for (int i = 0; i < boardSize; i++){
		for (int j = 0; j < boardSize; j++) {

			if (n->arr[i][j] == invalid)
				cout << "# ";
			else if (n->arr[i][j] == blank)
				cout << "  ";
			else if (n->arr[i][j] == red)
				cout << "R ";
			else
				cout << "B ";
		}
		cout << endl;
	}
}

// Outputs the final solution to the console
void ForeAft::printSolutionToScreen() {
	while (current != NULL)
	{
		printBoard(current);
		std::cout << endl;
		current = current->parent;
	}
	std::cout << endl << "number of nodes created: " << open->getSize() + found.size() << endl;
}

// Outputs the final solution to a file given an output file stream and filename
void ForeAft::printSolutionToFile(ofstream &outfile, string filename) {
	// If the solution was found
	if (solutionFound(current)) {
		outfile.open(filename);
		list<node*> list;
		node *n;
		int count = 0;

		while (current != NULL)
		{
			list.emplace_front(current);
			current = current->parent;
		}

		while (!list.empty())
		{
			n = list.front();
			outfile << to_string(count) << ":\n";

			for (int i = 0; i < boardSize; i++)
			{
				for (int j = 0; j < boardSize; j++)
				{

					if (n->arr[i][j] == invalid)
						outfile << "#";
					else if (n->arr[i][j] == blank)
						outfile << " ";
					else if (n->arr[i][j] == red)
						outfile << "R";
					else
						outfile << "B";
				}
				outfile << endl;
			}
			outfile << endl << endl;
			list.pop_front();
			count++;
		}
		cout << "\nHeuristic search has a found a solution with " << to_string(count) << " steps.";
		cout << "\nSee " << filename << " for details.";
		cout << endl << "Total of " << open->getSize() + found.size() << " nodes generated.\n\n";

		outfile.close();
	}
}

void ForeAft::getBoardId(node *n) {
	// If the id hasn't been created yet
	if (n->id == "") {
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				n->id.append(to_string(n->arr[i][j]));
	}
}

// Returns if the solution has been found
bool ForeAft::solutionFound(node *n) {
	if (n->num == solution)
		return true;

	return false;
}

// Starts timer
void ForeAft::startTimer()
{
	timer = clock();
}

// Stops timer and outputs time
void ForeAft::endTimer()
{
	timer = clock() - timer;

	// Clock source: http://www.cplusplus.com/reference/ctime/clock/
	std::cout << "Time (s) to make calculations: " << ((float)timer) / CLOCKS_PER_SEC << endl << endl;
}

// From Dr. Yu's 8-Puzzle program, for determining duplicate boards
long ForeAft::getNum(node* n)
{
	long num = 0;

	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			num = num * 3 + n->arr[i][j];

	n->num = num;

	return num;
}