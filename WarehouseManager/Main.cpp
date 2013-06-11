///////////////////////////////////////
// Workfile    : Main.cpp
// Author      : Matthias Schett
// Date        : 20-04-2013
// Description : Ware house management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////
#include <vld.h>
#include "Article.h"
#include "WareHouse.h"
#include <fstream>
#include <iostream>
#include <string>

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
    ofstream oFile("OutputA2.txt");
    try{
        printTestHeader(1, oFile);

        WareHouse newWarehouse (string("TestWarehouse"));

        ifstream file ("Input.txt");

        newWarehouse.readArticlesFromFile(file);

        newWarehouse.printArticleList(oFile);

        printTestHeader(2, oFile);

        WareHouse newWarehouse2 (string("TestWarehouse"));
    
        ifstream file2 ("InputWrong.txt");
    
        newWarehouse2.readArticlesFromFile(file2);
    
        newWarehouse2.printArticleList(oFile);

        file.close();
        file2.close();
    } catch(exception e){
        oFile << e.what();
    }

    oFile.close();

    cin.get();
    return 0;
}