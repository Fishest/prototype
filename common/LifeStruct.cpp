#include <string>
#include <stdio.h>

#include "LifeStruct.h"

LifeStruct::LifeStruct() : BaseStruct( BaseStruct::LIFE ){
	Grid grid( Grid::DEAD );
	this->setGrid( grid );
}

LifeStruct::LifeStruct(std::string name) : BaseStruct( BaseStruct::LIFE, name ){
    //This is just an empty shell for the time being.
    	Grid grid( Grid::DEAD );
	this->setGrid( grid );

}

void LifeStruct::generateFile( FILE *ptr ){

	unsigned int index = 0;

	fprintf( ptr, "Life = {\n");

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
	fprintf( ptr, "\t\tAlive = %d;\n", this->getChar( Grid::ALIVE ) );
	fprintf( ptr, "\t\tDead = %d;\n", this->getChar( Grid::DEAD ) );
	fprintf( ptr, "\t};\n");

	Color alive = this->getColor( Grid::ALIVE );
	Color dead = this->getColor( Grid::DEAD );
	fprintf( ptr, "\tColors = {\n");
	fprintf( ptr, "\t\tAlive = (%d,%d,%d);\n", alive.getRed(), alive.getGreen(), alive.getBlue() );
	fprintf( ptr, "\t\tDead = (%d,%d,%d);\n", dead.getRed(), dead.getGreen(), dead.getBlue() );
	fprintf( ptr, "\t};\n");

	std::vector< Point > vec = this->getGrid().getAllWithState( Grid::ALIVE );
	fprintf( ptr, "\tInitial = {\n");
	fprintf( ptr, "\t\tAlive = ");
	for( index = 0; index < vec.size(); index++ ){
		fprintf( ptr, "(%d,%d)", vec.at( index ).getFirst(), vec.at( index ).getSecond() );
		if( index < vec.size() - 1)
			fprintf( ptr, ",");
		else
			fprintf( ptr, ";");
	}
	fprintf( ptr, "\n");
	fprintf( ptr, "\t};\n");

	fprintf( ptr, "};\n");
}

BaseStruct* LifeStruct::duplicate(){

	LifeStruct *life = new LifeStruct( name );

	life->setGrid( this->getGrid() );
	life->setTerrain( this->getTerrain() );
	life->setWindow( this->getWindow() );
	life->setColorMap( colorMap );
	life->setCharMap( charMap );
	life->setWinDefined( winDefined );

	return (BaseStruct*)life;
}
