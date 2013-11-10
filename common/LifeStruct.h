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

/**
 * Implementation of the BaseStruct that is specific for the Life structs that are defined in the
 * first part of the project.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class LifeStruct : public BaseStruct {
public:

    /**
     * Creates the Life struct object. If the parameter is null then the default
     * name should be used for creating the class.
     */
    LifeStruct();
    LifeStruct(std::string name);

    /**
     * Implementation of the virtual function in the BaseStruct class. The function handles the 
     * exportation of a LifeStruct back to the given File.
     */
    void generateFile( FILE *ptr );

    /**
     * Returns a reference to a duplicate of the LifeStruct stored on the heap. Caller takes
     * care of releasing data when finished.
     */
    BaseStruct* duplicate();


private:

};

#endif	/* LIFESTRUCT_H */

