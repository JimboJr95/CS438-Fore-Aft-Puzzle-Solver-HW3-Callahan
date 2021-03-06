//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		CS438 Homework 3.cpp
// Due Date:	22 February 2018
//
// Description of algorithms used:
//	I used a heapsort from a previous class to store and sort my data (though there may be a flaw in it, I'm not sure yet).
//	For determining the heuristic, if a given peg was not on its targed side of the board, the distance it was from the furthest corner of its target side was added to the value.
//	If the peg was on its target side of the board, no value was added.
//	If there was one or more successive rows of completed peg colors, I gave them a reward by dividing the final value by the number of rows completed.
//
// Timing Analysis:
//	This program works in release mode -> start without debugging for the following board sized:
//		5x5 (0.02 seconds), 7x7 (0.23 seconds) and 9x9 (7.306 seconds)
//	It crashes trying to solve 11 and above at the moment
//
//	I included BFS and DFS, but they only work on 5x5 boards. (don't need them, but added them)
//

#include "stdafx.h"
#include "ForeAft.h"
#include <iostream>
#include <string>
#include <fstream>

int main()
{
	ForeAft *f = new ForeAft();

	f->run();

	delete f;
    return 0;
}

