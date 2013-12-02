#include <stdio.h>

#include "CustomException.h"

CustomException::CustomException(ErrorCode errorCode) {
    code = errorCode;
}

CustomException::ErrorCode CustomException::getError() {
    return code;
}

void CustomException::printMessage( FILE *ptr, ErrorCode code ){

	/*
	   Prints an error message consisten with the problem that was encountered
	   during the programs execution.
	   */

	if (code == INVALID_MAPPING) 
		fprintf( ptr, "Unable to find mapping to cell state.\n");
	else if (code == INVALID_FILE) 
		fprintf( ptr, "Provided file doesn't follow proper file format.\n");
	else if (code == NULL_PARAMETER)
		fprintf( ptr, "Invalid parameter passed to the function.\n");
	else if( code == INVALID_FILENAME )
		fprintf( ptr, "Provided filename doesn't correspond to a proper file.\n");
	else if( code == NOT_ENOUGH_BUFFER_FOR_TOKEN )
		fprintf( ptr, "Not enough memory available on system for processing file.\n");
	else if( code == INVALID_COLOR )
		fprintf( ptr, "Invalid formatted color object in specified file.\n");
	else if( code == INVALID_POINT )
		fprintf( ptr, "Invalid point was ran across throughout the application.\n");
	else if( code == INVALID_TERRAIN_WINDOW )
		fprintf( ptr, "Specified terrain doesn't follow proper formatting.\n");
	else if( code == INVALID_RANGE )
		fprintf( ptr, "Invalid set of ranges provided in configuration file or command line.\n");
	else if( code == INVALID_COLOR_STRUCT )
		fprintf( ptr, "Color struct wasn't properly formatted. Please verify correct format.\n");
	else if( code == INVALID_CELL_STATE_FOUND )
		fprintf( ptr, "Provided file contains a cell state that program doesn't support. Please verify files content.\n");
	else if( code == PREMATURE_EOF )
		fprintf( ptr, "Given file is too short or improperly formatted to be read correctly.\n");
	else if( code == NO_NEXT_STRUCT )
		fprintf( ptr, "Improper processing of given file. Another struct was not found in the provided file.\n");
	else if( code == NEGATIVE_GENERATIONS )
		fprintf( ptr, "Negative value provided for generations. Please specify proper value.\n");
	else if( code == INVALID_CHAR )
		fprintf( ptr, "Invalid character value provided in the given file. Supported values are 0-255.\n");


}
