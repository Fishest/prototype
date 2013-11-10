#include "CustomException.h"

CustomException::CustomException(ErrorCode errorCode) {
    code = errorCode;
}

const char* CustomException::ErrorMessage() const throw () {

	/*
	   Prints an error message consisten with the problem that was encountered
	   during the programs execution.
	   */

	if (code == INVALID_MAPPING) 
		std::cerr << "Unable to find mapping to cell state.\n";
	else if (code == INVALID_FILE) 
		std::cerr << "Provided file doesn't follow proper file format.\n";
	else if (code == NULL_PARAMETER)
		std::cerr << "Invalid parameter passed to the function.\n";
	else if( code == INVALID_FILENAME )
		std::cerr << "Provided filename doesn't correspond to a proper file.\n";
	else if( code == NOT_ENOUGH_BUFFER_FOR_TOKEN )
		std::cerr << "Not enough memory available on system for processing file.\n";
	else if( code == INVALID_COLOR )
		std::cerr << "Invalid formatted color object in specified file.\n";
	else if( code == INVALID_POINT )
		std::cerr << "Invalid point was ran across throughout the application.\n";
	else if( code == INVALID_TERRAIN_WINDOW )
		std::cerr << "Specified terrain doesn't follow proper formatting.\n";
	else if( code == INVALID_RANGE )
		std::cerr << "Invalid set of ranges provided in configuration file or command line.\n";
	else if( code == INVALID_COLOR_STRUCT )
		std::cerr << "Color struct wasn't properly formatted. Please verify correct format.\n";
	else if( code == INVALID_CELL_STATE_FOUND )
		std::cerr << "Provided file contains a cell state that program doesn't support. Please verify files content.\n";
	else if( code == PREMATURE_EOF )
		std::cerr << "Given file is too short or improperly formatted to be read correctly.\n";
	else if( code == NO_NEXT_STRUCT )
		std::cerr << "Improper processing of given file. Another struct was not found in the provided file.\n";
	else if( code == NEGATIVE_GENERATIONS )
		std::cerr << "Negative value provided for generations. Please specify proper value.\n";
	else if( code == INVALID_CHAR )
		std::cerr << "Invalid character value provided in the given file. Supported values are 0-255.\n";

}

CustomException::ErrorCode CustomException::getError() {
    return code;
}
