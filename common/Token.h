#ifndef TOKEN_H
#define	TOKEN_H

#include <string>

/**
 * A Token is a result from performing a getNextToken function call from the FileParser class.
 * A Token is used to represent a collection of content from a provided file. The Token allows
 * for extracting the desired content from the file. It also provides a means for identifying
 * on which delimiter the FileParser functions completed. It often times becomes important to 
 * know which delimiting character was matching to know how to handle the following content from
 * the file.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class Token{
    
public:

	/**
	 * Creates an empty Token.
	 */
    Token();

	/**
	 * Creates Token with the specified message and delimiter.
	 *
	 * @param value The delimiting character that was matched.
	 * @param content The message content that was pulled from file.
	 */
    Token( char value, std::string content);
   
	/**
	 * Retrieves the delimiter that was matched.
	 *
	 * @return The character code for the character that was matched.
	 */
    char getMatachedDelim();

	/**
	 * Retrieves the content of the message that was extracted from the file.
	 *
	 * @return The content pulled from the file prior to coming across the delimiter.
	 */
    std::string getContent();
    
    
private:
    char delim;
    std::string content;
};



#endif	/* TOKEN_H */

