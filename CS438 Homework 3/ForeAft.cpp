//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.cpp
// Due Date:	15 February 2018
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
	open = new Heap();
	solution = 0;
//	closed = new Heap();
}

// Destructor
ForeAft::~ForeAft()
{
	delete root;
	delete open;
	//delete closed;
}


// Utility functions
// Handles the execution of everything from this class
void ForeAft::run() {
	int inputI, quit = 2, boardSizeI;
	string inputS, boardSizeS;

	while (true)
	{
	begin:;
		cout << "Select a search method:\n";
		cout << "\t1. Best First Search\n";
		cout << "\t2. Exit\n";
		cin >> inputS;
		
		// Validate that the entered value is an int
		try{
			inputI = stoi(inputS);
		}catch (exception e) {
			cout << "Please select a value from 1 to 2\n\n";
			goto begin;
		}

		if (!validNumber(inputI, 1, 2))
		{
			cout << "Please enter a valid number from 1 to 2\n";
			goto begin;
		}

		// If the user selects to quit
		if (inputI == quit)
			break;


	board:;
		// Get board size
		if (inputI == 1)
		{
			cout << "Enter board size for A* (5 - 13): ";
			cin >> boardSizeS;
		}

		// Validate that the entered value is an int
		try {
			boardSizeI = stoi(boardSizeS);
		}
		catch (exception e) {
			cout << "\nInvalid value, enter a valid board size (5-13)\n\n";
			goto board;
		}

		if (!validNumber(boardSizeI, 5, 13))
		{
			cout << "\nInvalid value, enter a valid board size (5-13)\n\n";
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
		getBoardId(root);
		getNum(root);

		// get solution string
		/*for (int i = boardSize-1; i >= 0; i--)
			for (int j = boardSize-1; j >= 0; j--)
				solution.append(to_string(root->arr[i][j]));*/

		for (int i = boardSize - 1; i >= 0; i--)
			for (int j = boardSize - 1; j >= 0; j--)
				solution = solution * 3 + root->arr[i][j];

//				num = num * 3 + n->arr[i][j];

		// Perform selected search on selected size

		//printBoard(root);
		AStar();
		//delete root;
		nodesVisited = 0;
		//solution = "";
		solution = 0;
	}
}

void ForeAft::AStar() {
	//node *n;
	bool moveable = false;
	current = root;
	ofstream out;

	startTimer();

	// If the root is the solution (should never happen)
	if (solutionFound(root))
		return;

	while (true) {
		/*n = new node(current, boardSize);
		n->partent = current;
		if (moveBlankUpOne(n))
		{
			n->h = heuristic(n);
			n->g = n->partent->g++;
		}
		else
			delete n;*/
		if (makeMove(UP))
			break;
		if (makeMove(UP2))
			break;
		if(makeMove(DOWN))
			break;
		if (makeMove(DOWN2))
			break;
		if (makeMove(LEFT))
			break;
		if (makeMove(LEFT2))
			break;
		if (makeMove(RIGHT))
			break;
		if (makeMove(RIGHT2))
			break;

		//open->sort();

		if (!open->isEmpty())
		{
			current = open->getFront();
			//found.emplace(current->id); ///////////////////////////// need to add sting to closed
			open->popFront();
			//closed->add(open->popFront());
			//printBoard(current);
			//cout << endl << "current f (above): " << current->f << endl;
		}
		else {
			std::cout << "Ran out of explorable nodes.\nNo solution found.\n";
			break;
		}
	}

	//printSolutionToScreen();
	printSolutionToFile(out, "best" + to_string(boardSize) + ".out");
	endTimer();

	delete open;
	//delete closed;

	open = new Heap();
	//closed = new Heap();
	found.clear();
}

void ForeAft::printSolutionToScreen() {
	while (current != NULL)
	{
		printBoard(current);
		std::cout << endl;
		current = current->parent;
	}
	std::cout << endl << "number of nodes created: " << open->getSize() + found.size() << endl;
}

void ForeAft::printSolutionToFile(ofstream &outfile, string filename) {
	outfile.open(filename);
	list<node*> list;
	node *n;

	while (current != NULL)
	{
		list.emplace_front(current);
		current = current->parent;
	}

	while (!list.empty())
	{
		n = list.front();

		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{

				if (n->arr[i][j] == invalid)
					outfile << "# ";
				else if (n->arr[i][j] == blank)
					outfile << "  ";
				else if (n->arr[i][j] == red)
					outfile << "R ";
				else
					outfile << "B ";
			}
			outfile << endl;
		}
		outfile << endl;
		list.pop_front();
	}

	cout << endl << "number of nodes created: " << open->getSize() + found.size() << endl;

	outfile.close();
}

bool ForeAft::makeMove(direction d) {
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
		//getBoardId(n);
		getNum(n);
		if ( found.find(n->num) != found.end() /*found.find(n->id) != found.end()*/ /*open->alreadyAdded(n) || closed->alreadyAdded(n)*/)
			delete n;
		else {
			//found.emplace(n->id);
			found.emplace(n->num);
			// If we found the solution
			if (solutionFound(n)) {
				current = n;
				return true;
			}
			else {
				n->h = heuristic(n);
				n->g = n->parent->g++;
				n->f = n->g + n->h;
				open->add(n);
				//printBoard(n);
				//cout << endl;
			}
		}
	}
	else
		delete n;

	return false;
}

/// another option would be to have the heuristic check how far a color is from the desired sides furthest corner and calc off of that
float ForeAft::heuristic(node *n) {
	float tmp = 0.0;
	int t = 0, rcb = 0, rcr = 0, divB = 1, divR = 1;

	for (int i = 0; i <= boardSize/2; i++)
	{
		for (int j = 0; j <= boardSize/2; j++)
		{
			// top half of the board
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




	//int tmp = 0;
	//int rowR = 0, rowB = 0, colR = 0, colB = 0, rc = 0, cc = 0, row = 0, col = 0;

	//for (int i = 0; i < boardSize / 2; i++)
	//{
	//	for (int j = 0; j < boardSize; j++)
	//	{
	//		if (n->arr[i][j] != invalid && n->arr[i][j] != blank)
	//		{
	//			//if (j == 0 || i == 0)
	//			//{
	//			//	if (n->arr[i][j] == blue) // greater value
	//			//		tmp += 1;
	//			//	else // lesser value
	//			//		tmp += 7;
	//			//} // end row and col == 0 check
	//			//else if (j == boardSize - 1 && i == boardSize - 1) {
	//			//	if (n->arr[i][j] == red)
	//			//		tmp += 1;
	//			//	else
	//			//		tmp += 7;
	//			//}
	//			//else if (i == 1 || j == 1) {
	//			//	if (n->arr[i][j] == blue)
	//			//		tmp += 2;
	//			//	else
	//			//		tmp += 6;
	//			//}
	//			//else if (i == boardSize-2 || j == boardSize-2) {
	//			//	if (n->arr[i][j] == red)
	//			//		tmp += 2;
	//			//	else
	//			//		tmp += 6;
	//			//}
	//			//else if (i == 2 || j == 2) {
	//			//	if (n->arr[i][j] == blue)
	//			//		tmp += 3;
	//			//	else
	//			//		tmp += 5;
	//			//}
	//			//else if (i == boardSize - 3 || j == boardSize - 3) {
	//			//	if (n->arr[i][j] == red)
	//			//		tmp += 3;
	//			//	else
	//			//		tmp += 5;
	//			//}

	//			// blue survival
	//			//if (i == 0 && j == 0 && n->arr[i][j] == blue)
	//			//	tmp += 0;
	//			//else if (i == 1 && j == 0 && n->arr[i][j] == blue)
	//			//	tmp += 0;
	//			//else if (i == 2 && j == 0 && n->arr[i][j] == blue)
	//			//	tmp += 0;
	//			//else if (i == 0 && j == 1 && n->arr[i][j] == blue)
	//			//	tmp += 0;
	//			//else if (i == 0 && j == 2 && n->arr[i][j] == blue)
	//			//	tmp += 0;
	//			//// red survival
	//			//else if (i == boardSize-1 && j == boardSize-1 && n->arr[i][j] == red)
	//			//	tmp += 0;
	//			//else if (i == boardSize-2 && j == boardSize-1 && n->arr[i][j] == red)
	//			//	tmp += 0;
	//			//else if (i == boardSize-3 && j == boardSize-1 && n->arr[i][j] == red)
	//			//	tmp += 0;
	//			//else if (i == boardSize-1 && j == boardSize-2 && n->arr[i][j] == red)
	//			//	tmp += 0;
	//			//else if (i == boardSize-1 && j == boardSize-3 && n->arr[i][j] == red)
	//			//	tmp += 0;
	//			//else if (i == boardSize-1 && j == boardSize-1 && n->arr[i][j] == red)
	//			//	tmp += 0;


	//			// could give rewards for completing whole row or column then keep stacking rewards
	//			if (/*i <= boardSize-4 &&*/ n->arr[i][j] == blue) {
	//				//tmp += 0;
	//				tmp += manhattanDistance(i, row, j, col);
	//				if (rc == i) {
	//					rowB++;
	//					col++;
	//				}
	//			}
	//			//else if (j <= boardSize-4 && n->arr[i][j] == blue) {
	//			//	tmp += 0;
	//			//	//if(cc == i)
	//			//	//colB++;
	//			//}
	//			/*else if (i >= boardSize - (boardSize-4) && n->arr[i][j] == red) {
	//				tmp += 0;
	//				if(rc == i)
	//					rowR++;
	//			}
	//			else if (j >= boardSize - (boardSize - 4) && n->arr[i][j] == red) {
	//				tmp += 0;
	//				colR++;
	//			}*/
	//			/*else if (n->arr[i][j] == blue && i <= boardSize/2  ) {
	//				tmp += 0;
	//			}
	//			else if (n->arr[i][j] == red && i > boardSize / 2 + 1) {
	//				tmp += 0;
	//			}*/
	//			// general survival
	//			/*else if (n->arr[i][j] == blue) {
	//				tmp += manhattanDistance(i, 0, j, 0);
	//			}*/
	//			/*else {
	//				tmp += manhattanDistance(i, boardSize - 1, j, boardSize - 1);
	//			}*/

	//			// red is being analyzed in the wrong order for booosts... -> fixed


	//		} // end check if not invalid and not blank
	//		// incrementing for each makes comparisons below easier
	//		else {
	//			//rowR++;
	//			//rowB++;
	//			//colR++;
	//			//colB++;
	//		}
	//	} // end for loop (j -> col)

	//	if (rowB == boardSize/2 + 1) {
	//		//tmp -= 1000;
	//		row++;
	//		col = 0;
	//		/*if (tmp - 1350 > 0)
	//			tmp -= 1350;
	//		else
	//			tmp = 0;*/
	//		//tmp = tmp / 2;
	//		rc++;
	//	}
	//	/*if (rowR == boardSize) {
	//		tmp -= 1350;
	//		rc++;
	//	}*/
	//	/*if (colR == boardSize) {
	//		tmp -= 1350;
	//		cc++;
	//	}
	//	if (colB == boardSize) {
	//		tmp -= 1350;
	//		cc++;
	//	}*/
	//	/*if (i == boardSize / 2 + 1)
	//		rc = i + 1;*/

	//	//rowR = 0;
	//	rowB = 0;
	//	//colR = 0;
	//	//colB = 0;
	//} // end for loop (i -> row)

	//rc = boardSize - 1;
	//row = boardSize - 1;
	//col = boardSize - 1;
	//int a = boardSize - 1, b = boardSize - 1;

	//for (int i = boardSize - 1; i >= 0 /*boardSize / 2*/; i--)
	//{
	//	for (int j = 0; j < boardSize; j++)
	//	{
	//		if (n->arr[i][j] != blank && n->arr[i][j] != invalid)
	//		{

	//			//if (i >= boardSize - (boardSize / 2) && n->arr[i][j] == red) {
	//			//	//tmp += 0;
	//			//	if (rc == i)
	//			//		rowR++;
	//			//}
	//			if (/*j >= boardSize - (boardSize / 2) &&*/ n->arr[i][j] == red) {
	//				tmp += manhattanDistance(i, row, j, col);
	//				if (rc == i) {
	//					rowR++;
	//					col--;
	//				}
	//				//tmp += 0;
	//				//colR++;
	//			}
	//			/*else if (n->arr[i][j] == blue) {
	//				tmp += manhattanDistance(i, 0, j, 0);
	//			}*/
	//			/*else {
	//				tmp += manhattanDistance(i, boardSize - 1, j, boardSize - 1);
	//			}*/
	//		}
	//		else {
	//			//rowR++;
	//		}

	//		/*if (col == boardSize / 2) {
	//			row--;
	//			col = boardSize - 1;
	//		}*/
	//	}

	//	if (rowR == boardSize / 2 + 1) {
	//		//tmp -= 1000;
	//		row--;
	//		col = boardSize - 1;
	//		/*if (tmp - 1350 > 0)
	//			tmp -= 1350;
	//		else
	//			tmp = 0;*/
	//		//tmp = tmp / 2;
	//		rc--;
	//	}

	//	rowR = 0;
	//}

	//int t = 0;
	//for (int i = 0; i < boardSize - 4; i++)
	//{
	//	for (int j = 0; j < boardSize; j++)
	//	{
	//		if (n->arr[i][j] == blue /*|| n->arr[i][j] == blank*/ || n->arr[i][j] == invalid)
	//			t++;
	//	}
	//	if (t == boardSize)
	//		tmp -= 20;
	//	t = 0;
	//}

	//for (int i = boardSize-1; i >= boardSize - 4; i--)
	//{
	//	for (int j = 0; j < boardSize; j++)
	//	{
	//		if (n->arr[i][j] == red /*|| n->arr[i][j] == blank*/ || n->arr[i][j] == invalid)
	//			t++;
	//	}
	//	if (t == boardSize)
	//		tmp -= 20;
	//	t = 0;
	//}

	//for (int i = 0; i < boardSize - 4; i++)
	//{
	//	for (int j = 0; j < boardSize; j++)
	//	{
	//		if (n->arr[j][i] == blue /*|| n->arr[i][j] == blank*/ || n->arr[i][j] == invalid)
	//			t++;
	//	}
	//	if (t == boardSize)
	//		tmp -= 20;
	//	t = 0;
	//}

	//for (int i = boardSize - 1; i >= boardSize - 4; i--)
	//{
	//	for (int j = 0; j < boardSize; j++)
	//	{
	//		if (n->arr[j][i] == red /*|| n->arr[i][j] == blank*/ || n->arr[i][j] == invalid)
	//			t++;
	//	}
	//	if (t == boardSize)
	//		tmp -= 20;
	//	t = 0;
	//}

	float a = tmp * C;
	a = a / divR;
	a = a / divB;

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
	/*for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			if (i == boardSize / 2 && j == boardSize / 2) {
				if (n->arr[i][j] != blank)
					return false;
			}
			else if ((i / (boardSize / 2 + 1)) == 0 && (j / (boardSize / 2 + 1)) == 0) {
				if (n->arr[i][j] != blue)
					return false;
			}
			else if ((i / (boardSize / 2)) >= 1 && (j / (boardSize / 2)) >= 1)
					if (n->arr[i][j] != red)
						return false;
		}
	}

	return true;
	*/

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
	std::cout << "Time (s) to make calculations: " << ((float)timer) / CLOCKS_PER_SEC << endl;
}

// From Dr. Yu's 8-Puzzle program, for determining duplicate graphs
long ForeAft::getNum(node* n)
{
	long num = 0;

	for (int i = 0; i < boardSize; i++)
		for (int j = 0; j < boardSize; j++)
			num = num * 3 + n->arr[i][j];

	n->num = num;

	return num;
}