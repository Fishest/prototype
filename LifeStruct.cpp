#include <string>

#include "LifeStruct.h"

LifeStruct::LifeStruct() : BaseStruct( BaseStruct::LIFE ){
}

LifeStruct::LifeStruct(std::string name) : BaseStruct( BaseStruct::LIFE, name ){
    //This is just an empty shell for the time being.
}
