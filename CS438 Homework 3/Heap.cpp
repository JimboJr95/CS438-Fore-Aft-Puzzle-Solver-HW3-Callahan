//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		Heap.cpp
// Due Date:	22 February 2018
//

#include "stdafx.h"
#include "Heap.h"
#include <string>

using namespace std;

// Constructor
Heap::Heap()
{
	count = 0;
	poppedNum = 0;
	heapSize = 50;
	poppedSize = 50000;
	h = new node*[heapSize];
	popped = new node*[poppedSize];

	for (int i = 0; i < heapSize; i++) {
		h[i] = NULL;
		popped[i] = NULL;
	}
}

// Destructor
Heap::~Heap()
{
	for (int i = 0; i < count; i++)
		delete h[i];

	for (int i = 0; i < poppedNum; i++)
		delete popped[i];

	delete[]h;
	delete[]popped;
}

// Sorts the heap
void Heap::sort() {
	heapsort();
}

// Adds a new node to the heap
void Heap::add(node *n) {
	if (count+1 > heapSize)
	{
		count = heapSize / 2;

		if (poppedNum + heapSize / 2 > poppedSize)
			expandPopped();

		for (int i = heapSize / 2; i < heapSize; i++) {
			popped[poppedNum] = h[i];
			poppedNum++;
		}
	}

	h[count] = n;
	count++;
}

// Pops the front of the heap and puts it in the popped array
node * Heap::popFront() {
	node *tmp = h[0];
	h[0] = h[count - 1];
	count--;
	sort();
	// add check if popped num has exceeded limit
	if (poppedNum + 1 > poppedSize)
		expandPopped();

	popped[poppedNum] = tmp;
	poppedNum++;
	return tmp;
}


// The next three functions make up the actual heap sort
void Heap::buildMaxHeap() {
	for (int i = count / 2 - 1; i >= 0; i--)
		heapify(i);
}

void Heap::heapsort() {
	buildMaxHeap();

	for (int i = count - 1; i >= 0; i--)
	{
		swap(h[0], h[i]);
		heapify(i);
	}
}

void Heap::heapify(int i) {
	int l = left(i), r = right(i), smallest;

	if (l < count && h[l]->f < h[i]->f)
		smallest = l;
	else
		smallest = i;

	if (r < count && h[r]->f < h[smallest]->f)
		smallest = r;

	if (smallest != i)
	{
		swap(h[i], h[smallest]);
		heapify(smallest);
	}
}

// Is the heap empty
bool Heap::isEmpty() {
	if (count <= 0)
		return true;

	return false;
}

// Returns the front node of the heap
node * Heap::getFront() {
	return h[0];
}

// Returns total number of nodes viewed
int Heap::getSize() {
	return count + poppedNum;
}

// Finds parent for heap
int Heap::parent(int i) {
	return ((i - 1) / 2);
}

// Finds left child for heap
int Heap::left(int i) {
	return 2 * i + 1;
}

// Finds right child for heap
int Heap::right(int i) {
	return 2 * i + 2;
}

// This function expands the array that holds the popped nodes
void Heap::expandPopped() {
	poppedSize += 10000;
	node **tmp = new node*[poppedSize];

	for (int i = 0; i < poppedNum; i++)
		tmp[i] = popped[i];

	//delete[]popped;

	popped = tmp;
}