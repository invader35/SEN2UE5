///////////////////////////////////////
// Workfile    : Article.cpp
// Author      : Matthias Schett
// Date        : 20-04-2013
// Description : Ware house management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////
#include "Article.h"
#include <exception>

using namespace std;

Article::Article(int articleNumber, std::string articleName, size_t quantity, double price) : mArticleNumber(articleNumber), mArticleName(articleName), mQuantity(quantity), mPrice(price)
{
}

Article::~Article()
{
}

int Article::getArticleNumber(){
    return mArticleNumber;
}

std::string &Article::getArticleName(){
    return mArticleName; 
}

size_t Article::getQuantity(){
    return mQuantity;
}

double Article::getPrice(){
    return mPrice;
}

void Article::setArticleNumber(int articleNumber){
    mArticleNumber = articleNumber;
}

void Article::setArticleName(std::string & articleName){
    mArticleName = articleName;
}

void Article::setQuantity(size_t quantity){
    mQuantity = quantity;
}

void Article::setPrice(double price){
    if(price < 0.0){
        throw std::exception("Price is not allowed to be negative");
    }
    mPrice = price;
}

bool Article::operator<(Article const & vgl) const{
    return (mQuantity < vgl.mQuantity);
}