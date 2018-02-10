//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		Heap.cpp
// Due Date:	15 February 2018
//

#include "stdafx.h"
#include "Heap.h"
#include <string>

using namespace std;

Heap::Heap()
{
	count = 0;
	heapSize = 50000;
	h = new node*[heapSize];

	for (int i = 0; i < heapSize; i++)
		h[i] = NULL;
}

Heap::~Heap()
{
	for (int i = 0; i < count; i++)
		delete h[i];

	delete []h;
}

void Heap::sort() {
	heapsort();
}

void Heap::add(node *n) {
	// If the heap is full, expand the array
	if (count+1 > heapSize) {
		heapSize += 50000;
		node **newH = new node*[heapSize];
		node **tmp;

		for (int i = 0; i < count; i++)
		{
			newH[i] = h[i];
		}
		tmp = h;
		h = newH;
		delete []tmp; // need to make sure this doesn't eliminate data
	}

	h[count] = n;
	count++;
}

node * Heap::popFront() {
	node *tmp = h[0];
	h[0] = h[count - 1];
	count--;
	sort();
	return tmp;
}

void Heap::buildMaxHeap() {
	for (int i = count - 1; i >= 0; i--)
		heapify(i);
}

void Heap::heapsort() {
	buildMaxHeap();

	for (int i = count - 1; i >= 0; i--)
	{
		swap(h[0], h[i]); // may or may not work
		heapify(0);
	}
}

void Heap::heapify(int i) {
	int l = left(i), r = right(i), largest;

	if (l < count && h[l]->f > h[i]->f)
		largest = l;
	else
		largest = i;

	if (r < count && h[r]->f > h[largest]->f)
		largest = r;

	if (largest != i)
	{
		swap(h[i], h[largest]);
		heapify(largest);
	}
}

// Is the heap empty
bool Heap::isEmpty() {
	if (count == 0)
		return true;

	return false;
}

node * Heap::getFront() {
	return h[0];
}

int Heap::getSize() {
	return count;
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
