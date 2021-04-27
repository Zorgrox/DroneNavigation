#ifndef DATE_H
#define DATE_H

#include "Debug.h"
#include "Exceptions.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;
class Date {
public:
    Date() ;
    Date(int, int, int) ;
    ~Date() ;

    std::string show() const ;

    bool equals(const Date &) const ;

    bool before(const Date &) const ;

    void day_inc(int) ;

    Date copy() const ;

private:
    int year, month, day ;
};





















Date mkDate(int y, int m, int d) ;
Date * mkDate_ptr(int y, int m, int d) ;

#endif
