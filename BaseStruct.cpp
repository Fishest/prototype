#include <string>
#include <map>

#include "BaseStruct.h"
#include "CustomException.h"

using namespace std;

BaseStruct::BaseStruct(StructType type, std::string name){
    this->type = type;
    this->name = name;
}

BaseStruct::init(){
    type = StructType.UNKOWN;
    name.clear();
    data.reset( Grid::cell_state.DEAD );
    
    window.xVals.reset();
    window.yVals.reset();
    
    charMap.clear();
    colorMap.clear();
}

BaseStruct::getChar(Grid::cell_state value){
    
    std::map< Grid::cell_state, int>::iterator it;
    
    it = charMap.find( value );
    if( it != charMap.end() ){
        return (char)( 0x000000ff & it->second );
    }
    else{
        //Mapping was not able to be found for the state
        throw new CustomException( CustomException::ErrorCode.INVALID_MAPPING );
    }
}

BaseStruct::getColor(Grid::cell_state value){
    
    std::map< Grid::cell_state, Color>::iterator it;
    
    it = colorMap.find( value );
    if( it != colorMap.end() )
        return it->second;
    else
        throw new CustomException( CustomException::ErrorCode.INVALID_MAPPING );
}

BaseStruct::getGrid(){
    return data;
}

BaseStruct::getName(){
    return name;
}

BaseStruct::getType(){
    return type;
}

BaseStruct::getWindow(){
    return window;
}

BaseStruct::setChar(Grid::cell_state state, int value){
    
    std::map< Grid::cell_state, int>::iterator it;
    
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

BaseStruct::setColor(Grid::cell_state state, Color val){
    
    std::map< Grid::cell_state, Color >::iterator it;
    
    it = colorMap.find( state );
    if( it != colorMap.end() ){
        it->second = val;
    }
    else{
        colorMap.insert( std::pair< Grid::cell_state, Color>( state, val) );
    }
}

BaseStruct::setGrid(Grid update){
    
    if( update == NULL )
        throw new CustomException( CustomException::ErrorCode.NULL_PARAMETER );
    
    this->data = update;
}

BaseStruct::setWindow(grid_dimension dimen){
    
    if( dimen == NULL )
        throw new CustomException( CustomException::ErrorCode.NULL_PARAMETER );
    
    this->window = dimen;
}