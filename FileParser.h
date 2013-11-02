/* 
 * File:   FileParser.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:32 PM
 */

#ifndef FILEPARSER_H
#define	FILEPARSER_H

#include <string>
#include <map>

#include "BaseStruct.h"
#include "Point.h"
#include "Color.h"
#include "Token.h"

class FileParser {
public:
    
    FileParser( FILE *file );
    FileParser( std::string filename );
    ~FileParser();

    BaseStruct getNext();
    bool hasNext();

private:

    enum ParseState {
        NOTHING, START, DONE, LIFE_START
    };

    FILE *input;
    ParseState state;
    Grid::cell_state defaultState;

    //Functions for moving around inside the file.
    Token getNextToken( char *delim, int length );
    void skipToNextLine();
    
    //Functions for handling the structs defined in file
    BaseStruct processLifeStruct();

    //Functions for parsing the smaller sections of the Structs
    Grid processInititalLayout( );
    grid_dimension processTerrain( );
    std::map< Grid::cell_state, int > processChars();
    std::map< Grid::cell_state, Color > processColors();
        
    //Functions for parsing inside the smaller sections
    Color parseColor( std::string content );
    Point parsePoint( std::string content );
    
    Point parseDotRange( std::string content );
    
    bool onlyDigits( char *ptr );
    int isInDelim( char value, char *ptr, int length );
 
};

#endif	/* FILEPARSER_H */

