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
#include <string>
#include <iostream>

using namespace std;

// Constructor
ForeAft::ForeAft()
{
}

// Destructor
ForeAft::~ForeAft()
{
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
			cout << "Please select a value from 5 - 13\n\n";
			goto board;
		}

		if (!validNumber(boardSizeI, 5, 13))
		{
			cout << "Enter a valid board size (5-13)\n";
			goto board;
		}

		boardSize = boardSizeI;

		// Initialize the root node
		root = new node(boardSizeI);
		for (int i = 0; i < boardSizeI; i++)
		{
			for (int j = 0; j < boardSizeI; j++)
			{
				if (i == boardSize / 2 && j == boardSize / 2) {
					root->arr[i][j] = blank;
					root->blankR = i;
					root->blankC = j;
				}
				else if ((i / (boardSizeI / 2 + 1)) == 0 && (j / (boardSizeI / 2 + 1)) == 0)
					root->arr[i][j] = red;
				else if ((i / (boardSizeI / 2)) >= 1 && (j / (boardSizeI / 2)) >= 1)
					root->arr[i][j] = blue;
			}
		}


		// Perform selected search on selected size

		printBoard(root);

		delete root;
	}
}

void ForeAft::AStar() {

}

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
	if (n->arr[n->blankR + 1][n->blankC] != invalid && n->blankR + 1 < boardSize)
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
