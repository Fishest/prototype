#include <map>

#include "iRuleSet.h"
#include "constants.h"
#include "Grid.h"
#include "CustomException.h"
#include "LifeRuleSet.h"
#include "Point.h"

LifeRuleSet::LifeRuleSet(){
}

Grid::cell_state LifeRuleSet::calculateNewState( Grid data, Point pt, grid_dimension terrain ){

	int rowIndex = 0;
	int count = 0;

	/*
	   Scans the row directly above the given parameter.
	   */
	for( rowIndex = pt.getFirst() - 1; rowIndex <= pt.getFirst() + 1; rowIndex++ ){
		Point temp( rowIndex, pt.getSecond() - 1 );
		if( data.get( temp ) == Grid::ALIVE && temp.getFirst() >= terrain.xVals.getFirst() &&
				temp.getFirst() <= terrain.xVals.getSecond() && temp.getSecond() >= terrain.yVals.getFirst() &&
					temp.getSecond() <= terrain.yVals.getSecond() ){
			count++;
		}
	}

	//Scans the row directly below the given parameter.
	for( rowIndex = pt.getFirst() - 1; rowIndex <= pt.getFirst() + 1; rowIndex++ ){
		Point temp( rowIndex, pt.getSecond() + 1 );
		if( data.get( temp ) == Grid::ALIVE && temp.getFirst() >= terrain.xVals.getFirst() &&
				temp.getFirst() <= terrain.xVals.getSecond() && temp.getSecond() >= terrain.yVals.getFirst() &&
					temp.getSecond() <= terrain.yVals.getSecond() ){
			count++;
		}
	}

	//Checks cell to the left of the given point.
	Point temp( pt.getFirst() - 1, pt.getSecond() );
	if( data.get( temp ) == Grid::ALIVE && temp.getFirst() >= terrain.xVals.getFirst() &&
			temp.getFirst() <= terrain.xVals.getSecond() && temp.getSecond() >= terrain.yVals.getFirst() &&
				temp.getSecond() <= terrain.yVals.getSecond() ){
		count++;
	}

	//Checks cell to the left of the given point.
	Point temp1( pt.getFirst() + 1, pt.getSecond() );
	if( data.get( temp1 ) == Grid::ALIVE && temp1.getFirst() >= terrain.xVals.getFirst() &&
			temp1.getFirst() <= terrain.xVals.getSecond() && temp1.getSecond() >= terrain.yVals.getFirst() &&
				temp1.getSecond() <= terrain.yVals.getSecond() ){
		count++;
	}

	if( data.get( pt ) == Grid::ALIVE ){
		if( count < 2 )
			return Grid::DEAD;
		if( count == 2 || count == 3 )
			return Grid::ALIVE;
		else
			return Grid::DEAD;
	}
	else{

		if( count == 3 )
			return Grid::ALIVE;
		else
			return Grid::DEAD;
	}
}

Grid LifeRuleSet::simulateGenerations( Grid live, int numGenerations, grid_dimension terrain){
	Grid current = live;
	Grid past = live;

	if( numGenerations < 0 ){
		throw new CustomException( CustomException::NEGATIVE_GENERATIONS );
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

				Point temp( colIndex, rowIndex);
				Grid::cell_state newState = calculateNewState( past, temp, terrain);

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

