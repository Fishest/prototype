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
#include "AsciiVisual.h"
#include "visuals.h"

void printHelpMessage(){
	fprintf( stderr, "\n\nLife\n");
	fprintf( stderr, "Developer: Cameron Whipple\n");
	fprintf( stderr, "-----------------------------------------------------------------------\n");
	fprintf( stderr, "The life application provides a way to run simulations on differing life states.\n");
	fprintf( stderr, "It is based on the \"Game of Life\" that was devised by John Conway in the 1970's.\n");
	fprintf( stderr, "The simulations work by defining layout of cells within a grid. Each of these cells\n");
	fprintf( stderr, "are provided a state, such as Dead or Alive. The program then runs through a specified\n");
	fprintf( stderr, "number of generations in which the states of the cells are altered based on the rule set.\n");
	fprintf( stderr, "Over the years, several different sets of rules have been derived to alter the flow of\n");
	fprintf( stderr, "the simulations.\n\n");

	fprintf( stderr, "The application is able to accept configuration information in two ways. The default method\n");
	fprintf( stderr, "involves reading the content from the standard input stream. The second method is enabled by\n");
	fprintf( stderr, "specifying the name of a file from the command line. An example of this is given below.\n");

	fprintf( stderr, "\n\t./life [switches] file1\n\n");

	fprintf( stderr, "There are several switches that can be used to control the operation of the application.\n");
	fprintf( stderr, "-f : The results of the simulation will be output in a form consistent with input file.\n");
	fprintf( stderr, "-g N : Specifies the number of generations that should be simulated.\n");
	fprintf( stderr, "-h : Displays this help message\n");
	fprintf( stderr, "-tx l..h : Specify the X values of the terrain, will override content from file.\n");
	fprintf( stderr, "-ty l..h : Specify the Y values of the terrain, will override content from file.\n");
	fprintf( stderr, "-v : Displays the results of the simuations in an ascii format.\n");
	fprintf( stderr, "-wx : Controls the width of the cells that are displayed on the screen.\n");
	fprintf( stderr, "-wy : Controls the height of the cells that are displayed on the screen.\n\n\n");

	return;
}

int main( int argc, char **args ){

	int index = 1;
	bool fileOutput = false;
	int generations = 0;
	Point tx;
	Point ty;
	Point wx;
	Point wy;
	bool terrainXOverride = false;
	bool terrainYOverride = false;
	bool winXOverride = false;
	bool winYOverride = false;
	bool visualOutput = false;
	bool fileInput = false;
	std::string filename;

	BaseStruct* base = NULL;

	LifeRuleSet rules;
	LifeStruct *life = NULL;

	FILE *input = NULL;

	while( index < argc ){

		if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'h' ){
			printHelpMessage();
			return 0;
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
				terrainXOverride = true;
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
				terrainYOverride = true;
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
				winXOverride = true;
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
				winYOverride = true;
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

	if( !fileOutput && !visualOutput ){
		fprintf( stderr, "Please specify output form.\n");
		return 0;
	}

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
			base = parse.getNext();
		}

	}catch( CustomException a ){
		fprintf( stderr, "Error occured while parsing the file.\n");
		return 0;
	}

	if( base != NULL && base->getType() == BaseStruct::LIFE ){
		life = (LifeStruct*)base;
	}

	if( life == NULL ){
		fprintf( stderr, "Error during processing of Life struct.\n");
		return 0;
	}

	/*
	 * The next step is to update the window and terrain values within the struct
	 * with the values that were pulled from the arguments.
	 */

	 if( terrainXOverride ){
	 	grid_dimension dimen = life->getTerrain();
	 	dimen.xVals = tx;
	 	life->setTerrain( dimen );
	 }

	 if( terrainYOverride ){
	 	grid_dimension dimen = life->getTerrain();
	 	dimen.yVals = ty;
	 	life->setTerrain( dimen );
	 }

	 if( winXOverride ){
	 	grid_dimension dimen;
	 	if( life->isWinDefined() )
	 		dimen = life->getWindow();
	 	
	 	dimen.xVals = wx;
	 	life->setWindow( dimen );
	 }

	 if( winYOverride ){
	 	grid_dimension dimen;
	 	if( life->isWinDefined() )
	 		dimen = life->getWindow();

	 	dimen.yVals = wy;
	 	life->setWindow( dimen );
	 }
	 
	/*
	 * The next step is to run the grid through the requested number of generations.
	 */
	 Grid locGrid = life->getGrid();
	 Grid & refGrid = locGrid;
	 life->setGrid( rules.simulateGenerations( refGrid, generations, life->getTerrain() ) );

	/*
	 * The last step is to output the results of the simulations to standard output. The format
	 * is controlled through the use of the command line arguments.
	 */
	 if( visualOutput ){
	 	AsciiVisual vis;

	 	vis.visualize( life );
	 }
	 else if( fileOutput ){
	 	life->generateFile( stdout );
	 }

	delete life;

	return 0;
}