#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <QtGui>

#include "../common/FileParser.h"
#include "../common/LifeStruct.h"
#include "../common/BaseStruct.h"
#include "../common/Point.h"
#include "../life_gui_source/LifeGUI.h"
#include "../common/CustomException.h"

void printHelpMessage(){
	fprintf( stderr, "\n\nlife_gui\n");
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

	fprintf( stderr, "\n\t./life_gui [switches] file1\n\n");

	fprintf( stderr, "This application differs from \"life\" only in that it presents a graphical interface designed\n");
	fprintf( stderr, "in the QT graphical framework. The life application presents the generation data in an ascii\n");
	fprintf( stderr, "terminal. life_gui also supports the ability to step through the generations by clicking the mouse\n");
	fprintf( stderr, "within the graphical window.\n");

	fprintf( stderr, "This application supports many of the same switches as life. There are a couple of switches that\n");
	fprintf( stderr, "are different than the life application. Specifically, the gui application supports the ability\n");
	fprintf( stderr, "to control the size of the cells in pixels.\n Below are the available switches for life_gui.\n");

	fprintf( stderr, "-g N : Specifies the number of generations that should be simulated.\n");
	fprintf( stderr, "-s P : Specifies the number of pixels to use for each cell on the map.\n");
	fprintf( stderr, "-h : Displays this help message\n");
	fprintf( stderr, "-tx l..h : Specify the X values of the terrain, will override content from file.\n");
	fprintf( stderr, "-ty l..h : Specify the Y values of the terrain, will override content from file.\n");
	fprintf( stderr, "-wx : Controls the width of the cells that are displayed on the screen.\n");
	fprintf( stderr, "-wy : Controls the height of the cells that are displayed on the screen.\n\n\n");

	return;
}

int main( int argc, char ** args ){

	int numPixels = 10;
	int generations = 0;

	int index = 1;
	Point tx;
	Point ty;
	Point wx;
	Point wy;
	bool terrainXOverride = false;
	bool terrainYOverride = false;
	bool winXOverride = false;
	bool winYOverride = false;
	bool fileInput = false;
	std::string filename;
	QApplication app(argc, args);

	BaseStruct* base = NULL;

	LifeStruct *life = NULL;

	FILE *input = NULL;

	LifeGUI *gui = new LifeGUI();

	while( index < argc ){

		if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'h' ){
			printHelpMessage();
			return 0;
		}
		if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 's' ){
			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain the number of pixels.\n");
				return 0;
			}

			if( FileParser::onlyDigits( args[index] ) )
				numPixels = atoi( args[index] );
			else
				numPixels = -1;

			if( numPixels < 1 ){
				fprintf( stderr, "Please choose a value of at least 1 for the number of pixels per block.\n");
				return 0;
			}
		}
		else if( strlen( args[index] ) == 2 && args[index][0] == '-' && args[index][1] == 'g' ){

			if( argc <= ++index ){
				fprintf( stderr, "Invalid number of arguments to contain generation count.\n");
				return 0;
			}

			if( FileParser::onlyDigits( args[index] ) )
				generations = atoi( args[index] );
			else
				generations = -1;

			if( generations < 0 ){
				fprintf( stderr, "Must give positive number of generations.\n");
				return 0;
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
		a.ErrorMessage();
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

	try{
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
	} catch( CustomException a ){
		a.ErrorMessage();
		return 0;
	}

	gui->setStruct( base );
	gui->setPixels( numPixels );
	gui->runGenerations( generations );

	gui->show();

	return app.exec();

}




