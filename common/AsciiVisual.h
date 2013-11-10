#ifndef ASCIIVISUAL_H
#define ASCIIVISUAL_H

#include "Grid.h"
#include "constants.h"
#include "visuals.h"
#include "BaseStruct.h"
#include "LifeStruct.h"

/**
 * The class provides the visual functionality for the Life structures. It implements
 * the Visuals interface to allow for quick and efficient switching from visualization
 * methods.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class AsciiVisual : public Visuals {

public:

	AsciiVisual();

	/**
	 * Function takes care of visualizing the BaseStruct that is presented as a parameter.
	 * By using the visualization interface, it becomes easy to switch between visualization methods
	 * as the call to the visualize will be handled by whatever class has extended the interface.
	 *
	 * @param base Pointer to the BaseStruct that should be visualized to the screen.
	 */
	void visualize( BaseStruct* base );

};

#endif