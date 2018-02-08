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

class ForeAft
{
public:
	// Constructor/Destructor
	ForeAft();
	~ForeAft();

	// Functions
	void run();

private:
	bool validNumber(int num, int beginRange, int endRange);
};

