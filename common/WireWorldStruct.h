#ifndef WIREWORLDSTRUCT_H
#define WIREWORLDSTRUCT_H

#include <string>

#include "BaseStruct.h"

/**
 * The WireWorldStruct is an extension of the BaseStruct class for the Game of Life simulations. The WireWorldStruct is 
 * a different type of possible simulation that can be performed through the context of the Game of Life simulations. It
 * has it's own specific rules for progressing the simulations generations.
 *
 * @author Cameron Whipple
 * @date December 1, 2013
 */
class WireWorldStruct : public BaseStruct {

	public:

		WireWorldStruct();
		WireWorldStruct( std::string name );

		/**
		 * Implements the function that will handle the file creation, consisten with Appendix A, for the WireWorldStruct's.
		 * 
		 * @param ptr File to which the content should be written.
		 */
		void generateFile( FILE *ptr );

		/**
		 * Provides exact duplicate of the struct. Caller assumes responsibility for the memory.
		 *
		 * @return Point to the struct.
		 */
		BaseStruct* duplicate();

		/**
		 * Gets the default cell state for this particular struct type.
		 *
		 * @return The state that should be regarded as default.
		 */
		Grid::cell_state getDefaultState();

		/**
		 * Progresses the simulation of the struct forward by the specified number of generations.
		 *
		 * @param numgenerations Number of generations to progress.
		 * @param localTerrain The terrain to be used for this progression.
		 */
		void simulateGenerations( int numGenerations, grid_dimension localTerrain );

	private:

		/**
		 * Calculates the next state for the specified cell location.
		 *
		 * @param grid The current grid to be read from.
		 * @param loc The location within the grid to update.
		 * @param terrain The terrain to be used when performing this calculation.
		 * @return The state of the cell for generation N+1.
		 */
		Grid::cell_state getNextGeneration( Grid grid, Point loc, grid_dimension terrain);

};

#endif
