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
	else if( code == INVALID_STRUCT_TYPE )
		fprintf( ptr, "Unsupported struct type was found in the provided configuration file.\n");
	else if( code == INVALID_TYPE_FOR_SIMULATION )
		fprintf( ptr, "A not compatible struct was provided to the Elementary rule set. Please make sure that proper configuration file provided.\n");
	else if( code == INVALID_RULE_VALUE )
		fprintf( ptr, "An invalid value was provided for the Elementary structs rule argument. The value must be between 0 and 255.\n");
	else if( code == INVALID_TERRAIN_STRUCT )
		fprintf( ptr, "Terrain struct provided in the configuration file is not properly formatted.\n");
	else if( code == NOT_IMPLEMENTED_YET )
		fprintf( ptr, "You've come across a feature that is currently in progress of being developed. I apologize for the inconvenience.\n");

}
