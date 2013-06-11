///////////////////////////////////////
// Workfile    : Main.cpp
// Author      : Matthias Schett
// Date        : 12-04-2013
// Description : Dive Computer
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#include "DiveComputer.h"
#include <string>
#include "scanner.h"
#include <iomanip>

using namespace std;

vector<DiveData> diveComputer (0);

bool isTbReal(scanner &scan){
    return scan.symbol_is_real();
}

bool isTbBracket(scanner &scan){
    return scan.symbol_is_lpar();
}

bool isTbInt(scanner &scan){
    return scan.symbol_is_integer();
}

time_t parseTime(scanner &scan){
    time_t temp = scan.get_integer();
    scan.next_symbol();
    return temp;
}

double parseDepth( scanner & scan ) {
    scan.next_symbol();
    if(isTbReal(scan)){
        double temp = scan.get_real();
        scan.next_symbol();
        return temp;
    }
    return 0.0;
}

void calcUpDown(DiveData &newData) {
    if(!diveComputer.empty()){
        DiveData oldData = diveComputer.at(diveComputer.size() - 1);
        newData.mUpDown = (oldData.mDepth - newData.mDepth) / (newData.mTime - oldData.mTime);
    } else {
        newData.mUpDown = 0.0;
    }
}

void readDiveData( std::istream &is ){

    scanner scan(is);

    while(!scan.symbol_is_eof()){
        if(isTbInt(scan)){
            time_t parsedTime = parseTime(scan);
            if(isTbBracket(scan)){
                double parsedDepth = parseDepth(scan);
                scan.next_symbol();
                DiveData data;
                data.mDepth = parsedDepth;
                data.mTime = parsedTime;
                calcUpDown(data);
                diveComputer.push_back(data);
            }
        } else {
            throw std::exception("Unkown format");
        }
    }
}

ostream& hr(ostream& os) {
    return os << "-------------------------------------------------";
}

ostream& colSpace(ostream& os) {
    return os << setw(colSpacing) << " ";
}

ostream& colWidth(ostream& os){
    return os << setw(colWidthNum) << " ";
}

ostream& colFormat(ostream& os) {
    return os << setw(colWidthNum);
}

ostream& formatUpDown(ostream &os){
    return os << right << setiosflags(ios::fixed) << setprecision(4);
}

ostream& formatDepth(ostream &os){
    return os << right << setiosflags(ios::fixed) << setprecision(2);
}


void printTableHeader(std::ostream &os){
    os << left << colFormat << "Dive Time " << colSpace << colFormat << "Dive Depth " << colSpace << colFormat << "Down/Up";
    os << endl << colFormat << "(hh:mm:ss)"  << colSpace << colFormat << "(m)" << colSpace  << colFormat << "(m/sec)" << endl << hr << endl;
}

void printDataLine(std::ostream &os, DiveData const & data, int i){
    struct tm * ptm = gmtime(&data.mTime);
    if(i != 0){ // Don't print this at the first line
        os << colWidth << colSpace << colWidth << colSpace << colFormat << formatUpDown << data.mUpDown << endl;
    }
    os << colFormat << put_time(ptm,"%H:%M:%S") << colSpace << colFormat << formatDepth << data.mDepth << endl;
}

void printDiveData( std::ostream &os ){

   printTableHeader(os);

   for(int i = 0; i < diveComputer.size(); i++){
       printDataLine(os, diveComputer.at(i), i);
   }

}
