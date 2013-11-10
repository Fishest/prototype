#include <stdio.h>

#include "AsciiVisual.h"
#include "Grid.h"
#include "constants.h"
#include "BaseStruct.h"
#include "Point.h"
#include "LifeStruct.h"

AsciiVisual::AsciiVisual(){

}

void AsciiVisual::visualize( BaseStruct* base ){

	grid_dimension win = base->getWindow();
	int rowIndex = win.yVals.getFirst();
	int colIndex = win.xVals.getFirst();

	/*
	   Need to loop through every cell in the set window. For each cell, it's state is then
	   pulled from the Grid. Based on the found state, a character is then displayed to the screen
	   for that cell.
	   */
	for( rowIndex = win.yVals.getSecond() ; rowIndex >= win.yVals.getFirst(); rowIndex-- ){

		for( colIndex = win.xVals.getFirst() ; colIndex <= win.xVals.getSecond(); colIndex++ ){

			Point loc( colIndex, rowIndex );

			//Obtains the state of the cell at the currently processing location
			Grid::cell_state state = base->getGrid().get( loc );

			//Determines what character to use for drawing that cell
			int displayChar = base->getChar( state );
			displayChar = displayChar & 0x000000ff;

			//Prints the character to the screen.
			char value = displayChar;
			fprintf( stdout, "%c", value);
		}

		fprintf( stdout, "\n");

	}
}
