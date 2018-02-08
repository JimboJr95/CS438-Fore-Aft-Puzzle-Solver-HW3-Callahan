//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.cpp
// Due Date:	15 February 2018
//
// Description:
//		This program is meant to solve a fore aft puzzle (example: https://www.cheesygames.com/foreaft/ )
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

		// Perform selected search on selected size

	}
}

// Checks to make sure the number input by the user is valid
bool ForeAft::validNumber(int num, int beginRange, int endRange) {
	if(num >= beginRange && num <= endRange)	
		return true;
	
	return false;
}
