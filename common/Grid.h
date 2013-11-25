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

/**
 * The Grid handles the management of the cell states that are used for processing the 
 * generation simuations. There was a particular need for this class to be as efficient
 * in memory and speed as possible. A simulation will require many accesses into the Grid
 * and may lead to significant amount of time being spent processing the information. The 
 * implementation also needs to be efficient in memory usage as a provided Grid could be
 * extremely large but at the same time sparsely populated. The class works by only keeping
 * track of the states that are different than the default state. This allows for a memory
 * footprint only the size of the number of elements that are different. Thus, an extremely
 * large but sparse Grid will not take much memory and lookups will be quick.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class Grid {
public:
    
    /*
     * Each cell in the Grid corresponds to one of the states in this
     * enum. This layout makes it possible to easily add new states 
     * to the Grids supporting matrix without having to modify any
     * of the underlying processing code. New states are added by just
     * adding new values into this enum.
     */
    enum cell_state { ALIVE=0, DEAD=1, EMPTY=2, ELECTRON_HEAD=3, ELECTRON_TAIL=4, WIRE=5, ZERO=6, ONE=7 };

    Grid();
    Grid( Grid::cell_state defaultState );
 
   /**
     * Retrieves the state of the cell at the given point within the Grid.
     *
     * @param loc The location in the Grid to retrieve the state
     * @return State of the cell, consisten with cell_state enum.
     */
    Grid::cell_state get(Point loc);

    /**
     * Updates the state of a given cell within the Grid.
     *
     * @param dimen Location in the Grid to be updated.
     * @param value The new state for the specified cell.
     */
    void set(Point dimen, cell_state value);
    
    /**
     * Resets the entire Grid back to the default state.
     *
     * @param defaultState The state that should be marked as default within the Grid.
     */
    void reset( Grid::cell_state defaultState );
    
    /**
     * Scan through all the cells in the grid that don't
     * correspond to the default value. The terrain consists of all of these not default
     * cells addresses.
     *
     * @return grid_dimension that corresponds to the maxes and mins of both the X and Y values.
     */
    grid_dimension getTerrain();
    
    /**
     * Gets all the points in the Grid that have the specified state.
     *
     * @param val The state to perform the Grid wise search.
     * @return The list of all the points that correspond to the specified state.
     */
    std::vector< Point > getAllWithState( Grid::cell_state val );

    /**
     * Obtains the state that is marked as default in the Grid.
     *
     * @return State that corresponds as default.
     */
    Grid::cell_state getDefault();

	Grid::cell_state static convertState( std::string str );
	int static countCells( Grid grid, cell_state state, grid_dimension terrain, Point pt );

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

