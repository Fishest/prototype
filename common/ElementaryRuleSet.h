#ifndef ELEMENTARYRULESET_H
#define ELEMENTARYRULESET_H
#include <vector>

#include "BaseStruct.h"
#include "Grid.h"
#include "constants.h"
#include "iRuleSet.h"

class ElementaryRuleSet : public iRuleSet {

	public:
		ElementaryRuleSet();
		~ElementaryRuleSet();
		Grid simulateGenerations( BaseStruct *base, int numGenerations, grid_dimension terrain);

	private:
		Grid::cell_state getNextGeneration( Grid grid, Point loc, grid_dimension terrain);
		Grid::cell_state getCellWithTerrain( Grid grid, Point loc, grid_dimension terrain);
		std::vector< Gridd::cell_state > vec;

};
#endif
