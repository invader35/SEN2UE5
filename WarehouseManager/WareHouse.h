///////////////////////////////////////
// Workfile    : Warehouse.h
// Author      : Matthias Schett
// Date        : 20-04-2013
// Description : Ware house management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////
#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Article.h"
#include <vector>
#include <fstream>
#include <ostream>

class WareHouse {
private:

    std::vector<Article> mArticles;
    std::string mWareHouseName;

    
    size_t searchLongestName();
    size_t searchHighestArticleNum();
    size_t searchHighestQuantity();
    size_t searchHighestPrice();

public:
    WareHouse(std::string wareHouseName);
    ~WareHouse();

    //************************************
    // Method:    addArticle
    // FullName:  WareHouse::addArticle
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: Article const & newArticle
    //************************************
    void addArticle(Article const &newArticle);
    
    //************************************
    // Method:    getNumberOfArticles
    // FullName:  WareHouse::getNumberOfArticles
    // Access:    public 
    // Returns:   size_t
    // Qualifier:
    //************************************
    size_t getNumberOfArticles();

    //************************************
    // Method:    readArticlesFromFile
    // FullName:  WareHouse::readArticlesFromFile
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: ifstream & file
    // Reads articles from a file and adds them
    //************************************
    void readArticlesFromFile(std::ifstream &file);

    //************************************
    // Method:    printArticleList
    // FullName:  WareHouse::printArticleList
    // Access:    public 
    // Returns:   void
    // Qualifier:
    // Parameter: ostream & os
    // Prints the articles to the given stream
    //************************************
    void printArticleList(std::ostream &os);
};
#endif // WAREHOUSE_H