/*****************************************************************************
 * Developer: Xiaoyu Li
 * Project: CSCE-315 Individual Assignment
 *
 * File: ./IA1/books_data.h
 *****************************************************************************/
#ifndef _BOOKS_DATA_H
#define _BOOKS_DATA_H

/*****************************************************************************
 * Standard Library Includes
 *****************************************************************************/
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>




class Classes_data;


class Books_data
{

friend void defineBook(std::istringstream&,std::vector<Books_data>&);

private:
    long isbn;
    std::string title;
    std::string pub_date;
    std::string author;
    int edition;
    double new_price;
    double used_price;
    double ebook_price;
    double rent_price;


public:
    /* Constructor */
    Books_data();

    /* Getter Functions*/
    long getIsbn()const;
    int getEdition()const;
    double getNewPrice()const;
    double getUsedPrice()const;
    double getRentPrice()const;
    double getEbookPrice()const;
    std::string getTitle()const;
    std::string getPubDate()const;
    std::string getAuthor()const;

    /* Setter Functions*/
    void setIsbn(long new_isbn);
    void setEdition(int new_edition);
    void setNewPrice(double price);
    void setUsedPrice(double price);
    void setRentPrice(double price);
    void setEbookPrice(double price);
    void setTitle(std::string new_title);
    void setPubDate(std::string new_date);
    void setAuthor(std::string new_author);

};
// Print all information known about a particular book
void printBook(std::istringstream&, std::vector<Books_data>&);

// Print a kust if all books that are defined
void printBookALL(std::vector<Books_data>&);

// Print the book required and optional for all sections of a given course
void printBookCOURSE(std::istringstream&, std::vector<Classes_data>&);

// Print the books required and optional for a given section of a course
void printBookSECTION(std::istringstream&, std::vector<Classes_data>&);

// Print the list of all books used in a department, given by department code.
void printBookDEPT(std::istringstream&, std::vector<Classes_data>&);

// Print all books with known publication dates in the given month/year or later
void printBookYEAR(std::istringstream&, std::vector<Books_data>&);

// Print the average minimum and maximum costs of all books in a department.
void printBookAVG(std::istringstream&, std::vector<Classes_data>&);

// Define a book
void defineBook(std::istringstream&, std::vector<Books_data>&);

// Define a characteristic of a book
void defineBookChar(std::istringstream&, std::vector<Books_data>&);

// Define the cost for a book
void defineBookPrice(std::istringstream&, std::vector<Books_data>&);



/* Helper Functions*/

// Formatted output for a give book
std::ostream& printBookInfo(std::ostream&, std::vector<Books_data>::const_iterator);

// Formatted output for a give class
std::ostream& printBookInfo(std::ostream&, std::vector<Classes_data>::const_iterator);

// Convert date from string to int
int parseDate(const std::string &input);

void error_cmd();

// Return the cost of the cheapest version
double getLowest(const Books_data&);

// Return the cost of the most expensive version
double getHighest(const Books_data&);

// Return a iterator to that item
// If no such element is found, the function returns last.
std::vector<Books_data>::iterator Lookup(long, std::vector<Books_data>&);

inline double Maximum(const double&, const double&);
inline double Minimum(const double&, const double&);

#endif