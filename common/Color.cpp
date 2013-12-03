#include <stdio.h>

#include "Color.h"

Color::Color(){
    redValue = 0;
    greenValue = 0;
    blueValue = 0;
}

Color::Color(int red, int green, int blue){
    redValue = red;
    greenValue = green;
    blueValue = blue;
}

void Color::init(){
    this->redValue = 0;
    this->greenValue = 0;
    this->blueValue = 0;
}

int Color::getBlue(){
    return blueValue;
}

int Color::getGreen(){
    return greenValue;
}

int Color::getRed(){
    return redValue;
}

std::string Color::toString(){

	//Builds a string that represents the format that the color
	//object should follow when provided in the configuration file.
    char temp[100];
    sprintf( temp, "( %d, %d, %d)", redValue, greenValue, blueValue);
    
    std::string content( temp );
    
    return content;
}
