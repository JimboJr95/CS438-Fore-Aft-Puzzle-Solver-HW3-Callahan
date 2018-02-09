//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.h
// Due Date:	15 February 2018
//

#pragma once
#include <string>
#include <iostream>

using namespace std;

typedef int color;

const color invalid = 99;
const color red = 1;
const color blue = 2;
const color blank = 3;

struct node {
	// node constructor
	color **arr;
	int blankR, blankC;

	node(int boardSize) {
		arr = new color*[boardSize]; // initialize size of the array
		blankR = 0;
		blankC = 0;

		// initialize second dimension of the array
		for (int i = 0; i < boardSize; i++)
			arr[i] = new color [boardSize];

		// init array values to invalid
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				arr[i][j] = invalid;

	}
};

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
	node * root;
	int boardSize;

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

	void copyNode(node *source, node *target);
	void printBoard(node *n);
	//bool isMoveable (direction dir, )
};

