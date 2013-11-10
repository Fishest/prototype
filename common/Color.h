/* 
 * File:   Color.h
 * Author: cameron
 *
 * Created on October 28, 2013, 5:31 PM
 */

#ifndef COLOR_H
#define	COLOR_H

#include <string>

/**
 * Represents a Color that is used to fill in the pixels in the QT versions
 * of the applications.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
 */
class Color {
public:

    Color();
    Color(int red, int green, int blue);

    /**
     * Gets the Red value of the color object.
     *
     * @return The red portion of the Color.
     */
    int getRed();

    /**
     * Gets the Green value of the Color.
     *
     * @return The Green portion of the Color.
     */
    int getGreen();

    /**
     * Gets the Blue value of the Color.
     *
     * @return The Blue portion of the Color.
     */
    int getBlue();
    
    /**
     * Resets the Color back to 0 for all the components.
     */
    void reset();

    /**
     * Maps the Color attributes back to a format that can then
     * be used to export the color back to configuration file.
     *
     * @return String that contains a compatible format.
     */
    std::string toString();

private:

    int redValue;
    int greenValue;
    int blueValue;

    void init();

};

#endif	/* COLOR_H */

