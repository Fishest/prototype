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

Grid::cell_state static Grid::convertState( string content ){

	if( content.find( "Alive" ) != content.npos ){
		return Grid::ALIVE;
	}
	else if( content.find( "Dead" ) != content.npos ){
		return Grid::DEAD;
	}
	else if( content.find( "Empty" ) != content.npos ){
		return Grid::EMPTY;
	}
	else if( content.find( "Head" ) != content.npos ){
		return Grid::ELECTRON_HEAD;
	}
	else if( content.find( "Tail" ) != content.npos ){
		return Grid::ELECTRON_TAIL;
	}
	else if( content.find( "Wire" ) != content.npos ){
		return Grid::WIRE;
	}
	else if( content.find( "Zero" ) != content.npos ){
		return Grid::ZERO;
	}
	else if( content.find( "One" ) != content.npos ){
		return Grid::ONE;
	}
	else{
	throw new CustomException( CustomException::INVALID_FILE );
	}
}

int static Grid::countCells( Grid grid, cell_state state, grid_dimension terrain, Point pt ){
	int rowIndex = 0;
	int count = 0;

	/*
	   The firs series of for loops take care of adding the number of alive cells around a particular
	   point in the Grid. Once the total count is found, the count is compared with the rules defined
	   in the writeup to determine the next state of the cell.
	   */

	/*
	   Scans the row directly below the given parameter.
	   */
	for( rowIndex = pt.getFirst() - 1; rowIndex <= pt.getFirst() + 1; rowIndex++ ){
		Point temp( rowIndex, pt.getSecond() - 1 );
		if( data.get( temp ) == state && temp.getFirst() >= terrain.xVals.getFirst() &&
				temp.getFirst() <= terrain.xVals.getSecond() && temp.getSecond() >= terrain.yVals.getFirst() &&
					temp.getSecond() <= terrain.yVals.getSecond() ){
			count++;
		}
	}

	//Scans the row directly above the given parameter.
	for( rowIndex = pt.getFirst() - 1; rowIndex <= pt.getFirst() + 1; rowIndex++ ){
		Point temp( rowIndex, pt.getSecond() + 1 );
		if( data.get( temp ) == state && temp.getFirst() >= terrain.xVals.getFirst() &&
				temp.getFirst() <= terrain.xVals.getSecond() && temp.getSecond() >= terrain.yVals.getFirst() &&
					temp.getSecond() <= terrain.yVals.getSecond() ){
			count++;
		}
	}

	//Checks cell to the left of the given point.
	Point temp( pt.getFirst() - 1, pt.getSecond() );
	if( data.get( temp ) == state && temp.getFirst() >= terrain.xVals.getFirst() &&
			temp.getFirst() <= terrain.xVals.getSecond() && temp.getSecond() >= terrain.yVals.getFirst() &&
				temp.getSecond() <= terrain.yVals.getSecond() ){
		count++;
	}

	//Checks cell to the left of the given point.
	Point temp1( pt.getFirst() + 1, pt.getSecond() );
	if( data.get( temp1 ) == state && temp1.getFirst() >= terrain.xVals.getFirst() &&
			temp1.getFirst() <= terrain.xVals.getSecond() && temp1.getSecond() >= terrain.yVals.getFirst() &&
				temp1.getSecond() <= terrain.yVals.getSecond() ){
		count++;
	}

	return count;
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

	/*
	   Loops through all the cells in the map that have been changed from the
	   default value. With each of these cells, the point locations are compared
	   against the current max and min values. By the end of the altered cells, it
	   will be known what the upper and lower bounds of the altered cells are within
	   the Grid.
	   */
    
    std::map< Point, Grid::cell_state >::iterator it = data.begin();
    while( it != data.end() ){
        
        Point temp = it->first;
       
		//Determines if the current max or min needs to be updated
		//according to the new found location.
        if( temp.getFirst() < minX )
            minX = temp.getFirst();
        if( temp.getFirst() > maxX )
            maxX = temp.getFirst();
        if( temp.getSecond() < minY )
            minY = temp.getSecond();
        if( temp.getSecond() > maxY )
            maxY = temp.getSecond();
        
        it++;
    }

	//Creates the grid_dimension struct that will be returned
	//containing the bounds of the altered cells.
    
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
