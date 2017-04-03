/*****************************************************************************
 * Developer: Xiaoyu Li
 * Project: CSCE-315 Individual Assignment
 *
 * File: ./IA1/courses_data.h
 *****************************************************************************/

#ifndef _COURSES_DATA_H
#define _COURSES_DATA_H

/*****************************************************************************
 * User Defined Includes
 *****************************************************************************/
#include "books_data.h"

class Courses_data
{
friend void defineCourse(std::istringstream&, std::vector<Courses_data>&);

private:
    int course_num;
    std::string dept_code;
    std::string course_name;

public:
    Courses_data();

    int getCourseNum() const;
    std::string getDeptCode() const;
    std::string getCourseName() const;
};


struct Classes_data
{
    int section;
    char required;
    Books_data book;
    Courses_data course;
};

// Print a list of all courses that are defined
void printCourseALL(std::vector<Courses_data>&);

// Define a course
void defineCourse(std::istringstream&, std::vector<Courses_data>&);

// Assign a book to a class
void assignBook(std::istringstream&, std::vector<Books_data>&, std::vector<Courses_data>&, std::vector<Classes_data>&);

// Formatted output for a give course
std::ostream& printCourseInfo(std::ostream&, std::vector<Courses_data>::const_iterator);
std::ostream& printClassInfo(std::ostream&, std::vector<Classes_data>::const_iterator);
#endif
