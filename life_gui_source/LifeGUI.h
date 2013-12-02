#ifndef LIFEGUI_H
#define LIFEGUI_H

#include <QColor>
#include <QImage>
#include <QWidget>

#include "../common/constants.h"
#include "../common/BaseStruct.h"

/**
 * The LifeGUI is the QT application that handles the visualization of a BaseStruct to the screen.
 * The LifeGUI supports a series of signals and slots for controlling its operation. Many of the slots
 * correspond to events in which the display needs to be changed. These changes may come from a change
 * in the pixel size or generation size. Signals are emitted in order to keep interested parties apprised
 * of the displays state.

 * @author Cameron Whipple
 * @date December 1, 2013
 */
class LifeGUI : public QWidget{

	Q_OBJECT
	Q_PROPERTY(int pixels READ numPixels WRITE pixelsChanged)

	public:
	LifeGUI( QWidget *parent = 0 );
	virtual ~LifeGUI(){};

	QSize sizeHint() const;

	/**
	 * Sets the BaseStruct that will be used within the application to control the terrain and the window values.
	 *
	 * @param base Pointer to the Struct that should be used to draw the Grid.
	 */
	void setStruct( BaseStruct *base );

	/**
	 * Gets the BaseStruct that is currently being used for visualizing the Grid.
	 *
	 * @return Pointer to the BaseStruct being used.
	 */
	BaseStruct *getStruct();

	/**
	 * Gets the number of pixels that are used when drawing a single cell of the Grid.
	 *
	 * @return The number of pixels being used as the width of a cell.
	 */
	int numPixels() const { return pixels; }

	signals:

	/**
	 * This signal is emitted when the generation that is being displayed has beed changed. The value in the signal
	 * corresponds to the generation that is currently being displayed on the screen.
	 *
	 * @param value The generation that is currently being displayed on the screen.
	 */
	void genChanged( int value );

	public slots:

	/**
	 * This slot corresponds to when the number of pixels that are used to display the grid is changed. This will result
	 * in an updating of the display to reflect that new pixel amount. The input must be positive in order for the screen
	 * to be updated to the provided value.
	 *
	 * @param value Number of pixels to represent a piece of the grid.
	 */
	void pixelsChanged( int value );

	/**
	 * The delay in the application corresponds to the amount of time, in seconds, between the automated generation progression.
	 * This slot corresponds to the event in which the amount of time between the generations is changed from an external source.
	 * 
	 * @param value Number seconds between generation progression. A value of 0 will correspond to no automated progression.
	 */
	void delayChanged( int value );

	/**
	 * This slot will cause the display to progress forward by the specified number of generations. This slot if called whenever a third
	 * party wants to update the display to a next generation. A positive value must be specified in order for the generation to progress
	 * forward. Upon the change of the generation, the genChanged signal will be emitted to update any listeners of the new simulation 
	 * value.
	 *
	 * @param value The number of generations to progress forward.
	 */
	void simulateGen( int value );

	/**
	 * This slot will cause the display to progress forward by a single generation. This slot is called whenever a third party wants to
	 * update the display to show the next generation. Upon the change of the generation, the genChanged signal will be emitted to update any listeners
	 * that are interested in updates regarding the generation.
	 */
	void simulateGen();

	/**
	 * This slot will cause the display to reset the grid to the original appearance. This is called by the control dialog when the display
	 * needs to be reset back to the original settings.
	 */
	void resetChanged();

	protected:

	/**
	 * This function gets called when the mouse is clicked on the display window. This allows for custom operations to take
	 * place when the mouse is pressed. Currently, this isn't set up to add any additional functionality but it is in place
	 * for future features.
	 */
	void mousePressEvent( QMouseEvent *event );

	/**
	 * This function gets called when the mouse is moved across the display window. Currently, the display doesn't take
	 * any action when this is detected. This is here primarily as a potential feature addition point.
	 */
	void mouseMoveEvent(QMouseEvent *event);

	/**
	 * This function gets called when the content in the display needs to be redrawn, or painted. By Overriding this function, the code
	 * is able to control the content that gets placed on the screen.
	 */
	void paintEvent( QPaintEvent *event );

	/**
	 * This function gets called when the screen's size has been changed. This often is called by the dragging of the windows bounds to make the
	 * window smaller or larger.
	 */
	void resizeEvent( QResizeEvent *event );

	private:
	void init();

	/*
	   Updates the size of the image based on the setPixel size and the number
	   of cells currenty defined in the window.
	   */
	void updateImageSize();

	QColor curColor;
	int pixels;
	int delay;
	int pixelHeight;
	int pixelWidth;
	int numElementsWidth;
	int numElementsHeight;

	//Reference to the structure that contains all the information necessary to progress
	//the generation to the next value.
	BaseStruct *current;

	//The timer is used within the class to implement the automated generation
	//progression.
	QTimer *timer;

};

#endif
