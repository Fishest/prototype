#ifndef VISUALS_H
#define VISUALS_H

#include <map>

#include "Grid.h"
#include "constants.h"
#include "BaseStruct.h"

class Visuals {

public:

	virtual void visualize( BaseStruct* base ) = 0;

};

#endif