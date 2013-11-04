#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>

#include "FileParser.h"
#include "Point.h"
#include "LifeRuleSet.h"
#include "constants.h"
#include "LifeStruct.h"
#include "CustomException.h"

void printHelpMessage(){
	printf("Needs implemented.\n");
}

int main( int argc, char **args ){

	int index = 1;
	bool fileOutput = false;
	int generations = 0;
	Point tx;
	Point ty;
	Point wx;
	Point wy;
	bool terrainOverride = false;
	bool windowOverride = false;
	bool visualOutput = false;
	bool fileInput = false;
	std::string filename;

	LifeRuleSet rules;
	LifeStruct life;
	
	FILE *input = NULL;

	while( index < argc ){

		if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'h' ){
			printHelpMessage();
		}
		else if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'f' ){
			fileOutput = true;
		}
		else if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'g' ){

			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain generation count.\n");
				return 0;
			}
			generations = atoi( args[index] );
			if( generations < 0 ){
				fprintf( stderr, "Must give positive number of generations.\n");
			}
		}
		else if( strlen( args[ index ] ) == 3 && args[index][0] == '-' && args[index][1] == 't' && args[index][2] == 'x' ){

			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain range information.\n");
				return 0;
			}

			try{
				std::string content( args[index] );
				tx = FileParser::parseDotRange( content );
			}catch( CustomException& a ){
				fprintf( stderr, "Unable to process X Terrain range.\n");
				return 0;
			}

		}
		else if( strlen( args[ index ] ) == 3 && args[index][0] == '-' && args[index][1] == 't' && args[index][2] == 'y' ){

			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain range information.\n");
				return 0;
			}

			try{
				std::string content( args[index] );
				ty = FileParser::parseDotRange( content );
			}catch( CustomException& a ){
				fprintf( stderr, "Unable to process Y Terrain range.\n");
				return 0;
			}

		}
		else if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'v' ){
			visualOutput = true;	
		}
		else if( strlen( args[ index ] ) == 3 && args[index][0] == '-' && args[index][1] == 'w' && args[index][2] == 'x' ){

			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain range information.\n");
				return 0;
			}

			try{
				std::string content( args[index] );
				wx = FileParser::parseDotRange( content );
			}catch( CustomException a ){
				fprintf( stderr, "Unable to process X Window range.\n");
				return 0;
			}

		}
		else if( strlen( args[ index ] ) == 3 && args[index][0] == '-' && args[index][1] == 'w' && args[index][2] == 'y' ){

			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain range information.\n");
				return 0;
			}

			try{
				std::string content( args[index] );
				wy = FileParser::parseDotRange( content );
			}catch( CustomException a ){
				fprintf( stderr, "Unable to process Y Window range.\n");
				return 0;
			}

		}
		else if( strlen( args[index] ) > 0 && args[index][0] != '-'){
			filename = std::string( args[index] );
			fileInput = true;
		}

		index++;

	} //Ends While loop

	/*
		Set up the input file so that it can be passed to the appropriate parsing function.
		*/
	if( fileInput ){
		input = fopen( filename.c_str(), "r");
		if( input == NULL ){
			fprintf( stderr, "Unable to open specified file.\n");
			return 0;
		}
	}
	else{
		input = stdin;
	}


	/*
	 * This portion of the code handles the reading of the struct file from either standard
	 * input or a specified file.
	 */
	try{

		FileParser parse( input );

		if( parse.hasNext() ){
			life = parse.getNext();
		}

	}catch( CustomException a ){
		fprintf( stderr, "Error occured while parsing the file.\n");
		return 0;
	}

	/*
	 * The next step is to update the window and terrain values within the struct
	 * with the values that were pulled from the arguments.
	 */
	 
	 //Override the terrain from the file with the ones from the command line.
	 if( terrainOverride ){
	 	grid_dimension dimen;
	 	dimen.xVals = tx;
	 	dimen.yVals = ty;
	 	life.setTerrain( dimen );

	 	if( !windowOverride ){
	 		grid_dimension win;
	 		win.xVals = tx;
	 		win.yVals = ty;
	 		life.setWindow( win );
	 	}
	 }

	 if( windowOverride ){
	 	grid_dimension dimen;
	 	dimen.xVals = wx;
	 	dimen.yVals = wy;
	 	life.setWindow( dimen );
	 }

	/*
	 * The next step is to run the grid through the requested number of generations.
	 */
	 Grid locGrid = life.getGrid();
	 Grid & refGrid = locGrid;
	 rules.simulateGenerations( refGrid, generations, life.getTerrain() );

	/*
	 * The last step is to output the results of the simulations to standard output. The format
	 * is controlled through the use of the command line arguments.
	 */
	//TODO Implement the code to handle the exportation.


	return 0;
}