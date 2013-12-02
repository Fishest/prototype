#ifndef ELEMENTARYSTRUCT_H
#define ELEMENTARYSTRUCT_H

#include <string>

#include "BaseStruct.h"
#include "Grid.h"
#include "constants.h"

/**
 * The ElementaryStruct is a extension of the BaseStruct class that is specific to the Elementary rule set and
 * input structure. The ElementaryStruct follows specific rules as far as how to progress through to the next
 * generation of the simulation. It also requires the use of different cell states that the other structs and
 * thus needs a separate implementation for a few of the functions.
 *
 * @author Cameron Whipple
 * @date December 1, 2013
 */
class ElementaryStruct : public BaseStruct {

	public:

		ElementaryStruct();
		ElementaryStruct( std::string name );

		/**
		 * Implementation of the BaseStructs function that handles the exporting of the structs state to
		 * a file that is compatible with Appendix A in the project write-up.
		 *
		 * @param ptr File to which the content should be sent.
		 */
		void generateFile( FILE *ptr );

		/**
		 * Provides a duplicate of this struct on the heap.
		 *
		 * @return Returns an exact duplicate of this struct on the heap
		 */
		BaseStruct* duplicate();

		/**
		 * Returns the default state for the ElementaryStruct grid and ruleset.
		 *
		 * @return The default state for the cells.
		 */
		Grid::cell_state getDefaultState();

		/**
		 * Implementation of BaseStruct's simulateGenerations that has been crafted specifically
		 * to handle the ElementaryStruct rules and states.
		 *
		 * @param numGenerations Number of generations to move the simulation forward.
		 * @param localTerrain The terrain bounds to use for performing the progressions.
		 */
		void simulateGenerations( int numGenerations, grid_dimension localTerrain  );

		/**
		 * Obtains the current rule being used to progress the ElementaryStruct generations.
		 *
		 * @return The rule being used for generation progression.
		 */
		int getRule();

		/**
		 * Sets the rule that will be used for progressing the ElementaryStruct generations.
		 * 
		 * @param value The new value for the rule.
		 */
		void setRule( int value );

	private:
		int rule;

		/**
		 * This function handles the determination of a given cells state in the next generation. This function
		 * is used internally to map generations N location to the state for generation N+1.
		 *
		 * @param grid The state of the grid at state N
		 * @param loc The location in the grid that needs to be updated.
		 * @param terrain The terrain being used in the progression of the generations.
		 */
		Grid::cell_state getNextGeneration( Grid grid, Point loc, grid_dimension terrain);

		/**
		 * This function will pull the state of the cell from a given location during the current
		 * generation. While pulling the value, this function takes the terrain into account prior to pulling
		 * the cells state for generation N.
		 *
		 * @param grid The state of the grid at state N
		 * @param loc The location in the grid that needs to be updated.
		 * @param terrain The terrain being used in the progression of the generations.
		 */
		Grid::cell_state getCellWithTerrain( Grid grid, Point loc, grid_dimension terrain);
		std::vector< Grid::cell_state > vec;

};


#endif
