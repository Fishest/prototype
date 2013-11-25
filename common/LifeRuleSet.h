#ifndef LIFERULESET_H
#define LIFERULESET_H

#include "constants.h"
#include "Grid.h"
#include "Point.h"
#include "iRuleSet.h"
#include "BaseStruct.h"

/**
 * Implementation of the iRuleSet interface that corresponds to the Life struct rules as defined in
 * the first part of the project. This class contains the code for transforming a Grid through the
 * different generations using the Life struct rules.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class LifeRuleSet : public iRuleSet {

	public:
		LifeRuleSet();

		/**
		 * Transforms the provided Grid to numGenerations in the future based on the rules defined
		 * for the life struct.
		 *
		 * @param live The starting Grid state.
		 * @param numGenerations Number of generations to progress
		 * @param terrain The terrain of the Grid that should be processed
		 * @return the updated version of the Grid
		 */
		virtual Grid simulateGenerations( BaseStruct *base, int numGenerations, grid_dimension terrain);

	private:

		/*
		 * When provided with a Grid and a point in that Grid, this function will calculate
		 * the next state for that given cell. This transformation is based entirely off the
		 * rules defined in the project writeup.
		 *
		 * @param data The Grid that contains data for generation N.
		 * @param pt The cell within the Grid to be transformed to the next generation.
		 * @param terrain The dimension of the points that need to be transformed.
		 */
		Grid::cell_state calculateNewState( Grid data, Point pt, grid_dimension terrain );
};

#endif
