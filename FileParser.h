/* 
 * File:   FileParser.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:32 PM
 */

#ifndef FILEPARSER_H
#define	FILEPARSER_H

#include <string>

#include "BaseStruct.h"
#include "Point.h"
#include "Color.h"

class FileParser {
public:
    
    FileParser( FILE *file );

    BaseStruct& getNext();
    bool hasNext();

private:

    enum ParseState {
        START, DONE, LIFE_START, PROCESS_GRID_STRUCT, PROCESS_COLOR, PROCESS_CHARS
    };

    FILE *input;
    ParseState state;

    std::string getNextToken( char delim );
    void skipToNextLine();
    BaseStruct& processLifeStruct();
    
    Color parseColor( std::string content );
    Point parsePoint( std::string content );
    Grid processAliveCells( std::string content );
};

#endif	/* FILEPARSER_H */

