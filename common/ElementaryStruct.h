#ifndef ELEMENTARYSTRUCT_H
#define ELEMENTARYSTRUCT_H

#include <string>

#include "BaseStruct.h"
#include "Grid.h"
#include "iRuleSet.h"

class ElementaryStruct : public BaseStruct {

	public:

		ElementaryStruct();
		ElementaryStruct( std::string name );

		void generateFile( FILE *ptr );
		BaseStruct* duplicate();
		Grid::cell_state getDefaultState();
		void simulateGenerations( int numGenerations, grid_dimension localTerrain  );

		int getRule();
		void setRule( int value );

	private:
		int rule;

		Grid::cell_state getNextGeneration( Grid grid, Point loc, grid_dimension terrain);
		Grid::cell_state getCellWithTerrain( Grid grid, Point loc, grid_dimension terrain);
		std::vector< Gridd::cell_state > vec;

};


#endif
