/* 
 * File:   Color.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:31 PM
 */

#ifndef COLOR_H
#define	COLOR_H

#include <string>

class Color {
public:

    Color();
    Color(int red, int green, int blue);

    int getRed();
    int getGreen();
    int getBlue();
    
    void reset();
    std::string toString();

private:

    int redValue;
    int greenValue;
    int blueValue;

    void init();

};

#endif	/* COLOR_H */

