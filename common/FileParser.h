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
#include "LifeStruct.h"

/**
 * The FileParser class handles the parsing of the configuration files. It provides a scanner style
 * of interface to parsing the files. The class works by parsing the structs of the file one at a time
 * and returning a new object with each of the structs defined in the file.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class FileParser {
public:
    
    FileParser( FILE *file );
    FileParser( std::string filename );
    ~FileParser();

    /**
     * Grabs the next struct from the specified file. The next struct in the file is parsed
     * and stored in a BaseStruct class.
     *
     * @return Pointer to the BaseStruct that contains all the data from the file.
     */
    BaseStruct* getNext();

    /**
     * Determines if there are any more supported structs left within the given file.
     *
     *@ return True if struct remains. False otherwise.
     */
    bool hasNext();

    /**
     * Parses a range that is specified in the the low..high format. This format is used
     * throughout the configuration files and command line arguments.
     *
     * @param content String that contains the content to be parsed.
     * @return Point Contains the parsed values with low being placed in first element.
     * @throws CustomException In the event that an error occurs during processing.
     */
    static Point parseDotRange( std::string content );

    /**
     * Determines if the string at the provided pointer contains only numerical data. This
     * is used throughout the program to make sure that valid input is provided as parameters
     * in the file and command line arguments.
     *
     * @param ptr Pointer to a character array that should be tested for non-numerical data.
     * @return True if only numerical values, false otherwise.
     */
    static bool onlyDigits( char *ptr );

private:

    enum ParseState {
        NOTHING, START, DONE, STRUCT_START
    };

    FILE *input;
    ParseState state;
    Grid::cell_state defaultState;
	BaseStruct *base;

    /**
     * This FileParser works by using a custom built tokenizer for the file.
     * The tokenizer filters the files content as it's reading the content.
     * Specifically, it ignores all spaces and automatically removes any commented
     * lines as it's reading. The function will continue reading all the content
     * in the file until a specific character is run across. These characters are
     * used as a delimiter that should result in the founding of a new Token.
     *
     * @param delim Array of characters that should be used as a delimiter for the next token.
     * @param length Number of delimiters in the provided delimeter string.
     * @return Token that contains the content from the file.
     */
    Token getNextToken( char *delim, int length );

    /**
     * Operates exactly the same as getNextToken with one added feature. This function will ignore
     * the characters in the delimiter parameter if they are within a set of parenthesis. This is
     * useful when processing the initital layout section of the file.
     *
     * @param delim Array of characters that should be used as a delimiter for the next token.
     * @param length Number of delimiters in the provided delimeter string.
     * @return Token that contains the content from the file.
     */
    Token getNextTokenIgnoreParen( char *delim, int length);

    /**
     * Continues reading through the FILE until a new line has been found. Thus,
     * this function handles the skipping of the content found directly after a 
     * # symbol has been found in the file.
     */
    void skipToNextLine();
    
    /**
     * A configuration file could contain any number of different types of structs. In the event
     * that a Life struct is found, this function will handle the parsing of the file associated
     * with the Life Struct. The function will store all the data in a LifeStruct on the heap. A
     * BaseStruct pointer will be returned from this function. The calling function can determine
     * that the struct is actually a LifeStruct by looking at the type associated with it. The caller
     * assumes the responsibility of freeing the memory when the LifeStruct is no longer needed.
     *
     * @return Pointer to the LifeStruct on the heap that contains the information from the struct.
     */
    BaseStruct* processLifeStruct();

	void processStruct( BaseStruct *base );

    /**
     * Handles the processing of the initial layout section within the configuration files. The function
     * will populate a Grid object that can be used to represent the files contents.
     *
     * @return Grid object that represents the state marked within the configuration file.
     */
    Grid processInititalLayout( );

    /**
     * Processes the terrain struct within the configuration files. The terrain struct consists of a series
     * of ranges that reflect the X and Y coordinates that are used for calculating the next generation.
     *
     * @return grid_dimension Contains the terrain range of the configuration file.
     * @throws CustomException If an error is encountered during processing of the terrain.
     */
    grid_dimension processTerrain( );

    /**
     * Processes the characters that should be used to represent the different states within the ascii
     * visual mode. The characters are stored in a map with the state being the key. The map allows
     * for quick and extendable way to process the configuration file.
     *
     * @return Map that contains a mapping for each of the states.
     */
    std::map< Grid::cell_state, int > processChars();

    /**
     * Process the colors that should be used to represent the different states within the QT application.
     * A map of the state to the corresponding color is returned after processing the Colors struct. The
     * map allows for efficient and extendable storage of the color data. Adding or updating colors becomes
     * a simple operation through the use of the map.
     *
     * @return Map that contains a mapping for each state to the corresponding color.
     */
    std::map< Grid::cell_state, Color > processColors();
        
    /**
     * Parses the color values out of the given string. The color object is expected to
     * be of a Red, Green, Blue format. The function will handle any extra spacings or 
     * comments that may be seen within the file. The String must contain three valid
     * values that are seperated by a comma.
     *
     * @param content String that contains the color values that need to be parsed.
     * @return Color object that contains the color values in the string.
     * @throws CustomException if the specified string isn't properly formatted.
     */
    Color parseColor( std::string content );

    /**
     * Parses the provided string in an effort to pull the tuple of values. The numbers should be
     * separated by a comma within string. The function will handle extra spacing as well as comments
     * that may have been added to the string.
     *
     * @param content String that contains the content that needs to be parsed.
     * @return Point that contains the values from the provided string.
     */
    Point parsePoint( std::string content );
    
    /**
     * Determines if the provided character is within the provided list of delimiters.
     *
     * @param value The value to look for in the list.
     * @param ptr Pointer to the list of delimiters.
     * @param length Number of elements in the provided list.
     * @return Ascii value of the delimiter that was matched.
     */
    int isInDelim( char value, char *ptr, int length );
 
};

#endif	/* FILEPARSER_H */

