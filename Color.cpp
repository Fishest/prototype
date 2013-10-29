#include "Color.h"

Color::Color(int red, int green, int blue){
    redValue = red;
    greenValue = green;
    blueValue = blue;
}

Color::init(){
    this->redValue = 0;
    this->greenValue = 0;
    this->blueValue = 0;
}

Color::getBlue(){
    return blueValue;
}

Color::getGreen(){
    return greenValue;
}

Color::getRed(){
    return redValue;
}

Color::toString(){
    
    char temp[100];
    sprintf( temp, "( %d, %d, %d)", redValue, greenValue, blueValue);
    
    std::string content( temp );
    
    return content;
}
