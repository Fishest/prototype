#ifndef LIFERULESET_H
#define LIFERULESET_H

#include "constants.h"
#include "Grid.h"
#include "Point.h"
#include "iRuleSet.h"

class LifeRuleSet : public iRuleSet {

	public:
		LifeRuleSet();
		virtual Grid simulateGenerations( Grid live, int numGenerations, grid_dimension terrain);

	private:
		Grid::cell_state calculateNewState( Grid data, Point pt, grid_dimension terrain );
};

#endif
