#include "ElementaryRuleSet.h"
#include "Grid.h"
#include "constants.h"
#include "BaseStruct.h"

ElementaryRuleSet::ElementaryRuleSet(){
	vec();
}

ElementaryRuleSet::~ElementaryRuleSet(){
}

Grid ElementaryRuleSet::simulateGenerations( BaseStruct *base, int numGenerations, grid_dimension terrain){

	if( numGenerations < 0 ){
		throw new CustomException( CustomException::NEGATIVE_GENERATIONS );
	}
	Grid current = base->getGrid();
	Grid past = base->getGrid();

	if( base->getType() != BaseStruct::ELEMENTARY ){
		throw new CustomException( CustomException::INVALID_TYPE_FOR_SIMULATION );
	}

	//Correct the type of the struct that was provided.
	ElementaryStruct *el = (ElementaryStruct*)base;

	int rule = el->getRule();
	if( rule < 0 || rule >= 512 ){
		throw new CustomException( CustomException::INVALID_RULE_VALUE );
	}

	/*
	   Builds a vector that corresponds to the bits of the provided rule. Once this is 
	   built, all that needs to be done is to treat the bits above the current location
	   as a integer index value into this vector to determine the next state.
	   */
	int index = 0;
	int mask = 0x01;
	for( index=0; index < 8; index++){
		if( rule & mask != 0 ){
			vec.push_back( Grid::ONE );
		}
		else{
			vec.push_back( Grid::ZERO );
		}
		mask = mask << 1;
	}

	int currentGen = 0;
	int rowIndex = 0;
	int colIndex = 0;

	/*
	 * Runs through the specified number of generations. Each run through this loop corresponds to a
	 * generation being simulated.
	 */
	while( currentGen < numGenerations ){

		for( rowIndex = terrain.yVals.getFirst(); rowIndex <= terrain.yVals.getSecond(); rowIndex++ ){

			for( colIndex = terrain.xVals.getFirst(); colIndex <= terrain.xVals.getSecond(); colIndex++ ){

				/*
				   For each cell in the terrain, the new state of that cell needs to be calculated.
				   */
				Point temp( colIndex, rowIndex);
				Grid::cell_state newState = getNextGeneration( past, temp, terrain);

				//Updates the state with the currently processing cell.
				current.set( temp, newState );
			}
		}

		//Updates the reading table
		past = current;

		//Clears the current board so that it can be filled again.
		current.reset( live.getDefault() );

		//Completed another generation of simulations
		currentGen++;	
	}

	return past;
}

Grid::cell_state ElementaryRuleSet::getNextGeneration( Grid grid, Point loc, grid_dimension terrain){

	Grid::cell_state state = grid.get( loc );
	if( state == Grid::ONE ){
		return Grid::ONE;
	}

	/*
	 * In the event that this rule set is applied to a Grid that was loaded for a separate
	 * struct type.
	 */
	if( state != GRID::ZERO ){
		return state;
	}

	int builtIndex = 0;

	//Set the most significant bit if the left bit above is a 1.
	Point loc1 = loc;
	loc1.setFirst( loc1.getFirst() - 1);
	loc1.setSecond( loc1.getSecond() + 1);
	Grid::cell_state val = getCellWithTerrain( grid, loc1, terrain);
	if( val == Grid::ONE ){
		builtIndex = 0x04;
	}

	//Set the middle bit if the one directly above is a 1
	loc1.setFirst( loc.getFirst() );
	val = getCellWithTerrain( grid, loc1, terrain );
	if( val == Grid::ONE ){
		builtIndex = builtIndex & 0x02;
	}

	//Set the LSB if the cell to the right, above, is a 1
	loc1.setFirst( loc.getFirst() + 1 );
	val = getCellWithTerrain( grid, loc1, terrain );
	if( val == Grid::ONE ){
		builtIndex = builtIndex & 0x01;
	}

	return vec.at( builtIndex );

}

Grid::cell_state ElementaryRuleSet::getCellWithTerrain( Grid grid, Point loc, grid_dimension terrain){

	//Invalid X coordinate was provided with the terrain. Just return the default value.
	if( loc.getFirst() < terrain.xVals.getFirst() || loc.getFirst() > terrain.xVals.getSecond() ){
		return grid.getDefault();
	}

	//Invalid Y coordinate was provided with the terrain. Just return the default value.
	if( loc.getSecond() < terrain.yVals.getFirst() || loc.getSecond() > terrain.yVals.getSecond() ){
		return grid.getDefault();
	}

	return grid.get( loc );
}





