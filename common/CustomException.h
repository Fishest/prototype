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

/**
 * The CustomException is used throughout the application to report an error occurring. For the sake of time, this one exception
 * is composed of all the possible error conditions that the application reports. Ideally, a separate exception type should be
 * created to handle each of these error conditions.
 *
 * @author Cameron Whipple
 * @date December 1, 2013
 */
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
		INVALID_STRUCT_TYPE,
		INVALID_TYPE_FOR_SIMULATION,/*Refers to a non elementary struct being provided to elementary rule set*/
		INVALID_RULE_VALUE, /*Value pulled for the Rule isn't valid*/
		NOT_IMPLEMENTED_YET,//Used when a function hasn't been implemented yet.
 		INVALID_TERRAIN_STRUCT//Invalid terrain provided in the configuration file.
    };

    CustomException(ErrorCode errorCode);

    /**
     * Obtain the ErrorCode from the exception. This ErrorCode is used to determine what type
     * of error was encountered during the operation. These codes can be used with the printMessage
     * function to provide textual description to the end user.
     *
     * @return ErrorCode that corresponds to the reason for the exception.
     */
    ErrorCode getError();

    /**
     * Convert the provided ErrorCode into a human readable error message that is written to the specified file.
     *
     * @param ptr File to write the error contents to
     * @param code The code to be converted to human readable format.
     */
    static void printMessage( FILE *ptr, ErrorCode code );

private:
    ErrorCode code;

};



#endif	/* CUSTOMEXCEPTION_H */

