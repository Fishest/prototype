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
#include "WireWorldStruct.h"
#include "BaseStruct.h"
#include "ElementaryStruct.h"

FileParser::FileParser(FILE* file){
    input = file;
    state = FileParser::NOTHING;
	defaultState = Grid::UNKNOWN;
	base = NULL;
}

FileParser::FileParser( std::string filename ){
    
    input = fopen( filename.c_str(), "r");
    if( input == NULL ){
        throw CustomException( CustomException::INVALID_FILENAME );
    }
    state = FileParser::NOTHING;    
	defaultState = Grid::UNKNOWN;
	base = NULL;
}

FileParser::~FileParser(){
}

BaseStruct* FileParser::getNext(){

	/*
	   The FileParser looks at the file as a series of structs followed by each other. For instance,
	   there might be a Life struct as well as a WireFrame struct among others. With this being the case,
	   the getNext function will grab and parse the next large struct, such as Life, from the file and 
	   return a reference to it. This design allows for more controlled processing of the configuration
	   file. It also allows for less memory usage than if the application were to process all the structs
	   in the file at the same time.

	   This follows the design of the Scanner class from java language.
	   */

    if( hasNext() ){
		processStruct( base );
		BaseStruct *temp = base;
		base = NULL;
		return temp;
    }
    else{
        throw CustomException( CustomException::NO_NEXT_STRUCT );
    }  
}

bool FileParser::hasNext(){

	/*
	   Determines if there is another struct in the input file that needs to be processed
	   within the file.
	   */
    Token tok;
    
    if( base != NULL ){
        return true;
    }
    
    try{
        tok = getNextToken( "=", 1);
        if( tok.getContent().find( "Life" ) != tok.getContent().npos ){
			base = new LifeStruct(); 
        }
		else if( tok.getContent().find( "WireWorld" ) != tok.getContent().npos ){
			base = new WireWorldStruct();
		}
		else if( tok.getContent().find( "Elementary" ) != tok.getContent().npos ){
			base = new ElementaryStruct();
		}
        else{
			base = NULL;
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
    
	/*
	   Copies the string content into a character buffer that can
	   then be used with the strtok function.
	   */
    int index = 0;
    for( index= 0; index < length; index++) {
        buffer[index] = content.at( index );
    }

	/*
	   The following code handles breaking apart the string by splitting it
	   based on the ".." delimiter. The values are then converted to an integer.
	   */
    ptr = strtok( buffer, "..");
    if( ptr !=  NULL && FileParser::onlyDigits( ptr ) ){
        values.setFirst( atoi( ptr ) );
    }
    else{
        throw CustomException( CustomException::INVALID_RANGE );
    }
    
    ptr = strtok( NULL, "..");
    if( ptr != NULL && FileParser::onlyDigits( ptr ) ){
        values.setSecond( atoi( ptr ) );
    }
    else{
        throw CustomException( CustomException::INVALID_RANGE );
    }
    
    if( values.getSecond() < values.getFirst() ){
        throw CustomException( CustomException::INVALID_RANGE );
    }
    
    return values;    
}

bool FileParser::onlyDigits( char *ptr ){
   
	/*
	   Scans through the pointer to make sure that only the negative sign and numbers
	   are present within the given buffer.
	   */
    while( ptr != NULL && *ptr != 0 ){
        if( !( (*ptr >= 48 && *ptr <= 57) || *ptr == '-' ) ){
            return false;
        }
        ptr++;
    }
    return true;
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
                throw CustomException( CustomException::PREMATURE_EOF );
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
        throw CustomException( CustomException::NOT_ENOUGH_BUFFER_FOR_TOKEN );
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
                throw CustomException( CustomException::PREMATURE_EOF );
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
        throw CustomException( CustomException::NOT_ENOUGH_BUFFER_FOR_TOKEN );
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
             * within the buffer. Also need to break when the closing parenthesis is seen.
             */
            if( content[index] == ',' || content[index] == ')' ){
                
                /*
                 * If comma is seen then the content in the buffer needs to be processed.
                 */
                
                int temp = atoi( buffer );
                if( temp < 0 || temp > 255 ){
                    throw CustomException( CustomException::INVALID_COLOR );
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
        throw CustomException( CustomException::INVALID_COLOR );
    }
    
    /*
     * Make sure that a valid value was found for each of the colors in string.
     */
    if( red < 0 || green < 0 || blue < 0 )
        throw CustomException( CustomException::INVALID_COLOR );
    
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
        throw CustomException( CustomException::INVALID_POINT );
    }
    
    if( val1Found == false || val2Found == false )
        throw CustomException( CustomException::INVALID_POINT );
    
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
                throw CustomException( CustomException::INVALID_FILE );
            }
        }
        
    } //Ends while loop
}

Grid FileParser::processInititalLayout( ){
    
    Grid data( defaultState );
    
    Grid::cell_state currentState = Grid::UNKNOWN;
    int state = 0;
    
    /*
	 * The intital layout is processed around a finite state machine, like most processing. The methods
	 * of processing the found content differ depending on the current state of the application. The 
	 * states are outlined below in what each one refers to.
	 *
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

			//Map the read content to a defined state value
			currentState = Grid::convertState( tok.getContent() );
                       
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

	bool processingX = false;

    Token tok = getNextToken("{", 1);
    int state = 0;
    
    while( tok.getMatachedDelim() != '}' ){
        
        
        if( state == 1 && tok.getMatachedDelim() == '=' ){
            //Two headers in a row have been found in the provided file. This isn't valid
            //and thus needs to be reported.
            throw CustomException( CustomException::INVALID_TERRAIN_STRUCT );
        }
        else if( state == 0 && tok.getMatachedDelim() == '='){
            //A header was found.
 			state = 1;

			if( tok.getContent().find( "Xrange" ) != tok.getContent().npos ){
				processingX = true;
				if( xFound )
					throw CustomException( CustomException::INVALID_TERRAIN_STRUCT );
				xFound = true;
			}
			else if( tok.getContent().find( "Yrange" ) != tok.getContent().npos ){
				processingX = false;
				if( yFound )
					throw CustomException( CustomException::INVALID_TERRAIN_STRUCT );
				yFound = true;
			}
			else{
				throw CustomException( CustomException::INVALID_TERRAIN_STRUCT );
			}

        }
        else if( state == 1 && tok.getMatachedDelim() == ';' ){
            state = 0;

			Point pt1 = parseDotRange( tok.getContent() );
			if( processingX ){
				grid.xVals = pt1;
			}
			else{
				grid.yVals = pt1;
			}
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

	if( !xFound || !yFound )
		throw CustomException( CustomException::INVALID_TERRAIN_STRUCT );
    
    return grid;
}

void FileParser::processStruct( BaseStruct *base ){

	//Obtain the default state from the underlying struct
	defaultState = base->getDefaultState();

    bool terrainDefined = false;
    bool charsDefined = false;
    bool colorsDefined = false;
    bool initialDefined = false;

    Token tok = getNextToken( "{", 1);
    ParseState state = FileParser::STRUCT_START;
    
    while( tok.getMatachedDelim() != '}' ){
        
        if( state == FileParser::STRUCT_START && tok.getMatachedDelim() == '=' ){
          
			/*
			   At this point, a header value has been found from the getNextToken function. The next
			   step is to determine which type struct the header was for. Once that is determined, the
			   program will continue by calling the appropriate processing function to obtain the
			   value portion of the header that was found.
			   */
            if( tok.getContent().find( "Name" ) != tok.getContent().npos ){

				//Found the optional name header
                tok = getNextToken(";", 1);
                 base->setName( tok.getContent() );
                 state = FileParser::STRUCT_START;
            }
            else if( tok.getContent().find( "Terrain" ) != tok.getContent().npos ){

				//Found the Terrain portion of the configuration file
                grid_dimension dimen = processTerrain();
                base->setTerrain( dimen );
                terrainDefined = true;
                state = FileParser::STRUCT_START;
            }
            else if( tok.getContent().find( "Window" ) != tok.getContent().npos ){

				//Found the optional Window parameter of the configuration file. The
				//window value format is consisten with the terrain and thus the same
				//processing function is used.
                grid_dimension dimen = processTerrain();
                base->setWindow( dimen );
                state = FileParser::STRUCT_START;
            }
            else if( tok.getContent().find( "Chars" ) != tok.getContent().npos ){

				//Character map has been found within the file.
                std::map< Grid::cell_state, int > temp = processChars();
                base->setCharMap( temp );
                charsDefined = true;
                state = FileParser::STRUCT_START;
            }
            else if( tok.getContent().find( "Colors" ) != tok.getContent().npos ){

				//Color map has been found within the file.
                std::map< Grid::cell_state, Color> temp = processColors();
                base->setColorMap( temp );
                colorsDefined = true;
                state = FileParser::STRUCT_START;
            }
            else if( tok.getContent().find( "Initial" ) != tok.getContent().npos ){

				//The initial layout section has been found.
                Grid temp = processInititalLayout();
                base->setGrid( temp );
                initialDefined = true;
                state = FileParser::STRUCT_START;
            }
			else if( tok.getContent().find( "Rule" ) != tok.getContent().npos ){

				tok = getNextToken( ";", 1 );
				int value = atoi( tok.getContent().c_str() );
				if( value < 0 || value >= 512 ){
					throw CustomException( CustomException::INVALID_RULE_VALUE );
				}

				if( base->getType() != BaseStruct::ELEMENTARY )
				{
					throw CustomException( CustomException::INVALID_STRUCT_TYPE );
				}

				ElementaryStruct * el = (ElementaryStruct*) base;
				el->setRule( value );

				state = FileParser::STRUCT_START;
			}
        }
       
		/*
		   Need to grab the next section of the files content up to either an '=' or a '}' character
		   is found. In the event that an '}' is found, the end of the Life Struct has been found.
		   */
        if( state == FileParser::STRUCT_START ){
                tok = getNextToken( "=}", 2);
        }
        
    } //Ends while loop

	/*
	   Make sure that all the required sections have been defined.
	   */
    if( !terrainDefined || !charsDefined || !colorsDefined ){
        throw CustomException( CustomException::INVALID_FILE );
    }
    
    //Get rid of trailing semi-colon
    getNextToken( ";" , 1);
}

std::map< Grid::cell_state, int> FileParser::processChars(){
    
    std::map< Grid::cell_state, int > chars;
    
    int state = 0;
    Grid::cell_state foundState = Grid::UNKNOWN;
    
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
            /*
             * About ready to process the next header
             */
            state = 1;
            
            //Map the string representation of the state to the enum.
            //Note: This could potentially be redone to use abstraction among classes for autodetection of support.
			foundState = Grid::convertState( worker.getContent() );
            
        }
        else if( state == 1 && worker.getMatachedDelim() == ';' ){
            /*
             * The character value was found and needs to be processed at this point.
             */
            state = 0;
            
            //Add the newly found state to the mapping
            int ch = atoi( worker.getContent().c_str() );
			if( ch < 0 || ch >= 256 )
				throw CustomException( CustomException::INVALID_CHAR );

			//Adds the new character code into the mapping
			chars.insert( std::pair< Grid::cell_state, int>( foundState, ch) );
		}
        
        
    }// ends while loop
    
    getNextToken(";", 1);
    
    return chars;   
}

std::map< Grid::cell_state, Color> FileParser::processColors(){
    
    std::map< Grid::cell_state, Color > colors;
    
    Token tok = getNextToken("{", 1);
    Grid::cell_state stateHeader = Grid::UNKNOWN;
    Color value;
    int state = 0;
    
    while( tok.getMatachedDelim() != '}' ){
        
        
        if( state == 1 && tok.getMatachedDelim() == '=' ){
            //Two headers in a row have been found in the provided file. This isn't valid
            //and thus needs to be reported.
            throw CustomException( CustomException::INVALID_COLOR_STRUCT );
        }
        else if( state == 0 && tok.getMatachedDelim() == '='){
            //A header was found.
 			state = 1;
			stateHeader = Grid::convertState( tok.getContent() );
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

int FileParser::isInDelim( char value, char *ptr, int length ){
    int index = 0;
    
    for( index = 0; index < length && ptr != NULL; index++){
        if( value == ptr[index] ){
            return ptr[index];
        }
    }
    
    return -1;
}



