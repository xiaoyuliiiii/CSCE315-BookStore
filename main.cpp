/*****************************************************************************
 * Developer: Xiaoyu Li
 * Project: CSCE-315 Individual Assignment
 *
 * File: ./IA1/main.cpp
 *****************************************************************************/

/*****************************************************************************
 * Standard Library Includes
 *****************************************************************************/



/*****************************************************************************
 * User Defined Includes
 *****************************************************************************/
#include "books_data.h"
#include "courses_data.h"

int main()
{
    std::vector<Books_data> books;
    std::vector<Courses_data> courses;
    std::vector<Classes_data> classes;

    Books_data book;
    Courses_data course;
    Classes_data my_class;

    std::cout << "\nEnter 'quit' to quit the program! " << std::endl;
    std::string line;

    while(getline(std::cin,line)){
        try{
            if(line == "quit") break;
            if(line == "") throw std::runtime_error("`\\n` (newline) detected.");
            std::string code;
            std::istringstream scan(line);
            scan >> code;

            switch(code.at(0)){
                case 'B' : defineBook(scan,books); break;
                case 'D' : defineBookChar(scan,books); break;
                case 'M' : defineBookPrice(scan,books); break;
                case 'C' : defineCourse(scan,courses); break;
                case 'A' : assignBook(scan,books,courses,classes); break;
                case 'G' :
                    if(code == "GB") printBook(scan,books);
                    else if(code == "GS")printBookSECTION(scan,classes);
                    else if (code == "GC") printBookCOURSE(scan,classes);
                    else error_cmd();
                    break;
                case 'P' :
                    if(code == "PB") printBookALL(books);
                    else if(code =="PC") printCourseALL(courses);
                    else if(code == "PY") printBookYEAR(scan,books);
                    else if (code == "PD") printBookDEPT(scan,classes);
                    else if (code == "PM") printBookAVG(scan,classes);
                    else error_cmd();

                    break;
                default  :
                    error_cmd();
                    break;
            }
        } catch (std::runtime_error err){
            std::cout << err.what()
                      << "\nTry again ? Enter y or n " << std::endl;
            char c;
            std::cin >> c;
            if (!std::cin || c == 'n') break;
            //ingore '/n'
            std::cin.get();
        }
    }
//
//    for(const auto c : classes){
//        printClass(std::cout,c);
//    }
}