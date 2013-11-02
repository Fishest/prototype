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

    Point();
    Point(int val1, int val2);

    int getFirst() const;
    int getSecond() const;
    
    void setFirst( int value );
    void setSecond( int value );
  
    void reset();
    std::string toString();

private:

    int firstValue;
    int secondValue;

};

inline bool operator< (const Point& a, const Point& b){
        if( a.getFirst() < b.getFirst() ){
            return true;
        }
        else if( a.getFirst() > b.getFirst() ){
            return false;
        }
        
        if( a.getSecond() < b.getSecond() ){
            return true;
        }
        else if( a.getSecond() > b.getSecond() ){
            return false;
        }
        
        return false;
    }

#endif	/* POINT_H */

