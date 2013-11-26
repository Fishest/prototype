#include <string>

#include "BaseStruct.h"
#include "Grid.h"
#include "iRuleSet.h"
#include "ElementaryStruct.h"

ElementaryStruct::ElementaryStruct() : BaseStruct( BaseStruct::ELEMENTARY ){
	Grid grid( Grid::ZERO );
	this->setGrid( grid );
	rule = 0;
	vec();
}

ElementaryStruct::ElementaryStruct( std::string name ) : BaseStruct( BaseStruct::ELEMENTARY, name){
	Grid grid( Grid::ZERO );
	this->setGrid( grid );
	rule = 0;
	vec();
}

void ElementaryStruct::generateFile( FILE *ptr ){

	fprintf( ptr, "Elementary = {\n");
	fprintf( ptr, "\tName=\"%s\";\n", this->getName().c_str() );
	fprintf( ptr, "\tRule=%d;\n", this->getRule() );

	fprintf( ptr, "\tTerrain = {\n");
	fprintf( ptr, "\t\tXrange = %d..%d;\n", this->getTerrain().xVals.getFirst(), this->getTerrain().xVals.getSecond() );
	fprintf( ptr, "\t\tYrange = %d..%d;\n", this->getTerrain().yVals.getFirst(), this->getTerrain().yVals.getSecond() );
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "\tWindow = {\n");
	fprintf( ptr, "\t\tXrange = %d..%d;\n", this->getWindow().xVals.getFirst(), this->getWindow().xVals.getSecond() );
	fprintf( ptr, "\t\tYrange = %d..%d;\n", this->getWindow().yVals.getFirst(), this->getWindow().yVals.getSecond() );
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "\tChars = {\n");
	fprintf( ptr, "\t\tZero = %d;\n", this->getChar( Grid::ZERO ) );
	fprintf( ptr, "\t\tOne = %d;\n", this->getChar( Grid::ONE ) );
	fprintf( ptr, "\t};\n");

	Color zero = this->getColor( Grid::ZERO );
	Color one = this->getColor( Grid::ONE );
	fprintf( ptr, "\tColors = {\n");
	fprintf( ptr, "\t\tZero = %s;\n", zero.toString().c_str() );
	fprintf( ptr, "\t\tOne = %s;\n", one.toString().c_str() );
	fprintf( ptr, "\t};\n");

	std::vector< Point > vec = this->getGrid().getAllWithState( Grid::ONE );
	fprintf( ptr, "\tInitial = {\n");
	fprintf( ptr, "\t\tOne = ");
	for( index = 0; index < vec.size(); index++ ){
		fprintf( ptr, "%s", vec.at( index ).toString().c_str() );
		if( index < vec.size() - 1)
			fprintf( ptr, ",");
		else
			fprintf( ptr, ";");
	}
	fprintf( ptr, "\n");
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "};\n");
}

BaseStruct* ElementaryStruct::duplicate(){
	ElementaryStruct *ele = new ElementaryStruct();

	ele->setName( this->getName() );
	ele->setGrid( this->getGrid() );
	ele->setColorMap( this->getColorMap() );
	ele->setCharMap( this->getCharMap() );
	ele->setWindow( this->getWindow() );
	ele->setTerrain( this->getTerrain() );
	ele->setWinDefined( this->isWinDefined() );

	return (BaseStruct*)ele;
}

int ElementaryStruct::getRule(){
	return rule;
}

void ElementaryStruct::setRule( int value ){
	rule = value;
}

Grid::cell_state ElementaryStruct::getDefaultState(){
	return Grid::ZERO;
}

void ElementaryStruct::simulateGenerations( int numGenerations, grid_dimension localTerrain ) {

	//Call the super classes implementation of the function before extending its functionality
	BaseStruct::simulateGenerations( numGenerations, localTerrain );

	if( numGenerations < 0 ){
		throw new CustomException( CustomException::NEGATIVE_GENERATIONS );
	}
	Grid current = data;
	Grid past = data;

	if( base->getType() != BaseStruct::ELEMENTARY ){
		throw new CustomException( CustomException::INVALID_TYPE_FOR_SIMULATION );
	}

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

		for( rowIndex = localTerrain.yVals.getFirst(); rowIndex <= localTerrain.yVals.getSecond(); rowIndex++ ){

			for( colIndex = localTerrain.xVals.getFirst(); colIndex <= localTerrain.xVals.getSecond(); colIndex++ ){

				/*
				   For each cell in the terrain, the new state of that cell needs to be calculated.
				   */
				Point temp( colIndex, rowIndex);
				Grid::cell_state newState = getNextGeneration( past, temp, localTerrain);

				//Updates the state with the currently processing cell.
				current.set( temp, newState );
			}
		}

		//Updates the reading table
		past = current;

		//Clears the current board so that it can be filled again.
		current.reset( this->getDefault() );

		//Completed another generation of simulations
		currentGen++;	
	}

	//Update the internal working version of the Grid
	data = past;
}

Grid::cell_state ElementaryStruct::getNextGeneration( Grid grid, Point loc, grid_dimension terrain){

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

Grid::cell_state ElementaryStruct::getCellWithTerrain( Grid grid, Point loc, grid_dimension terrain){

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