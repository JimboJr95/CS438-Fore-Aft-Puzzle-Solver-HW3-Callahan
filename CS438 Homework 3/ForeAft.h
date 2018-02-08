//
// Author:		James Callahan
// Class:		CS438 (Artificial Intelligence)
// File:		ForeAft.h
// Due Date:	15 February 2018
//

#pragma once
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class ForeAft
{
public:
	// Constructor/Destructor
	ForeAft(string filename);
	~ForeAft();

	// Functions
	void run();

private:
	bool openFile(string filename, ifstream &infile);
};

