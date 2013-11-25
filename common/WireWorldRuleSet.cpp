#include "Grid.h"
#include "WireWorldRuleSet.h"
#include "constants.h"
#include "BaseStruct.h"

WireWorldRuleSet::WireWorldRuleSet(){
}

WireWorldRuleSet::~WireWorldRuleSet(){
}

Grid WireWorldRuleSet::simulateGenerations( BaseStruct *base, int numGenerations, grid_dimension terrain){

	if( numGenerations < 0 ){
		throw new CustomException( CustomException::NEGATIVE_GENERATIONS );
	}
	Grid current = base->getGrid();
	Grid past = base->getGrid();

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

Grid::cell_state WireWorldRuleSet::getNextGeneration( Grid grid, Point loc, grid_dimension terrain){

	int rowIndex = 0;
	int colIndex = 0;

	Grid::cell_state current = grid.get( loc );
	if( current == Grid::EMPTY ){
		return Grid::EMPTY;
	}
	else if( current == Grid::ELECTRON_HEAD ){
		return Grid::ELECTRON_TAIL;
	}
	else if( current == Grid::ELECTRON_TAIL ){
		return Grid::WIRE;
	}
	else if( current == Grid::WIRE )
	{
		int count = Grid::countCells( grid, Grid::ELECTRON_HEAD, terrain, loc );
		if( count == 1 || count == 2 )
			return Grid::ELECTRON_HEAD;
		else
			return Grid::WIRE;
	}
		
}
