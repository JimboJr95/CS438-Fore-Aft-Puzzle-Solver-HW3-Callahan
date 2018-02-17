//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.h
// Due Date:	22 February 2018
//

#pragma once
#include "Heap.h"
#include <string>
#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <set>
#include <list>

// directions is a typedef integer that tells the function makeMove which direction to move the blank spot
typedef int direction;
typedef int algorithm;

const direction UP = 1, DOWN = 2, LEFT = 3, RIGHT = 4, UP2 = 5, DOWN2 = 6, LEFT2 = 7, RIGHT2 = 8;
const algorithm aStar = 20, bfs = 21, dfs = 22;

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
	long solution;
	int boardSize, nodesVisited, expRowBlue, expRowRed, expColBlue, expColRed;
	int C = 10; // C value is constant for heuristic
	Heap *open;
	time_t timer;
	set<long> found;
	list<node*> openList, closedList;

	// Functions
	void AStar();
	void BFS();
	void DFS();
	
	bool validNumber(int num, int beginRange, int endRange);
	bool moveBlankUpOne(node *n);
	bool moveBlankUpTwo(node *n);
	bool moveBlankDownOne(node *n);
	bool moveBlankDownTwo(node *n);
	bool moveBlankLeftOne(node *n);
	bool moveBlankLeftTwo(node *n);
	bool moveBlankRightOne(node *n);
	bool moveBlankRightTwo(node *n);
	bool makeMove(direction d, algorithm a);

	float heuristic(node *n);
	int manhattanDistance(int row1, int row2, int col1, int col2);

	void copyNode(node *source, node *target);
	void printBoard(node *n);
	void printSolutionToScreen();
	void printSolutionToFile(ofstream &outfile, string filename);
	void getBoardId(node *n);

	bool solutionFound(node *n);
	long getNum(node *n);

	void startTimer();
	void endTimer();
};

