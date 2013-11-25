#include <string>

#include "BaseStruct.h"
#include "Grid.h"
#include "iRuleSet.h"
#include "ElementaryStruct.h"

ElementaryStruct::ElementaryStruct() : BaseStruct( BaseStruct::ELEMENTARY ){
	Grid grid( Grid::ZERO );
	this->setGrid( grid );
	rule = 0;
}

ElementaryStruct::ElementaryStruct( std::string name ) : BaseStruct( BaseStruct::ELEMENTARY, name){
	Grid grid( Grid::ZERO );
	this->setGrid( grid );
	rule = 0;
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

iRuletSet* ElementaryStruct::getDefaultRuleSet(){
	ElementaryRuleSet *rules = new ElementaryRuleSet();
	return rules;
}

