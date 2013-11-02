#include <string>
#include <stdio.h>
#include <string.h>

#include "Point.h"

Point::Point(){
    firstValue = 0;
    secondValue = 0;
}

Point::Point(int val1, int val2){
    firstValue = val1;
    secondValue = val2;
}

int Point::getFirst() const{
    return firstValue;
}

int Point::getSecond() const{
    return secondValue;
}

void Point::setFirst(int value){
    firstValue = value;
}

void Point::setSecond(int value){
    secondValue = value;
}

void Point::reset(){
    firstValue = 0;
    secondValue = 0;
}

std::string Point::toString(){    
    char temp[ 100 ];
    bzero( temp, 100);
    
    sprintf( temp, "( %d, %d)", firstValue, secondValue );
    std::string ret( temp );
    return ret;
}
