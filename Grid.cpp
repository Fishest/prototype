#include <map>
#include <vector>
#include <set>

#include "Grid.h"
#include "Point.h"
#include "CustomException.h"

using namespace std;

Grid::Grid(){
    this->defaultState = Grid::DEAD;
    init();
}

Grid::Grid( Grid::cell_state defaultState ){
    this->defaultState = defaultState;
    init();
}

Grid::cell_state Grid::get( Point dimen ){
    
    std::map<Point,Grid::cell_state>::iterator it = data.find( dimen );
    if( it != data.end() ){
        
        //If a record has been added for the specified value then we want to return that previously seen
        //state. A state being saved means that the coordinate has been changed from the default.
        return it->second;
    }
    else{
        
        /*
         * A record wasn't found in the map for the corresponding location. This means that the requested element
         * hasn't been changed from the default state of the grid. This type of layout allows for quick searches
         * and optimal storage of the grid values. The code only has to look through the cells that have been changed.
         */
        return defaultState;
    }
}

std::vector< Point > Grid::getAllWithState( Grid::cell_state val ){
    
    std::vector< Point > ret;
    
    std::map< Point, Grid::cell_state>::iterator it = data.begin();
    while( it != data.end() ){
        
        /*
         * Looks through all the mappings from Point to cell_state. The first element is the point and the second
         * element is the cell state. This adds the Point, or first element, to the vector that contains all the 
         * Points.
         */
        if( it->second == val ){
            ret.push_back( it->first );
        }
        it++;
    }
    
    return ret;    
}

grid_dimension Grid::getTerrain(){
    
    int minX = 0;
    int maxX = 0;
    int minY = 0;
    int maxY = 0;
    
    std::map< Point, Grid::cell_state >::iterator it = data.begin();
    while( it != data.end() ){
        
        Point temp = it->first;
        
        if( temp.getFirst() < minX ){
            minX = temp.getFirst();
        }
        if( temp.getFirst() > maxX )
            maxX = temp.getFirst();
        if( temp.getSecond() < minY )
            minY = temp.getSecond();
        if( temp.getSecond() > maxY )
            maxY = temp.getSecond();
        
        it++;
    }
    
    grid_dimension temp;
    Point pt(minX, maxX);
    
    temp.xVals = pt;
    
    Point pt1( minY, maxY);
    temp.yVals = pt1;
    
    return temp;
}

void Grid::init(){
    data.clear();
}

void Grid::reset( Grid::cell_state defaultState ){
    this->defaultState = defaultState;
    data.clear();
}

void Grid::set(Point dimen, Grid::cell_state value){    
    
    bool del = false;
    if( value == defaultState )
        del = true;
    
    std::map< Point, Grid::cell_state >::iterator it = data.find( dimen );
    if( it != data.end() ){
        
        /*
         * The given point is in the map and thus it needs to be updated. In the event that
         * the new state is equivalent to the current default, the point needs to be deleted
         * from the map. If they aren't the same then the current value in the map needs to be
         * adjusted.
         */
        if( del )
            data.erase( dimen );
        else
            it->second = value;
    }
    else{
        
        /*
         * If new value isn't equal to the default then we want to add it to
         * the mapping for the Grid.
         */
        if( !del )
            data.insert( std::pair< Point, Grid::cell_state>( dimen, value) );
        
    }
}

Grid::cell_state Grid::getDefault(){
    return defaultState;
}