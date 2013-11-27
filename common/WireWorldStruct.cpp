#include <string>
#include <vector>
#include <stdio.h>

#include "WireWorldStruct.h"
#include "BaseStruct.h"
#include "Grid.h"
#include "constants.h"
#include "CustomException.h"

WireWorldStruct::WireWorldStruct() : BaseStruct( BaseStruct::WIREWORLD ) {
	Grid grid( this->getDefaultState() );
	this->setGrid( grid );
}

WireWorldStruct::WireWorldStruct( std::string name ) : BaseStruct( BaseStruct::WIREWORLD, name ) {
	Grid grid( this->getDefaultState() );
	this->setGrid( grid );
}

void WireWorldStruct::generateFile( FILE *ptr ){

	unsigned int index = 0;

	fprintf( ptr, "WireWorld = {\n");

	fprintf( ptr, "\tName = \"%s\";\n", this->getName().c_str() );

	fprintf( ptr, "\tTerrain = {\n");
	fprintf( ptr, "\t\tXrange = %d..%d;\n", this->getTerrain().xVals.getFirst(), this->getTerrain().xVals.getSecond() );
	fprintf( ptr, "\t\tYrange = %d..%d;\n", this->getTerrain().yVals.getFirst(), this->getTerrain().yVals.getSecond() );
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "\tWindow = {\n");
	fprintf( ptr, "\t\tXrange = %d..%d;\n", this->getWindow().xVals.getFirst(), this->getWindow().xVals.getSecond() );
	fprintf( ptr, "\t\tYrange = %d..%d;\n", this->getWindow().yVals.getFirst(), this->getWindow().yVals.getSecond() );
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "\tChars = {\n");
	fprintf( ptr, "\t\tEmpty = %d;\n", this->getChar( Grid::EMPTY ) );
	fprintf( ptr, "\t\tTail = %d;\n", this->getChar( Grid::ELECTRON_TAIL ) );
	fprintf( ptr, "\t\tHead = %d;\n", this->getChar( Grid::ELECTRON_HEAD ) );
	fprintf( ptr, "\t\tWire = %d;\n", this->getChar( Grid::WIRE ) );
	fprintf( ptr, "\t};\n");

	Color empty = this->getColor( Grid::EMPTY );
	Color head = this->getColor( Grid::ELECTRON_HEAD );
	Color tail = this->getColor( Grid::ELECTRON_TAIL );
	Color wire = this->getColor( Grid::WIRE );

	fprintf( ptr, "\tColors = {\n");
	fprintf( ptr, "\t\tEmpty = %s;\n", empty.toString().c_str() );
	fprintf( ptr, "\t\tHead = %s;\n", head.toString().c_str() );
	fprintf( ptr, "\t\tTail = %s;\n", tail.toString().c_str() );
	fprintf( ptr, "\t\tWire = %s;\n", wire.toString().c_str() );
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "\tInitial = {\n");
	std::vector< Point > vec = this->getGrid().getAllWithState( Grid::ELECTRON_HEAD );
	fprintf( ptr, "\t\tHead = ");
	for( index = 0; index < vec.size(); index++ ){
		fprintf( ptr, "%s", vec.at( index ).toString().c_str() );
		if( index < vec.size() - 1)
			fprintf( ptr, ",");
		else
			fprintf( ptr, ";");
	}
	fprintf( ptr, "\n");

	vec = this->getGrid().getAllWithState( Grid::ELECTRON_TAIL );
	fprintf( ptr, "\t\tTail = ");
	for( index = 0; index < vec.size(); index++ ){
		fprintf( ptr, "%s", vec.at( index ).toString().c_str() );
		if( index < vec.size() - 1)
			fprintf( ptr, ",");
		else
			fprintf( ptr, ";");
	}
	fprintf( ptr, "\n");
	
	vec = this->getGrid().getAllWithState( Grid::WIRE );
	fprintf( ptr, "\t\tWire = ");
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

BaseStruct* WireWorldStruct::duplicate(){
	WireWorldStruct *wire = new WireWorldStruct();

	wire->setName( this->getName() );
	wire->setGrid( this->getGrid() );
	wire->setColorMap( this->getColorMap() );
	wire->setCharMap( this->getCharMap() );
	wire->setTerrain( this->getTerrain() );
	wire->setWindow( this->getWindow() );
	wire->setWinDefined( this->isWinDefined() );

	return wire;
}

Grid::cell_state WireWorldStruct::getDefaultState(){
	return Grid::EMPTY;
}

void WireWorldStruct::simulateGenerations( int numGenerations, grid_dimension localTerrain ){

	BaseStruct::simulateGenerations( numGenerations, localTerrain );

	if( numGenerations < 0 ){
		throw new CustomException( CustomException::NEGATIVE_GENERATIONS );
	}

	Grid current = data;
	Grid past = data;

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
		current.reset( this->getDefaultState() );

		//Completed another generation of simulations
		currentGen++;	
	}

	data = past;
}

Grid::cell_state WireWorldStruct::getNextGeneration( Grid grid, Point loc, grid_dimension terrain){

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
	else{
		return this->getDefaultState();
	}
}
