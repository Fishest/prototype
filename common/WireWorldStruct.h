#ifndef WIREWORLDSTRUCT_H
#define WIREWORLDSTRUCT_H

#include <string>

#include "BaseStruct.h"

class WireWorldStruct : public BaseStruct {

	public:

		WireWorldStruct();
		WireWorldStruct( std::string name );

		void generateFile( FILE *ptr );
		BaseStruct* duplicate();
		Grid::cell_state getDefaultState();

		void simulateGenerations( int numGenerations, grid_dimension localTerrain );

	private:

		Grid::cell_state getNextGeneration( Grid grid, Point loc, grid_dimension terrain);

};

#endif
