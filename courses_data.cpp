/*****************************************************************************
 * Developer: Xiaoyu Li
 * Project: CSCE-315 Individual Assignment
 *
 * File: ./IA1/courses_data.cpp
 *****************************************************************************/


/*****************************************************************************
 * User Defined Includes
 *****************************************************************************/
#include "courses_data.h"

Courses_data::Courses_data()
{
    dept_code = "";
    course_num = -1;
    course_name = "";
}

void printCourseALL(std::vector<Courses_data> &courses)
{
    for(auto beg = courses.cbegin(); beg != courses.cend(); beg++){
        printCourseInfo(std::cout,beg);
    }
    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";

}

void defineCourse(std::istringstream &iss, std::vector<Courses_data> &courses)
{
    Courses_data item;

    iss >> item.dept_code >> item.course_num;

    if (item.dept_code == ""){
        error_cmd();
        return;
    }
    //ignore the white space
    iss.get();
    getline(iss,item.course_name);

    courses.push_back(item);
}

void assignBook(std::istringstream &iss, std::vector<Books_data> &books, std::vector<Courses_data> &courses, std::vector<Classes_data> &classes)
{
    Classes_data item;
    long isbn_key;
    int course_key;
    std::string dept_key;

    iss >> isbn_key >> dept_key >> course_key;

    if (isbn_key == 0 || isbn_key == -1){
        error_cmd();
        return;
    }

    //check isbn_key is valid
    auto is_valid_isbn = std::find_if(books.begin(),books.end(),
                             [&](const Books_data a) {return a.getIsbn() == isbn_key;});
    //check course info is valid
    auto is_valid_course = std::find_if(courses.begin(),courses.end(),
         [&](const Courses_data c) {return c.getDeptCode() == dept_key && c.getCourseNum() == course_key;});

    if(is_valid_isbn != books.end() && is_valid_course != courses.end()){
        item.book = *is_valid_isbn;
        item.course = *is_valid_course;
        iss >> item.section >> item.required;
    }
    else{
        std::cerr << "Error : The isbn or department code is not in our database." << std::endl;
        return;
    }
    classes.push_back(item);
}

std::ostream& printCourseInfo(std::ostream &os, std::vector<Courses_data>::const_iterator iter)
{
    os << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
    os << "Course :" << std::endl;
    os << "  -  Name    : " << iter->getCourseName() << std::endl;
    os << "  -  Dept    : " << iter->getDeptCode() << std::endl;
    os << "  -  Number  : " << iter->getCourseNum() << std::endl;
    return os;
}

std::ostream& printClassInfo(std::ostream &os, std::vector<Classes_data>::const_iterator iter)
{
    os << "  -  Section    : " << iter->section << std::endl;
    return os;
}

std::string Courses_data::getDeptCode() const
{
    return dept_code;
}

std::string Courses_data::getCourseName() const
{
    return course_name;
}

int Courses_data::getCourseNum() const
{
    return course_num;
}
