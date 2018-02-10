//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.h
// Due Date:	15 February 2018
//

#pragma once
#include "Heap.h"
#include <string>
#include <iostream>
#include <vector>

typedef int direction;

const direction UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UP2 = 5, DOWN2 = 6, LEFT2 = 7, RIGHT2 = 8;

using namespace std;

class ForeAft
{
public:
	// Constructor/Destructor
	ForeAft();
	~ForeAft();

	// Functions
	void run();

private:
	// Variables
	node *root, *current;
	int boardSize, nodesVisited;
	float C = 2.0; // C value is constant for heuristic
	//vector<node*> open, closed;
	Heap *open, *closed;

	// Functions
	void AStar();
	
	bool validNumber(int num, int beginRange, int endRange);
	bool moveBlankUpOne(node *n);
	bool moveBlankUpTwo(node *n);
	bool moveBlankDownOne(node *n);
	bool moveBlankDownTwo(node *n);
	bool moveBlankLeftOne(node *n);
	bool moveBlankLeftTwo(node *n);
	bool moveBlankRightOne(node *n);
	bool moveBlankRightTwo(node *n);
	bool makeMove(direction d);

	float heuristic(node *n);
	int manhattanDistance(int row1, int row2, int col1, int col2);

	void copyNode(node *source, node *target);
	void printBoard(node *n);
	void printSolutionToScreen();
	void printSolutionToFile();
	void getBoardId(node *n);

	bool solutionFound(node *n);
};

