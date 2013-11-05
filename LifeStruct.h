/* 
 * File:   LifeStruct.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:39 PM
 */

#ifndef LIFESTRUCT_H
#define	LIFESTRUCT_H

#include <vector>
#include <string>

#include "BaseStruct.h"
#include "Color.h"
#include "Point.h"
#include "constants.h"

class LifeStruct : public BaseStruct {
public:

    /**
     * Creates the Life struct object. If the parameter is null then the default
     * name should be used for creating the class.
     */
    LifeStruct();
    LifeStruct(std::string name);

    void generateFile( FILE *ptr );


private:

};

#endif	/* LIFESTRUCT_H */

