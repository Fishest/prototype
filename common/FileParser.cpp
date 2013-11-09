#include <stdio.h>
#include <string>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "FileParser.h"
#include "CustomException.h"
#include "Grid.h"
#include "LifeStruct.h"
#include "Token.h"

FileParser::FileParser(FILE* file){
    input = file;
    state = FileParser::NOTHING;
}

FileParser::FileParser( std::string filename ){
    
    input = fopen( filename.c_str(), "r");
    if( input == NULL ){
        throw new CustomException( CustomException::INVALID_FILENAME );
    }
    state = FileParser::NOTHING;    
}

FileParser::~FileParser(){
}

BaseStruct* FileParser::getNext(){
    
    if( hasNext() ){
        if( state == FileParser::LIFE_START ){
            return processLifeStruct();
        }
        else{
            throw new CustomException( CustomException::NO_NEXT_STRUCT );
        }
    }
    else{
        throw new CustomException( CustomException::NO_NEXT_STRUCT );
    }  
}

bool FileParser::hasNext(){
    
    Token tok;
    
    if( state == FileParser::LIFE_START ){
        return true;
    }
    
    try{
        tok = getNextToken( "=", 1);
        if( tok.getContent().find( "Life" ) != tok.getContent().npos ){
            state = FileParser::LIFE_START;
        }
        else{
            return false;
        }
        return true;
    }catch( CustomException a){
        return false;
    }
}

/**
 * Function will take a string with values of the form lower..higher. This
 * string will then be parsed and returned as a point in the form of ( lower, higher).
 * @param content String representation of a range.
 * @return Point object corresponding to that range.
 */
Point FileParser::parseDotRange( std::string content ){
    
    //Use strtok to parse the ranges from the string.
    char *ptr = NULL;
    Point values; 
    
    int length = content.length();
    char buffer[length + 1];
    bzero( buffer, length + 1 );
    
    int index = 0;
    for( index= 0; index < length; index++) {
        buffer[index] = content.at( index );
    }

    ptr = strtok( buffer, "..");
    if( ptr !=  NULL && FileParser::onlyDigits( ptr ) ){
        values.setFirst( atoi( ptr ) );
    }
    else{
        throw new CustomException( CustomException::INVALID_RANGE );
    }
    
    ptr = strtok( NULL, "..");
    if( ptr != NULL && FileParser::onlyDigits( ptr ) ){
        values.setSecond( atoi( ptr ) );
    }
    else{
        throw new CustomException( CustomException::INVALID_RANGE );
    }
    
    if( values.getSecond() < values.getFirst() ){
        throw new CustomException( CustomException::INVALID_RANGE );
    }
    
    return values;    
}


//////////////////////////////////////////////Private Functions////////////////////////////////////////

Token FileParser::getNextToken( char *delim, int length ){
    
    const int bufferSize = 4000;
    
    char buffer[bufferSize];
    char workBuf[5];
    int index = 0;
    int insertIndex = 0;
    int result = 0;
    bool quoteFound = false;
    
    int delFound = -1;
    
    bzero( buffer, bufferSize);
    bzero( workBuf, 5);
    
    while( index < bufferSize ){
        bzero( workBuf, 5);
        
        /*
         * Reads the next byte from the input file and handles any possible errors
         * that were encountered.
         */
        result = fread( workBuf, 1, 1, input);
        if( result <= 0 ){
            
            if( feof( input ) ){
                throw new CustomException( CustomException::PREMATURE_EOF );
            }
            else if( ferror( input ) ){
                
                break;
            }
        }
        
        if( workBuf[0] == '#' ){
            /*
             * If the # is seen then the rest of the line should be ignored.
             */
            skipToNextLine();
        }
        /*
         * Determine if collection needs to cease as a result of running into the delimiter.
         */
        else if( (delFound = isInDelim( workBuf[0], delim, length )) > 0 ){
            break;
        }
        /*
         * Toggles the quoteFound variable. This is important because whitespace that is within
         * a quotation mark is important.
         */
        else if( workBuf[0] == '\"' ){
            if( quoteFound )
                quoteFound = false;
            else
                quoteFound = true;
        }
        /*
         * Determine if the element is white space or something else.
         */
        else if( !isspace( workBuf[0] ) ){
            
            /*
             * We found a character that isn't any form of white space. It needs to be
             * added to the buffer to be returned.
             */
            buffer[insertIndex++] = workBuf[0];
        }
        else if( quoteFound && isspace( workBuf[0] ) ){
            buffer[insertIndex++] = workBuf[0];
        }
        
        index++;
        
    } //Ends while loop
     
    if( index >= bufferSize ){
        throw new CustomException( CustomException::NOT_ENOUGH_BUFFER_FOR_TOKEN );
    }
    
    //Time to build string that will be returned.
    std::string retVal( buffer );
    Token tok( delFound, retVal );
   
    return tok;    
}

Token FileParser::getNextTokenIgnoreParen( char *delim, int length){

    const int bufferSize = 4000;
    
    char buffer[bufferSize];
    char workBuf[5];
    int index = 0;
    int insertIndex = 0;
    int result = 0;
    bool quoteFound = false;
    
    int delFound = -1;
    
    bzero( buffer, bufferSize);
    bzero( workBuf, 5);
    
    while( index < bufferSize ){
        bzero( workBuf, 5);
        
        /*
         * Reads the next byte from the input file and handles any possible errors
         * that were encountered.
         */
        result = fread( workBuf, 1, 1, input);
        if( result <= 0 ){
            
            if( feof( input ) ){
                throw new CustomException( CustomException::PREMATURE_EOF );
            }
            else if( ferror( input ) ){
                
                break;
            }
        }
        
        if( workBuf[0] == '#' ){
            /*
             * If the # is seen then the rest of the line should be ignored.
             */
            skipToNextLine();
        }
        /*
         * Determine if collection needs to cease as a result of running into the delimiter.
         */
        else if( (delFound = isInDelim( workBuf[0], delim, length )) > 0 && !quoteFound ){
            break;
        }
        /*
         * Toggles the quoteFound variable. This is important because whitespace that is within
         * a quotation mark is important.
         */
        else if( workBuf[0] == '(' ){
            buffer[insertIndex++] = workBuf[0];
            quoteFound = true;
        }
        else if( workBuf[0] == ')' ){
            buffer[insertIndex++] = workBuf[0];
            quoteFound = false;
        }
        /*
         * Determine if the element is white space or something else.
         */
        else if( !isspace( workBuf[0] ) ){
            
            /*
             * We found a character that isn't any form of white space. It needs to be
             * added to the buffer to be returned.
             */
            buffer[insertIndex++] = workBuf[0];
        }
        else if( quoteFound && isspace( workBuf[0] ) ){
            buffer[insertIndex++] = workBuf[0];
        }
        
        index++;
        
    } //Ends while loop
     
    if( index >= bufferSize ){
        throw new CustomException( CustomException::NOT_ENOUGH_BUFFER_FOR_TOKEN );
    }
    
    //Time to build string that will be returned.
    std::string retVal( buffer );
    Token tok( delFound, retVal );
   
    return tok;    
}

Color FileParser::parseColor(std::string content){
    
    char buffer[100];
    unsigned int insertIndex = 0;
    unsigned int index = 0;
    unsigned int state = 0;
    int red = -1, green = -1, blue = -1;
    
    bzero( buffer, 100);
    
    while( index++ < content.size() && insertIndex < 100 ){
        
        /*
         * Makes sure the parenthesis and white space is ignored during the processing of the color information.
         */
        if( content[index] != '(' && !isspace( content[index] ) ){
            
            /*
             * If the current character is a comma then it's time to break apart and parse the content
             * within the buffer.
             */
            if( content[index] == ',' || content[index] == ')' ){
                
                /*
                 * If comma is seen then the content in the buffer needs to be processed.
                 */
                
                int temp = atoi( buffer );
                if( temp < 0 || temp > 255 ){
                    throw new CustomException( CustomException::INVALID_COLOR );
                }
                
                if( state == 0 ){
                    red = temp;
                    state++;
                }else if( state == 2 ){
                    blue = temp;
                    break;
                }else if( state == 1 ){
                    green = temp;
                    state++;
                }
                
                insertIndex = 0;
                bzero( buffer, 100);
                
            } //Ends comma if statement
            else{
                /*
                 * At this point, the character can't be whitespace, comma or parentheses.
                 * The content needs to be copied into the buffer for later processing.
                 */
                buffer[insertIndex++] = content[index];
            }
        }
    } //Ends while loop
    
    if( index >= content.size() || insertIndex >= content.size() ){
        throw new CustomException( CustomException::INVALID_COLOR );
    }
    
    /*
     * Make sure that a valid value was found for each of the colors in string.
     */
    if( red < 0 || green < 0 || blue < 0 )
        throw new CustomException( CustomException::INVALID_COLOR );
    
    //Returns a copy of the representative Color object
    Color temp( red, green, blue);
    
    return temp;
}

Point FileParser::parsePoint(std::string content){
    
    char buffer[100];
    unsigned int insertIndex = 0;
    unsigned int index = 0;
    int state = 0;
    int val1 = 0, val2 = 0;
    bool val1Found = false;
    bool val2Found = false;
    
    bzero( buffer, 100);
    
    while( index++ < content.size() && insertIndex < 100 ){
        
        /*
         * Makes sure the parenthesis and white space is ignored during the processing of the color information.
         */
        if( content[index] != '(' && !isspace( content[index] ) ){
            
            /*
             * If the current character is a comma then it's time to break apart and parse the content
             * within the buffer.
             */
            if( content[index] == ',' || content[index] == ')' ){
                
                /*
                 * If comma is seen then the content in the buffer needs to be processed.
                 */
                
                int temp = atoi( buffer );
                
                if( state == 0 ){
                    val1 = temp;
                    val1Found = true;
                    state++;
                }else if( state == 1 ){
                    val2 = temp;
                    val2Found = true;
                    break;
                }
                
                bzero( buffer, 100);
                insertIndex = 0;
                
            } //Ends comma if statement
            else{
                /*
                 * At this point, the character can't be whitespace, comma or parentheses.
                 * The content needs to be copied into the buffer for later processing.
                 */
                buffer[insertIndex++] = content[index];
            }
        }
    } //Ends while loop
    
    if( index >= content.size() || insertIndex >= content.size() ){
        throw new CustomException( CustomException::INVALID_POINT );
    }
    
    if( val1Found == false || val2Found == false )
        throw new CustomException( CustomException::INVALID_POINT );
    
    Point temp( val1, val2);
    
    return temp;    
}

void FileParser::skipToNextLine(){
    
    int index = 0;
    char value[2];
    
    bzero( value, 2);
    
    while( value[0] != '\n' ){
        //Need to read from file until \n is seen.
        
        index = fread( value, 1, 1, input);
        if( index <= 0 ){
            
            if( feof( input ) ){
                return;
            }
            else if( ferror( input ) ){
                throw new CustomException( CustomException::INVALID_FILE );
            }
        }
        
    } //Ends while loop
}

Grid FileParser::processInititalLayout( ){
    
    Grid data( defaultState );
    
    Grid::cell_state currentState;
    int state = 0;
    
    /*
     * ZERO
     * Haven't found a state header as of yet. Need to find the header prior to 
     * processing point.
     * 
     * ONE
     * Found a header for the state. Now, looking for the points in the Grid that 
     * should contain the previously found state.
     */
    
    Token tok = getNextTokenIgnoreParen( "{", 1);
    while( tok.getMatachedDelim() != '}' ){
        
        if( state == 0 && tok.getMatachedDelim() == '=' ){
            //Found the header to be working with.
            state = 1;
            
            //Map the read content to a defined state value.
            if( tok.getContent().find( "Alive" ) != tok.getContent().npos ){
                currentState = Grid::ALIVE;
            }
            else if( tok.getContent().find( "Dead" ) != tok.getContent().npos ){
                currentState = Grid::DEAD;
            }
            else{
                throw new CustomException( CustomException::INVALID_CELL_STATE_FOUND );
            }
            
        }
        else if( state == 1 && ( tok.getMatachedDelim() == ',' || tok.getMatachedDelim() == ';' ) ){
            //Found another point in the file that needs to be processed and added to the map.
           
            Point pt = parsePoint( tok.getContent() );
            
            //Update the Grid with the newly found point
            data.set( pt, currentState );   

            //Found the last point and thus we want to switch to state of needing a new header.
            if( tok.getMatachedDelim() == ';' )
                state = 0;        
        }
        
        //Grab the next token from the file.
        tok = getNextTokenIgnoreParen( ",=;}", 4);
        
    } //Ends the while loop
    
    //Reads the final semi-colon after the struct.
    getNextTokenIgnoreParen( ";", 1);
    
    return data;   
}

grid_dimension FileParser::processTerrain(){
    grid_dimension grid;
    
    bool xFound = false;
    bool yFound = false;
    
    //Skip all content prior to the open curly brace
    getNextToken("{", 1);
    
    /*
     * Collect all the headers and values from the terrain
     * section. They will now be parsed and stored inside a grid_dimension
     * prior to being returned.
     */
    Token header = getNextToken("=", 1);
    Token value = getNextToken(";", 1);
    
    Token header2 = getNextToken("=", 1);
    Token value2 = getNextToken(";", 1);
    
    Point pt1 = parseDotRange( value.getContent() );
    Point pt2 = parseDotRange( value2.getContent() );
    
    //Processes the first header that was found.
    if( header.getContent().find( "Xrange" ) != header.getContent().npos ){
        grid.xVals = pt1;
        xFound = true;
    }
    else if( header.getContent().find( "Yrange" ) != header.getContent().npos ){
        grid.yVals = pt1;
        yFound = true;
    }
   
    //Processes the second header that found.
    if( header2.getContent().find( "Xrange" ) != header2.getContent().npos ){
        if( xFound )
            throw new CustomException( CustomException::INVALID_TERRAIN_WINDOW );
        
        grid.xVals = pt2;
    }
    if( header2.getContent().find( "Yrange" ) != header2.getContent().npos ){
        if( yFound )
            throw new CustomException( CustomException::INVALID_TERRAIN_WINDOW );
        
        grid.yVals = pt2;
    }
    
    getNextToken(";", 1);
    
    return grid;
}

BaseStruct* FileParser::processLifeStruct(){
    
    defaultState = Grid::DEAD;

    bool terrainDefined = false;
    bool charsDefined = false;
    bool colorsDefined = false;
    bool initialDefined = false;

    LifeStruct *life = new LifeStruct();
    
    Token tok = getNextToken( "{", 1);
    ParseState state = FileParser::LIFE_START;
    
    while( tok.getMatachedDelim() != '}' ){
        
        if( state == FileParser::LIFE_START && tok.getMatachedDelim() == '=' ){
            //Found a value header
           
            if( tok.getContent().find( "Name" ) != tok.getContent().npos ){
                tok = getNextToken(";", 1);
                 life->setName( tok.getContent() );
                 state = FileParser::LIFE_START;
            }
            else if( tok.getContent().find( "Terrain" ) != tok.getContent().npos ){
                grid_dimension dimen = processTerrain();
                life->setTerrain( dimen );
                terrainDefined = true;
                state = FileParser::LIFE_START;
            }
            else if( tok.getContent().find( "Window" ) != tok.getContent().npos ){
                grid_dimension dimen = processTerrain();
                life->setWindow( dimen );
                state = FileParser::LIFE_START;
            }
            else if( tok.getContent().find( "Chars" ) != tok.getContent().npos ){
                std::map< Grid::cell_state, int > temp = processChars();
                life->setCharMap( temp );
                charsDefined = true;
                state = FileParser::LIFE_START;
            }
            else if( tok.getContent().find( "Colors" ) != tok.getContent().npos ){
                std::map< Grid::cell_state, Color> temp = processColors();
                life->setColorMap( temp );
                colorsDefined = true;
                state = FileParser::LIFE_START;
            }
            else if( tok.getContent().find( "Initial" ) != tok.getContent().npos ){
                Grid temp = processInititalLayout();
                life->setGrid( temp );
                initialDefined = true;
                state = FileParser::LIFE_START;
            }
        }
        
        if( state == FileParser::LIFE_START ){
                tok = getNextToken( "=}", 2);
            }
        
    } //Ends while loop

    if( !terrainDefined || !charsDefined || !colorsDefined ){
        throw new CustomException( CustomException::INVALID_FILE );
    }
    
    //Get rid of trailing semi-colon
    getNextToken( ";" , 1);
    
    return life;  
}

std::map< Grid::cell_state, int> FileParser::processChars(){
    
    std::map< Grid::cell_state, int > chars;
    
    int state = 0;
    Grid::cell_state foundState;
    
    //Move over the open curly brace
    Token worker = getNextToken("{", 1);
    
    while( worker.getMatachedDelim() != '}'){
        
        worker = getNextToken( "=;}", 3);
        
        if( state == 0 && worker.getMatachedDelim() == '}' ){
            /*
             * Reached the end of the chars struct
             */
            break;            
        }
        else if( state == 0 && worker.getMatachedDelim() == '=' ){
            //TODO Determine if having multiple Alive or Dead declarations within the color struct will
            //just overwrite he previously seen value.
            
            /*
             * About ready to process the next header
             */
            state = 1;
            
            //Map the string representation of the state to the enum.
            //Note: This could potentially be redone to use abstraction among classes for autodetection of support.
            if( worker.getContent().find("Alive") != worker.getContent().npos ){
                foundState = Grid::ALIVE;
            }
            else if( worker.getContent().find("Dead") != worker.getContent().npos ){
                foundState = Grid::DEAD;
            }
            
        }
        else if( state == 1 && worker.getMatachedDelim() == ';' ){
            /*
             * The character value was found and needs to be processed at this point.
             */
            state = 0;
            
            //Add the newly found state to the mapping
            int ch = atoi( worker.getContent().c_str() );
	    if( ch < 0 || ch >= 256 )
	    	throw new CustomException( CustomException::INVALID_CHAR );

            chars.insert( std::pair< Grid::cell_state, int>( foundState, ch) );
        }
        
        
    }// ends while loop
    
    getNextToken(";", 1);
    
    return chars;   
}

std::map< Grid::cell_state, Color> FileParser::processColors(){
    
    std::map< Grid::cell_state, Color > colors;
    
    Token tok = getNextToken("{", 1);
    Grid::cell_state stateHeader;
    Color value;
    int state = 0;
    
    while( tok.getMatachedDelim() != '}' ){
        
        
        if( state == 1 && tok.getMatachedDelim() == '=' ){
            //Two headers in a row have been found in the provided file. This isn't valid
            //and thus needs to be reported.
            throw new CustomException( CustomException::INVALID_COLOR_STRUCT );
        }
        else if( state == 0 && tok.getMatachedDelim() == '='){
            //A header was found.
            if( tok.getContent().find("Alive") != tok.getContent().npos ){
                stateHeader = Grid::ALIVE;
                state = 1;
            }
            else if( tok.getContent().find( "Dead" ) != tok.getContent().npos ){
                stateHeader = Grid::DEAD;
                state = 1;
            }
        }
        else if( state == 1 && tok.getMatachedDelim() == ';' ){
            value = parseColor( tok.getContent() );
            state = 0;
            
            //Add the newly found header value pair to the mapping
            colors.insert( std::pair< Grid::cell_state, Color>(stateHeader, value) );
        }
        
        /*
         * Grabs the next token from the file. It will consider a token to be the content
         * , ignoring whitespace, that is between current location and the first occurence
         * of one of the provided delimeter characters.
         */
        tok = getNextToken( "=;}", 3);
        
    } //Ends while loop
    
    //Scan through the remaining semi-colon at the end of the struct.
    tok = getNextToken(";", 1);
    
    return colors;
    
}

bool FileParser::onlyDigits( char *ptr ){
    
    while( ptr != NULL && *ptr != 0 ){
        if( !( (*ptr >= 48 && *ptr <= 57) || *ptr == '-' ) ){
            return false;
        }
        ptr++;
    }
    return true;
}

int FileParser::isInDelim( char value, char *ptr, int length ){
    int index = 0;
    
    for( index = 0; index < length && ptr != NULL; index++){
        if( value == ptr[index] ){
            return ptr[index];
        }
    }
    
    return -1;
}

