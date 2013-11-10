#ifndef VISUALS_H
#define VISUALS_H

#include "BaseStruct.h"

/**
 * Interface that is used throughout the application to allow for visualizing the content
 * within the BaseStruct.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class Visuals {

public:

	/**
	 * Function that must be implemented in any class that extends a Visuals interface. The
	 * function will handle the displaying of the contents from the BaseStruct.
	 *
	 * @param base Pointer to the struct that should be displayed.
	 */
	virtual void visualize( BaseStruct* base ) = 0;

};

#endif
