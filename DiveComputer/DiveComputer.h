///////////////////////////////////////
// Workfile    : Main.cpp
// Author      : Matthias Schett
// Date        : 12-04-2013
// Description : Dive Computer
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#ifndef DIVE_H
#define DIVE_H

#include <ctime>
#include <vector>
#include <ostream>
#include <istream>
#include <exception>

int const colSpacing = 4;
int const colWidthNum = 10;
int const diveDepthPrecision = 2;
int const upDownPrecision = 3;

struct DiveData{
    time_t mTime;
    double mDepth;
    double mUpDown;
};

extern std::vector<DiveData> diveComputer;

//************************************
// Method:    readDiveData
// FullName:  readDiveData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: std::istream &is
// Reads dive data from stream and saves it - throws exception when an error occurs
//************************************
void readDiveData(std::istream &is);

//************************************
// Method:    printDiveData
// FullName:  printDiveData
// Access:    public 
// Returns:   void
// Qualifier:
// Parameter: std::ostream & os
// Prints formatted dive data to stream
//************************************
void printDiveData(std::ostream &os);

#endif