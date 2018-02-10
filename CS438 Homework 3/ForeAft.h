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
	vector<node*> open, closed;

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

	float heuristic(node *n);

	void copyNode(node *source, node *target);
	void printBoard(node *n);
	void getBoardId(node *n);

	bool solutionFound(node *n);
};

