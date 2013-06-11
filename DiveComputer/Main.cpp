///////////////////////////////////////
// Workfile    : Main.cpp
// Author      : Matthias Schett
// Date        : 12-04-2013
// Description : Dive Computer
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include <vld.h>
#include <iostream>
#include <fstream>
#include <string>
#include "scanner.h"
#include "DiveComputer.h"
#include <exception>

using namespace std;

void printTestHeader(int testNumber, ostream & stream){
    stream << endl << endl;
    if(testNumber < 10){
        stream << "Testfall 0" << testNumber;
    } else {
        stream << "Testfall " << testNumber;
    }
    stream << endl << "-----------" << endl << endl;
    
}

int main(){
    ofstream oFile("OutputA1.txt");
    try{
        printTestHeader(1, oFile);

        ifstream file("Test.txt");
        readDiveData(file);
        
        printDiveData(oFile);
        
        printTestHeader(2, oFile);
        
        ifstream file2("TestIncorrect.txt");
        readDiveData(file2);

        printDiveData(oFile);

        file.close();
        file2.close();
        
    } catch(std::exception &e){
        oFile << e.what();
    }
    oFile.close();
    cin.get();
    return 0;
}