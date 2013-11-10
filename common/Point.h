#ifndef POINT_H
#define	POINT_H

#include <string>

/**
 * The Point class stores two integer numbers. Primarily used to identifying a location
 * within the Grid.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class Point {
public:

    Point();
    Point(int val1, int val2);

	/**
	 * Retrieves the first value, or X coordinate, from the Point oject.
	 *
	 * @return The value stored at the first element.
	 */
    int getFirst() const;

	/**
	 * Retrieves the second value, or Y coordinate, from the Point object.
	 *
	 * @return The value stored at the second element.
	 */
    int getSecond() const;
   
	/**
	 * Alters the value that is stored in the first element.
	 *
	 * @param value The new value to be stored.
	 */
    void setFirst( int value );

	/**
	 * Alters the value that is stored in the second element.
	 *
	 * @param value The new value to be stored.
	 */
    void setSecond( int value );
 
	/**
	 * Resets the values stored in this Point. The first and second elements
	 * will be reset to zero.
	 */
    void reset();

	/**
	 * Exports the elements of the object as a Point that is compatible with the
	 * specification provided for part1 in regards to configuration file.
	 *
	 * @return String representation of the point, assuming being used to locate cell in Grid.
	 */
    std::string toString();

private:

    int firstValue;
    int secondValue;

};

/**
 * Defines what is means for a point to be less than another point value. This is defined
 * so that the map structure is able to properly use a point as a Key.
 *
 * @param a Constant reference to a point.
 * @param b Constant reference to a Point.
 * @return True if A is less than B, false otherwise.
 */
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

