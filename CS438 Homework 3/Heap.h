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
	node *parent;
	bool *rowsDone, *colsDone;
	long num;

	// basic constructor
	node(int boardSize) {
		arr = new color*[boardSize]; // initialize size of the array
		rowsDone = new bool[boardSize];
		colsDone = new bool[boardSize];
		blankR = 0;
		blankC = 0;
		f = 0;
		g = 0;
		h = 0;
		id = "";
		num = 0;

		// initialize second dimension of the array and row/col completion arrays
		for (int i = 0; i < boardSize; i++) {
			arr[i] = new color[boardSize];
			rowsDone[i] = false;
			colsDone[i] = false;
		}

		// init array values to invalid
		for (int i = 0; i < boardSize; i++)
			for (int j = 0; j < boardSize; j++)
				arr[i][j] = invalid;

	}
	
	// copy constructor
	node(node *n, int boardSize) {
		arr = new color*[boardSize]; // initialize size of the array
		rowsDone = new bool[boardSize];
		colsDone = new bool[boardSize];
		this->num = 0;

		// initialize second dimension of the array
		for (int i = 0; i < boardSize; i++) {
			arr[i] = new color[boardSize];
			rowsDone[i] = false;
			colsDone[i] = false;
		}

		for (int i = 0; i < boardSize; i++) {
			for (int j = 0; j < boardSize; j++) {
				this->arr[i][j] = n->arr[i][j];
			}
			this->rowsDone[i] = n->rowsDone[i];
			this->colsDone[i] = n->colsDone[i];
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
	Heap();
	~Heap();
	void add(node *n);
	node * popFront();
	node * getFront();
	bool isEmpty();
	int getSize();
	void sort();
	//bool alreadyAdded(node *n);

private:
	node *root, **h, **popped;
	//node h[50000];
	int count, heapSize, poppedNum, poppedSize;

	int parent(int i);
	int left(int i);
	int right(int i);

	void heapsort();
	void buildMaxHeap();
	void heapify(int i);
	void expandPopped();
	//void swap(node *a, node *b);
};

