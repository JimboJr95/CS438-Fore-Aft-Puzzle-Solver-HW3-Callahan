//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		Heap.h
// Due Date:	15 February 2018
//

#pragma once
#include <string>

typedef int color;

const color invalid = 9;
const color red = 1;
const color blue = 2;
const color blank = 3;

using namespace std;

struct node {
	// node constructor
	color **arr;
	int blankR, blankC;
	float f, g, h; // values for the heuristic
	string id;
	node *partent;

	node(int boardSize) {
		arr = new color*[boardSize]; // initialize size of the array
		blankR = 0;
		blankC = 0;
		f = 0;
		g = 0;
		h = 0;
		id = "";

		// initialize second dimension of the array
		for (int i = 0; i < boardSize; i++)
			arr[i] = new color[boardSize];

		// init array values to invalid
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				arr[i][j] = invalid;

	}
};

class Heap
{
public:
	Heap();
	~Heap();
	void add(node *n);
	node * popFront();
	node * getFront();
	bool isEmpty();
	int getSize();
	void sort();

private:
	node * root, **h;
	int count, heapSize;
	int parent(int i);
	int left(int i);
	int right(int i);

	void heapsort();
	void buildMaxHeap();
	void heapify(int i);
};

