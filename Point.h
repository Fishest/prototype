/* 
 * File:   Point.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:40 PM
 */

#ifndef POINT_H
#define	POINT_H

#include <string>

class Point {
public:

    Point(int val1, int val2);

    int getFirst();
    int getSecond();
    
    void reset();
    std::string toString();

private:

    int firstValue;
    int secondValue;

};

#endif	/* POINT_H */

