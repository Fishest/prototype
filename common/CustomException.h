/* 
 * File:   CustomException.h
 * Author: cameron
 *
 * Created on October 28, 2013, 11:40 PM
 */

#ifndef CUSTOMEXCEPTION_H
#define	CUSTOMEXCEPTION_H

#include <exception>
#include <stdio.h>
#include <iostream>
#include <ostream>

#include "constants.h"

class CustomException : public std::exception {
public:

    enum ErrorCode {
        INVALID_MAPPING, 
        INVALID_FILE, 
        NULL_PARAMETER, 
        INVALID_FILENAME, 
        NOT_ENOUGH_BUFFER_FOR_TOKEN, 
        INVALID_COLOR, 
        INVALID_POINT, 
        INVALID_TERRAIN_WINDOW, 
        INVALID_RANGE /*Refers to the low..high ranges*/,
        INVALID_COLOR_STRUCT /*Refers to the Colors struct not formatted correctly*/,
        INVALID_CELL_STATE_FOUND /*During processing, a state was found that isn't currently defined in application*/,
        PREMATURE_EOF,
        NO_NEXT_STRUCT,
		NEGATIVE_GENERATIONS,
		INVALID_CHAR,
		INVALID_TYPE_FOR_SIMULATION,/*Refers to a non elementary struct being provided to elementary rule set*/
		INVALID_RULE_VALUE, /*Value pulled for the Rule isn't valid*/
		NOT_IMPLEMENTED_YET//Used when a function hasn't been implemented yet.
                
    };

    CustomException(ErrorCode errorCode);

    virtual const char* ErrorMessage() const throw ();

    ErrorCode getError();

private:
    ErrorCode code;

};



#endif	/* CUSTOMEXCEPTION_H */

