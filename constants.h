/* 
 * File:   constants.h
 * Author: cameron
 *
 * Created on October 28, 2013, 9:59 PM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#include "Color.h"
#include "Point.h"

struct color_case {
    Color alive;
    Color dead;
};

struct grid_dimension {
    Point xVals;
    Point yVals;
};



#endif	/* CONSTANTS_H */

