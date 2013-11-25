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

/**
 * The BaseStruct class serves as a base class from which all the representations for the different
 * major structs will extend. All of these functions and features will be necessary regardless of the
 * specific struct that is being processed. The use of this class allows for inheritance within the 
 * application and thus makes it easier to handle the operations that would differ depending on the
 * underlying struct. This also removes the need for duplicate code as anything that is consistent
 * among all the structs will only need to be implemented once and then reused.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class BaseStruct {
public:

    /**
     * This enum corresponds to all the supported major struct types. Following this
     * method of differentiating types makes it easier to add support for future
     * struct types as a new entry will just be added to this enum.
     */
    enum StructType {
        LIFE, UNKOWN, WIREWORLD, ELEMENTARY
    };

    BaseStruct( StructType type );
    
    BaseStruct( StructType type, std::string name );
    virtual ~BaseStruct();

    /**
     * Gets the specific type of the struct that is represented by this BaseStruct. This
     * provides the knowledge that would be necessary to recast the instance down to the
     * sub-class if necessary within the code.
     *
     * @return Enum value that represents the sub-class level type of this struct.
     */
    StructType getType();
    
    /**
     * Gets the name that was specified for the given struct. This may be defined in the 
     * configuration file or programmatically later.
     *
     * @return Name of the simulation.
     */
    std::string getName();

    /**
     * Sets the name of the simulation within the struct.
     *
     * @param name The new name for the simulation.
     */
    void setName( std::string name );
    
    /**
     * Gets the Grid that corresponds to the state of the current simulation. The state contains
     * information regarding which cells are alive, dead, or any number of other possible states.
     *
     * @return Gets the Grid that represents the state of the simulation.
     */
    Grid getGrid();

    /**
     * Updates the Grid of the struct to reflect the provided Grid. The state of the Grid may
     * need to be updated after a simulation has been ran. This function allows that to be possible.
     *
     * @param update The new state of the grid for the struct.
     */
    void setGrid( Grid update );
    
    /**
     * Gets the current terrain within the BaseStruct. The terrain is used when calculating the next
     * generation of cells.
     *
     * @return The size of the terrain as a grid_dimension object.
     */
    grid_dimension getTerrain();

    /**
     * Updates the size of the terrain within the BaseStruct.
     *
     * @param dimen New size that should be used to handle the processing of the next generations states.
     */
    void setTerrain( grid_dimension dimen );
    
    /**
     * Gets the size of the window that will be used when displaying the generation information.
     *
     * @return Dimensions of the grid that should be displayed during the visualization stage.
     */
    grid_dimension getWindow();

    /**
     * Updates the dimensions of the window that will be displayed during the visualization operations.
     *
     * @param dimen The dimensions of the cell that should be displayed during next visualization operation.
     */
    void setWindow(grid_dimension dimen);
    
    /**
     * Determines if the window size has been explicitly specified. By default, the window size is the same
     * as the terrain.
     *
     * @param True if explicitly set, false otherwise.
     */
    bool isWinDefined();

    /**
     * Alters the state of whether the window has been explicitly defined.
     *
     * @param define Value to associate with the window assignment.
     */
    void setWinDefined( bool define );
    
    /**
     * Gets the ascii character code associated with the provided state.
     *
     * @param value State to look up the characer value
     * @return Ascii value for the character.
     */
    int getChar( Grid::cell_state value );

    /**
     * Changes the character for a given state.
     *
     * @param state The state for which to change the character code.
     * @param value The new character code.
     */
    void setChar( Grid::cell_state state, int value );
    
    /**
     * Gets the Color associated with the provided state.
     *
     * @param value State for which to get the Color
     * @return The Color that maps to the specified state.
     */
    Color getColor( Grid::cell_state value );

    /**
     * Sets the Color for the given state.
     *
     * @param state State for which to set the Color.
     * @param val The new Color.
     */
    void setColor( Grid::cell_state state, Color val );
    
    /**
     * Updates the map that handles the correlation between the Cell states and
     * the associated Colors.
     *
     * @param map The map between cell states and Colors.
     */
    void setColorMap( std::map< Grid::cell_state, Color> map );

    /**
     * Updates teh map that handles the correlation between the Cell states and
     * the associated Character codes.
     *
     * @param map The map between cell states and Character codes.
     */
    void setCharMap( std::map< Grid::cell_state, int > map );

    /**
     * Virtual function that must be implemented by any class that is
     * extending this class. This function will take the current state
     * of the Struct and will generate an output file consistent with
     * appendix A of the project writeup. Making the function virtual
     * means that the program doesn't have to care what struct is represented
     * in order to be able to generate the output file.
     *
     * @param ptr File that should be created during the operation.
     */
    virtual void generateFile( FILE *ptr ) = 0;

    /**
     * Creates an exact duplicate of the Struct on the heap. This allows
     * for a quick and easy way to create a duplicate without needing to know
     * the exact type of struct that is represented by this BaseStruct.
     *
     * @return Pointer to the BaseStruct on the heap that is a result of the duplication.
     */
    virtual BaseStruct* duplicate() = 0;

	virtual Grid::cell_state getDefaultState() = 0;

	virtual iRuletSet* getDefaultRuleSet() = 0;
    
private:
    void init();

protected:

    StructType type;
    std::string name;
    Grid data;
    bool winDefined;
    
    /*
     * These structs keep track of the window and terrain
     * that is used to perform the requested operations on the
     * Grids.
     */
    grid_dimension terrain;
    grid_dimension window;
    
    /*
     * Maps that handle the extraction of character codes and
     * Colors based on the cell state.
     */
    std::map< Grid::cell_state, int > charMap;
    std::map< Grid::cell_state, Color > colorMap;    

};

#endif	/* BASESTRUCT_H */

