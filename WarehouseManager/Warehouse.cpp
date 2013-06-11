///////////////////////////////////////
// Workfile    : Warehouse.cpp
// Author      : Matthias Schett
// Date        : 20-04-2013
// Description : Ware house management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////
#include "WareHouse.h"
#include "scanner.h"
#include <exception>
#include <algorithm>
#include <iomanip>

using namespace std;

// Comparison function object for sort method
class comp
{
public:
    bool operator() (const Article &a, const Article &b) const 
    {
        return a < b;
    }
};

int intlen(float start) { 
    int end = 0; 
    while(start >= 1) { 
        start = start/10; 
        end++; 
    } 
    return end; 
} 

size_t WareHouse::searchLongestName(){
    size_t length = 0;
    for (size_t i = 0; i < mArticles.size() - 1; i++){
        size_t length1 = mArticles.at(i).getArticleName().length();
        size_t length2 = mArticles.at(i+1).getArticleName().length();
        if(length1 < length2){
            length = length2;
        } else if(length1 > length2){
            length = length1;
        }
    }

    return length;
}

size_t WareHouse::searchHighestArticleNum(){
    size_t length = 0;
    for (size_t i = 0; i < mArticles.size() - 1; i++){
        size_t length1 = mArticles.at(i).getArticleNumber();
        size_t length2 = mArticles.at(i+1).getArticleNumber();
        if(length1 < length2){
            length = length2;
        } else if(length1 > length2){
            length = length1;
        }
    }

    return intlen(length);
}

size_t WareHouse::searchHighestQuantity(){
    size_t length = 0;
    for (size_t i = 0; i < mArticles.size() - 1; i++){
        size_t length1 = mArticles.at(i).getQuantity();
        size_t length2 = mArticles.at(i+1).getQuantity();
        if(length1 < length2){
            length = length2;
        } else if(length1 > length2){
            length = length1;
        }
    }

    return intlen(length);
}

size_t WareHouse::searchHighestPrice(){
    size_t length = 0;
    for (size_t i = 0; i < mArticles.size() - 1; i++){
        size_t length1 = mArticles.at(i).getPrice();
        size_t length2 = mArticles.at(i+1).getPrice();
        if(length1 < length2){
            length = length2;
        } else if(length1 > length2){
            length = length1;
        }
    }

    return intlen(length);
}


bool isTbReal(scanner &scan){
    return scan.symbol_is_real();
}

bool isTbString(scanner &scan){
    return scan.symbol_is_string();
}

bool isTbInt(scanner &scan){
    return scan.symbol_is_integer();
}

int parseArticleNumberOrQuantity(scanner &scan){
    if(isTbInt(scan)){
        return scan.get_integer();
    }
    throw std::exception("Unknown format");
}

string parseArticleName(scanner &scan){
    if(isTbString(scan)){
        return scan.get_string();
    }
    throw std::exception("Unknown format");
}

double parsePrice(scanner &scan){
    if(isTbReal(scan)){
        return scan.get_real();
    }
    throw std::exception("Unknown format");
}

WareHouse::WareHouse(std::string wareHouseName) : mWareHouseName(wareHouseName), mArticles() {
}

WareHouse::~WareHouse(){
}

void WareHouse::addArticle(Article const &newArticle){
    mArticles.push_back(newArticle);
}

size_t WareHouse::getNumberOfArticles(){
    return mArticles.size();
}

void WareHouse::readArticlesFromFile(std::ifstream &file){
    scanner scan (file);

    while(!scan.symbol_is_eof()){
        if(isTbInt(scan)){
            int articleNum = parseArticleNumberOrQuantity(scan);

            scan.next_symbol();
            scan.next_symbol();
            if(isTbString(scan)){
                string articleName = parseArticleName(scan);
                scan.next_symbol();
                scan.next_symbol();
                if(isTbInt(scan)){
                    size_t quant = parseArticleNumberOrQuantity(scan);
                    scan.next_symbol();
                    scan.next_symbol();
                    if(isTbReal(scan)){
                        double price = parsePrice(scan);
                        scan.next_symbol();
                        scan.next_symbol();
                        Article art (articleNum, articleName, quant, price);
                        mArticles.push_back(art);
                    }
                }
            }
        } else{
            throw std::exception("Unknown format");
        }
    }
}

void WareHouse::printArticleList( std::ostream &os ) {

    sort(mArticles.begin(), mArticles.end(), comp());
    
    size_t colSpacing = 2;
    size_t prec = 2;
    size_t articleNumLength = searchHighestArticleNum() + colSpacing;
    size_t articleNameLength = searchLongestName() + colSpacing;
    size_t articleQuantityLength = searchHighestQuantity() + colSpacing;
    size_t articlePriceLength = searchHighestPrice() + colSpacing + prec;
    

    os << "Article list of Warehouse " << mWareHouseName << endl;

    for (std::vector<Article>::iterator it=mArticles.begin(); it!=mArticles.end(); ++it){
        os << setw(articleNumLength) << left << it->getArticleNumber();
        os << setw(articleNameLength) << it->getArticleName();
        os << setw(articleQuantityLength) << it->getQuantity();
        os << right << setiosflags(ios::fixed) << setw(articlePriceLength) << setprecision(prec) << it->getPrice() << endl;
    }

}