#ifndef ELEMENTARYSTRUCT_H
#define ELEMENTARYSTRUCT_H

#include <string>

#include "BaseStruct.h"
#include "Grid.h"
#include "iRuleSet.h"

class ElementaryStruct : public BaseStruct {

	public:

		ElementaryStruct();
		ElementaryStruct( std::string name );

		void generateFile( FILE *ptr );
		BaseStruct* duplicate();
		Grid::cell_state getDefaultState();
		iRuletSet* getDefaultRuleSet();

		int getRule();
		void setRule( int value );

	private:
		int rule;

};


#endif
