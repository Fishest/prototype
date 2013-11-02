/* 
 * File:   Token.h
 * Author: cameron
 *
 * Created on November 1, 2013, 12:32 PM
 */

#ifndef TOKEN_H
#define	TOKEN_H

#include <string>

class Token{
    
public:
    Token();
    Token( char value, std::string content);
    
    char getMatachedDelim();
    std::string getContent();
    
    
private:
    char delim;
    std::string content;
};



#endif	/* TOKEN_H */

