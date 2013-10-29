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
        INVALID_MAPPING, INVALID_FILE, NULL_PARAMETER
    };

    CustomException(ErrorCode errorCode);

    virtual const char* ErrorMessage() const throw ();

    ErrorCode getError();

private:
    ErrorCode code;

};



#endif	/* CUSTOMEXCEPTION_H */

