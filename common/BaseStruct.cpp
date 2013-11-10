#include <string>
#include <map>

#include "BaseStruct.h"
#include "CustomException.h"

using namespace std;

BaseStruct::BaseStruct( StructType type ){
	init();
    this->type = type;
    std::string temp;
    this->name = temp;
    winDefined = false;
}

BaseStruct::BaseStruct(StructType type, std::string name){
	init();
    this->type = type;
    this->name = name;
    winDefined = false;
}

BaseStruct::~BaseStruct(){}


void BaseStruct::init(){
    type = BaseStruct::UNKOWN;
    name.clear();
    data.reset( Grid::DEAD );

	terrain.xVals.reset();
	terrain.yVals.reset();
    
    window.xVals.reset();
    window.yVals.reset();
    
    charMap.clear();
    colorMap.clear();
    
}

int BaseStruct::getChar(Grid::cell_state value){
    
    std::map< Grid::cell_state, int>::iterator it;
   
	/*
	   Locates the character code for the provided cell_state
	   value.
	   */
    it = charMap.find( value );
    if( it != charMap.end() ){
        return (char)( 0x000000ff & it->second );
    }
    else{
        //Mapping was not able to be found for the state
        throw new CustomException( CustomException::INVALID_MAPPING );
    }
}

Color BaseStruct::getColor(Grid::cell_state value){
    
    std::map< Grid::cell_state, Color>::iterator it;
   
	/*
	   Finds the color for the specified cell_state
	   */
    it = colorMap.find( value );
    if( it != colorMap.end() )
        return it->second;
    else
		//No mapping was available.
        throw new CustomException( CustomException::INVALID_MAPPING );
}

Grid BaseStruct::getGrid(){
    return data;
}

std::string BaseStruct::getName(){
    return name;
}

void BaseStruct::setName( std::string name ){
    this->name = name;
}

BaseStruct::StructType BaseStruct::getType(){
    return type;
}

grid_dimension BaseStruct::getWindow(){
	/*
	   The window should be the same as the terrain
	   until it has been explicitly defined. The following
	   if statement makes the determination of which case
	   to take.
	   */
    if( winDefined )
        return window;
    else
        return terrain;
}

bool BaseStruct::isWinDefined(){
    return winDefined;
}

void BaseStruct::setWinDefined( bool define ){
    winDefined = define;
}

grid_dimension BaseStruct::getTerrain(){
    return terrain;
}
    
void BaseStruct::setTerrain( grid_dimension dimen ){
    
    terrain = dimen;
}

void BaseStruct::setChar(Grid::cell_state state, int value){
    
    std::map< Grid::cell_state, int>::iterator it;
   
	/*
	   Attempts to find the specified state in the character mapping. If there is a 
	   mapping that already exists then it will be upated. If the mapping doesn't
	   already exist then it needs to be created.
	   */
    it = charMap.find( state );
    if( it != charMap.end() ){
        
        //If it already exists then just swap the value
        it->second = value;
    }
    else{
        
        //Insert the new value into the map if it isn't present.
        charMap.insert( std::pair< Grid::cell_state, int >(state, value) );
    }
}

void BaseStruct::setColor(Grid::cell_state state, Color val){
    
    std::map< Grid::cell_state, Color >::iterator it;

    /*
	   Attempts to find the specified state in the color mapping. If there is a 
	   mapping that already exists then it will be upated. If the mapping doesn't
	   already exist then it needs to be created.
	   */
    it = colorMap.find( state );
    if( it != colorMap.end() ){
		//Swap the value of the current mapping
        it->second = val;
    }
    else{
		//Add a new mapping for the state
        colorMap.insert( std::pair< Grid::cell_state, Color>( state, val) );
    }
}

void BaseStruct::setGrid(Grid update){
    this->data = update;
}

void BaseStruct::setWindow(grid_dimension dimen){
    this->window = dimen;
    winDefined = true;
}

void BaseStruct::setColorMap( std::map< Grid::cell_state, Color> map ){
        
    colorMap = map;
}

void BaseStruct::setCharMap( std::map< Grid::cell_state, int > map ){
 
    charMap = map;
}
