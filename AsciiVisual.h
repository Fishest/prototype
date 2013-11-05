#ifndef ASCIIVISUAL_H
#define ASCIIVISUAL_H

#include "Grid.h"
#include "constants.h"
#include "visuals.h"
#include "BaseStruct.h"
#include "LifeStruct.h"

class AsciiVisual : public Visuals {

public:

	AsciiVisual();
	void visualize( BaseStruct* base );

};

#endif