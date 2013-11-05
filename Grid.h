/* 
 * File:   Grid.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:38 PM
 */

#ifndef GRID_H
#define	GRID_H

#include <vector>
#include <map>

#include "Point.h"
#include "constants.h"

class Grid {
public:
    
    enum cell_state { ALIVE=0, DEAD=1 };
    //const static int ALIVE = 0;
    //const static int DEAD = 1;

    Grid();
    Grid( Grid::cell_state defaultState );
 
   /**
     * Retrieves the value at that particular coordinate within the grid.
     * @param dimen
     * @return 
     */
    Grid::cell_state get(Point dimen);
    void set(Point dimen, cell_state value);
    
    void reset( Grid::cell_state defaultState );
    
    /**
     * Scan through all the cells in the grid that don't
     * correspond to the default value. The terrain consists of all of these not default
     * cells addresses.
     * @return 
     */
    grid_dimension getTerrain();
    
    std::vector< Point > getAllWithState( Grid::cell_state val );

    Grid::cell_state getDefault();

private:
    
    /*
     * Instead of creating an N x N grid of integers in memory, this class should 
     * provide an interface that appears as if this is being performed in memory. In
     * actuality, the Grid class should be only storing records of the alive locations
     * and updating those according to function calls.
     */
    std::map< Point, Grid::cell_state > data;
    Grid::cell_state defaultState;

    void init();

};

#endif	/* GRID_H */

