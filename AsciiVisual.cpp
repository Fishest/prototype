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

	for( rowIndex = win.yVals.getSecond() ; rowIndex >= win.yVals.getFirst(); rowIndex-- ){

		for( colIndex = win.xVals.getFirst() ; colIndex <= win.xVals.getSecond(); colIndex++ ){

			Point loc( colIndex, rowIndex );
			Grid::cell_state state = base->getGrid().get( loc );

			int displayChar = base->getChar( state );
			displayChar = displayChar & 0x000000ff;

			char value = displayChar;
			fprintf( stdout, "%c", value);
		}

		fprintf( stdout, "\n");

	}
}