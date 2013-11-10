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

 /**
  * Holds the bounds that are used to represent the terrain
  * and window dimensions.
  */
struct grid_dimension {
    Point xVals;
    Point yVals;
};

#endif	/* CONSTANTS_H */

