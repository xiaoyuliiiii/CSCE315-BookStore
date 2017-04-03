/*****************************************************************************
 * Developer: Xiaoyu Li
 * Project: CSCE-315 Individual Assignment
 *
 * File: ./IA1/books_data.cpp
 *****************************************************************************/


/*****************************************************************************
 * User Defined Includes
 *****************************************************************************/

#include "books_data.h"
#include "courses_data.h"

Books_data::Books_data()
{

    title = "";
    pub_date = "";
    author = "";
    isbn = -1;
    edition = -1;
    new_price = -1.0;
    used_price = -1.0;
    ebook_price = -1.0;
    rent_price = -1.0;
}

void printBook(std::istringstream &iss, std::vector<Books_data> &books)
{
    long isbn_key = 0;
    iss >> isbn_key;

    if (isbn_key == 0){
        error_cmd();
        return;
    }
    auto found = Lookup(isbn_key,books);

    if(found != books.end()){
        printBookInfo(std::cout,found) << "\n";
    }
    else{
        std::cerr << "Error : The isbn or department code is not in our database." << std::endl;

    }
}

void printBookALL(std::vector<Books_data> &books)
{
    for(auto beg = books.cbegin(); beg != books.cend(); beg++){
        printBookInfo(std::cout,beg);
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
}

void printBookCOURSE(std::istringstream &iss, std::vector<Classes_data> &classes)
{
    std::string dept_key;
    int course_key;
    bool found;

    iss >> dept_key >> course_key;

    if(dept_key == ""){
        error_cmd();
        return;
    }
    std::vector<long>printed_isbns;


    // print book if key is match
    for(auto beg = classes.begin(); beg != classes.end();beg++){
        if(beg->course.getDeptCode() == dept_key && beg->course.getCourseNum() == course_key) {

            auto isPrinted = find(printed_isbns.cbegin(),
                                  printed_isbns.cend(), beg->book.getIsbn());
            //print list the books only once
            if ( isPrinted == printed_isbns.end()){
                printed_isbns.push_back(beg->book.getIsbn());

                printBookInfo(std::cout, beg);
                std::cout << "Class : \n" << "  -  Section    : ";
            }

            //print all sections that contain this book.
            std::cout << beg->section << " ";
            found = true;
        }
    }
    std::cout << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

    if(!found) {
        std::cerr << "Error : The department or course is not in our database." << std::endl;
        return;
    }
}

void printBookSECTION(std::istringstream &iss, std::vector<Classes_data> &classes)
{
    std::string dept_key;
    int course_key,section_key;
    bool found = false;

    iss >> dept_key >> course_key >> section_key;

    if(dept_key == ""){
        error_cmd();
        return;
    }

    for(auto beg = classes.begin(); beg != classes.end();beg++){
        if(beg->course.getDeptCode() == dept_key &&
           beg->course.getCourseNum() == course_key &&
           beg->section == section_key) {
                printBookInfo(std::cout, beg);
                found = true;
        }
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

    if(!found) {
        std::cerr << "Error : The department code, course or section is not in our database." << std::endl;
        return;
    }
}

void printBookDEPT(std::istringstream &iss, std::vector<Classes_data> &classes)
{
    std::string dept_key;
    bool found = false;

    iss >> dept_key;

    if(dept_key == ""){
        error_cmd();
        return;
    }

    std::vector<long>printed_isbns;

    //print list the books only once
    for(auto beg = classes.begin(); beg != classes.end();beg++){
        if(beg->course.getDeptCode() == dept_key) {
            auto isPrinted = find(printed_isbns.cbegin(),
                                  printed_isbns.cend(), beg->book.getIsbn());

            if ( isPrinted == printed_isbns.end()){
                printBookInfo(std::cout, beg);
                printed_isbns.push_back(beg->book.getIsbn());
            }
            found = true;
        }
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    if(!found) {
        std::cerr << "Error : The department code is not in our database." << std::endl;
    }
}

void printBookYEAR(std::istringstream &iss, std::vector<Books_data> &books)
{
    std::string temp;
    iss >> temp;
    if(temp == ""){
        error_cmd();
        return;
    }

    //convert string to int
    int date = parseDate(temp);

    //Print all books with known date >= given date
    for(auto beg = books.cbegin(); beg != books.cend(); ++beg){
        if(parseDate(beg->getPubDate()) >= date){
            printBookInfo(std::cout,beg);
        }
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
}

void printBookAVG(std::istringstream &iss, std::vector<Classes_data> &classes)
{
    std::string dept_key;
    bool found;
    double max_total = 0, min_total = 0;
    int min_cnt = 0, max_cnt = 0;

    iss >> dept_key;

    if(dept_key == ""){
        error_cmd();
        return;
    }
    //calculate the total minimum and maximum costs of all books in a department
    for(auto beg = classes.begin(); beg != classes.end();beg++){
        if(beg->course.getDeptCode() == dept_key){
            if (beg->required == 'O'){
                min_total += getLowest(beg->book);
                max_total += getHighest(beg->book);
                min_cnt++;
                max_cnt++;
            }
            //ingore books that has no known cost
            else if(getHighest(beg->book) != -1){
                max_total += getHighest(beg->book);
                max_cnt++;
            }
            found = true;
        }
    }

    if(!found) {
        std::cerr << "Error : The department code is not in our database." << std::endl;
    }

    if(min_total != 0) std::cout << "Average Minimum is : " << min_total/min_cnt << std::endl;
    if(max_total != 0) std::cout << "Average Maximum is : " << max_total/max_cnt << std::endl;
}

void defineBook(std::istringstream &iss, std::vector<Books_data> &books)
{
    Books_data item;
    iss >> item.isbn;

    //check incorrect input
    if (item.isbn == 0 || item.isbn == -1){
        error_cmd();
        return;
    }

    auto found = Lookup(item.isbn,books);
    if(found == books.cend()){
        //ignore the white space
        iss.get();
        getline(iss,item.title);
        books.push_back(item);
    }
    else{
        std::cerr << "Error : Duplicate ISBN : " << item.isbn << std::endl;
    }

}

void defineBookChar(std::istringstream &iss, std::vector<Books_data> &books)
{

    long isbn_key;
    char code;
    std::string word;

    iss >> isbn_key >> code;
    if (isbn_key == 0){
        error_cmd();
        return;
    }

    //ignore the white space
    iss.get();
    getline(iss,word);

    auto found = Lookup(isbn_key,books);

    if(found != books.end()){
        switch (code){
            case 'A' : found->setAuthor(word); break;

            //conver string to int
            case 'E' : found->setEdition(stoi(word)); break;
            case 'D' : found->setPubDate(word); break;
            default  : error_cmd();
        }
    }
    else{
        std::cerr << "Error : The isbn is not in our database." << std::endl;
    }
}

void defineBookPrice(std::istringstream &iss, std::vector<Books_data> &books)
{

    long isbn_key = 0;
    char code;
    double price;

    iss >> isbn_key >> price >> code;

    if (isbn_key == 0){
        error_cmd();
        return;
    }

    auto found = Lookup(isbn_key,books);

    if(found != books.end()){
        switch (code){
            case 'N' : found->setNewPrice(price); break;
            case 'U' : found->setUsedPrice(price); break;
            case 'R' : found->setRentPrice(price); break;
            case 'E' : found->setEbookPrice(price); break;
            default  : error_cmd();
        }
    }
    else{
        std::cerr << "Error : The isbn is not in our database." << std::endl;
        return;
    }
}

std::ostream& printBookInfo(std::ostream &os, std::vector<Books_data>::const_iterator iter)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    os << "Book :" << std::endl;
    os << "  -  Isbn       : " << iter->getIsbn() << std::endl;
    os << "  -  Title      : " << iter->getTitle() << std::endl;

    if(iter->getAuthor() != ""){
        os << "  -  Author     : " << iter->getAuthor() << std::endl;
    }
    if(iter->getPubDate() != ""){
        os << "  -  Pub Date   : " << iter->getPubDate()<< std::endl;
    }
    if(iter->getEdition() != -1){
        os << "  -  Edition    : " << iter->getEdition() << std::endl;
    }
    if(iter->getNewPrice() != -1.0){
        os << "  -  New Price  : " << iter->getNewPrice() << std::endl;
    }
    if(iter->getUsedPrice() != -1.0){
        os << "  -  Used Price : " << iter->getUsedPrice() << std::endl;
    }
    if(iter->getRentPrice() != -1.0){
        os << "  -  Rent Price : " << iter->getRentPrice() << std::endl;
    }
    if(iter->getEbookPrice() != -1.0){
        os << "  -  eBook Price: " << iter->getEbookPrice() << std::endl;
    }
    return os;
}

std::ostream& printBookInfo(std::ostream &os, std::vector<Classes_data>::const_iterator iter)
{
    os << "\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    os << "Book :" << std::endl;
    os << "  -  Isbn       : " << iter->book.getIsbn() << std::endl;
    os << "  -  Title      : " << iter->book.getTitle() << std::endl;

    if(iter->book.getAuthor() != ""){
        os << "  -  Author     : " << iter->book.getAuthor() << std::endl;
    }
    if(iter->book.getPubDate() != ""){
        os << "  -  Pub Date   : " << iter->book.getPubDate()<< std::endl;
    }
    if(iter->book.getEdition() != -1){
        os << "  -  Edition    : " << iter->book.getEdition() << std::endl;
    }
    if(iter->book.getNewPrice() != -1.0){
        os << "  -  New Price  : " << iter->book.getNewPrice() << std::endl;
    }
    if(iter->book.getUsedPrice() != -1.0){
        os << "  -  Used Price : " << iter->book.getUsedPrice() << std::endl;
    }
    if(iter->book.getRentPrice() != -1.0){
        os << "  -  Rent Price : " << iter->book.getRentPrice() << std::endl;
    }
    if(iter->book.getEbookPrice() != -1.0){
        os << "  -  eBook Price: " << iter->book.getEbookPrice() << std::endl;
    }
    switch (iter->required){
        case 'R' : os << "  -  Choice     : Required\n"; break;
        case 'O' : os << "  -  Choice     : Optional\n"; break;
        default  : break;
    }
    return os;
}

double getLowest(const Books_data &item)
{
    // used negative indicate uninitialized price
    // so set it to a imposible value in order to find minimum

    double temp_new = 999999, temp_used = 999999, temp_rent = 999999, temp_ebook = 999999;

    if(item.getNewPrice()!= -1) temp_new = item.getNewPrice();
    if(item.getUsedPrice()!= -1) temp_used = item.getUsedPrice();
    if(item.getRentPrice()!= -1) temp_rent = item.getRentPrice();
    if(item.getEbookPrice()!= -1) temp_ebook = item.getEbookPrice();

    return Minimum(Minimum(temp_ebook,temp_new),Minimum(temp_rent,temp_used));
}

double getHighest(const Books_data &item)
{
    return Maximum(Maximum(item.getNewPrice(),item.getUsedPrice()),Maximum(item.getRentPrice(),item.getEbookPrice()));
}

inline double Minimum(const double &a, const double &b)
{
    return a<b ? a : b;
}

inline double Maximum(const double &a, const double &b)
{
    return a>b ? a : b;
}

int parseDate(const std::string &input)
{
    int month,year;
    //handle invalid date format
    if (std::sscanf(input.c_str(), "%d/%d", &month, &year) != 2){
        error_cmd();
        return -1;
    }
    else{
        //return YYYYMM
        return year*100 + month;
    }
}

void error_cmd()
{
    std::cerr << "Error : The command is malformed." << std::endl;
}

std::vector<Books_data>::iterator Lookup(long isbn_key, std::vector<Books_data> &books){

    auto item = std::find_if(books.begin(),books.end(),
                             [=](const Books_data a) {return a.getIsbn() == isbn_key;});
    return item;
}
/* Getter Functions */

long Books_data::getIsbn()const
{
    return isbn;
}
int Books_data::getEdition()const
{
    return edition;
}
double Books_data::getNewPrice()const
{
    return new_price;
}
double Books_data::getUsedPrice()const
{
    return used_price;
}
double Books_data::getRentPrice()const
{
    return rent_price;
}
double Books_data::getEbookPrice()const
{
    return ebook_price;
}
std::string Books_data::getTitle()const
{
    return title;
}
std::string Books_data::getPubDate()const
{
    return pub_date;
}
std::string Books_data::getAuthor()const
{
    return author;
}

/* Setter Functions */

void Books_data::setIsbn(long new_isbn)
{
    isbn = new_isbn;
}
void Books_data::setEdition(int new_edition)
{
    edition = new_edition;
}
void Books_data::setNewPrice(double price)
{
    new_price = price;
}
void Books_data::setUsedPrice(double price)
{
    used_price = price;
}
void Books_data::setRentPrice(double price)
{
    rent_price = price;
}
void Books_data::setEbookPrice(double price)
{
    ebook_price = price;
}
void Books_data::setTitle(std::string new_title)
{
    title = new_title;
}
void Books_data::setPubDate(std::string new_date)
{
    pub_date = new_date;
}
void Books_data::setAuthor(std::string new_author)
{
    author = new_author;
}