#include <string>
#include <vector>

#include "WireWorldStruct.h"
#include "BaseStruct.h"
#include "Grid.h"

WireWorldStruct::WireWorldStruct() : BaseStruct( BaseStruct::WIREWORLD ) {
	Grid grid( this->getDefaultState() );
	this->setGrid( grid );
}

WireWorldStruct( std::string name ) : BaseStruct( BaseStruct::WIREWORLD, name ) {
	Grid grid( this->getDefaultState() );
	this->setGrid( grid );
}

void generateFile( FILE *ptr ){

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
	fprintf( ptr, "\t\tTail = ");
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

BaseStruct* duplicate(){
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

Grid::cell_state getDefaultState(){
	return Grid::EMPTY;
}

iRuleSet* WireWorldStruct::getDefaultRuleSet(){
	WireWorldRuleSet* wire = new WireWorldRuleSet();
	return (*iRuleSet)wire;
}
