/* 
 * File:   BaseStruct.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:30 PM
 */

#ifndef BASESTRUCT_H
#define	BASESTRUCT_H

#include <string>
#include <map>

#include "Grid.h"
#include "Color.h"
#include "Point.h"

class BaseStruct {
public:

    enum StructType {
        LIFE, UNKOWN
    };

    BaseStruct( StructType type );
    
    BaseStruct( StructType type, std::string name );

    StructType getType();
    
    std::string getName();
    void setName( std::string name );
    
    Grid getGrid();
    void setGrid( Grid update );
    
    grid_dimension getTerrain();
    void setTerrain( grid_dimension dimen );
    
    grid_dimension getWindow();
    void setWindow(grid_dimension dimen);
    
    int getChar( Grid::cell_state value );
    void setChar( Grid::cell_state state, int value );
    
    Color getColor( Grid::cell_state value );
    void setColor( Grid::cell_state, Color val );
    
    void setColorMap( std::map< Grid::cell_state, Color> map );
    void setCharMap( std::map< Grid::cell_state, int > map );
    
private:
    void init();

protected:

    StructType type;
    std::string name;
    Grid data;
    
    grid_dimension terrain;
    grid_dimension window;
    
    std::map< Grid::cell_state, int > charMap;
    std::map< Grid::cell_state, Color > colorMap;    

};

#endif	/* BASESTRUCT_H */

