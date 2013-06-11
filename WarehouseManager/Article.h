///////////////////////////////////////
// Workfile    : Article.h
// Author      : Matthias Schett
// Date        : 20-04-2013
// Description : Ware house management
// Remarks     : -
// Revision    : 0
///////////////////////////////////////

#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <exception>

class ArticleException: public std::exception
{

};

class Article {
private:

    int mArticleNumber;
    std::string mArticleName;
    size_t mQuantity;
    double mPrice;

public:
    // Ctr
    Article(int articleNumber, std::string ArticleName, size_t quantity, double price);
    
    // Dtr
    ~Article();

    // Getters
    int getArticleNumber();
    std::string & getArticleName();
    size_t getQuantity();
    double getPrice();

    // Setters
    void setArticleNumber(int articleNumber);
    void setArticleName(std::string & articleName);
    void setQuantity(size_t quantity);
    // Throws exception if price is negativ
    void setPrice(double price);

    // compares the quantity of two articles
    bool operator<(Article const & vgl) const;

};

#endif