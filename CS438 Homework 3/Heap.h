//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		Heap.h
// Due Date:	22 February 2018
//

#pragma once
#include <string>

// Colors are cast as integer and used for storing the state of a spot on the board
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
	node *parent;
	long num;

	// basic constructor
	node(int boardSize) {
		arr = new color*[boardSize]; // initialize size of the array
		blankR = 0;
		blankC = 0;
		f = 0;
		g = 0;
		h = 0;
		id = "";
		num = 0;

		// init array values to invalid
		for (int i = 0; i < boardSize; i++) {
			arr[i] = new color[boardSize];

			for (int j = 0; j < boardSize; j++) {
				arr[i][j] = invalid;
			}
		}

	}
	
	// copy constructor
	node(node *n, int boardSize) {
		arr = new color*[boardSize]; // initialize size of the array
		this->num = 0;

		for (int i = 0; i < boardSize; i++) {
			arr[i] = new color[boardSize];
			
			for (int j = 0; j < boardSize; j++) {
				this->arr[i][j] = n->arr[i][j];
			}
		}

		this->blankR = n->blankR;
		this->blankC = n->blankC;
		this->f = n->f;
		this->g = n->g;
		this->h = n->h;
	}
};


class Heap
{
public:
	// Functions
	Heap();
	~Heap();
	void add(node *n);
	node * popFront();
	node * getFront();
	bool isEmpty();
	int getSize();
	void sort();

private:
	// Variables
	node *root, **h, **popped;
	int count, heapSize, poppedNum, poppedSize;

	// Functions
	int parent(int i);
	int left(int i);
	int right(int i);

	void heapsort();
	void buildMaxHeap();
	void heapify(int i);
	void expandPopped();
};

