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

/**
 * Provides an interface for classes that are able to transition a Grid from Generation N to Generation
 * N+1. The implementing class takes care of the details on how that transformation occurs. The 
 * existence of this interface makes it possible to quickly and easily swap out the rules being
 * used for calcuating the next generation of cells.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class iRuleSet {
public:
    
    /**
     * Once implemented in another class, the function will handle the transformation of a Grid
     * from generation N to generation N+numGenerations. This interface allows for easily swappable
     * rules within the application.
     *
     * @param base Reference to the Struct that contains the data for start of simulations. 
     * @param numGenerations The number of generations that should be transformed.
     * @param terrain The dimensions of the cells within the provided Grid that should be processed.
     * @return Grid that corresponds to the specified number of generations being simulated.
     */
    virtual Grid simulateGenerations( BaseStruct *base, int numGenerations, grid_dimension terrain) = 0;
    
};

#endif	/* IRULESET_H */

