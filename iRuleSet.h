/* 
 * File:   iRuleSet.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:39 PM
 */

#ifndef IRULESET_H
#define	IRULESET_H

#include "constants.h"
#include "Grid.h"

class iRuleSet {
public:
    
    virtual void simulateGenerations( Grid & live, int numGenerations, grid_dimension terrain) = 0;
    
};

#endif	/* IRULESET_H */

