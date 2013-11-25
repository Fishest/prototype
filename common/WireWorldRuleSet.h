#ifndef WIREWORLDRULES_H
#define WIREWORLDRULES_H

#include "Grid.h"
#include "iRuleSet.h"
#include "constants.h"
#include "BaseStruct.h"

class WireWorldRuleSet : public iRuleSet{

	public:
		WireWorldRuleSet();
		~WireWorldRuleSet();
		Grid simulateGenerations( BaseStruct *base, int numGenerations, grid_dimension terrain);
	private:

		Grid::cell_state getNextGeneration( Grid grid, Point loc, grid_dimension terrain);

};


#endif
