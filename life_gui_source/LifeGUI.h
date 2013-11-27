#ifndef LIFEGUI_H
#define LIFEGUI_H

#include <QColor>
#include <QImage>
#include <QWidget>

#include "../common/constants.h"
#include "../common/BaseStruct.h"

/**
 * The LifeGUI is the QT application that handles the visualization of a BaseStruct to the screen.
 * The LifeGUI supports a series of function calls for updating the pixel size or updating the RuleSet
 * that is used for calculating the next generation of cellular states.
 *
 * @author Cameron Whipple
 * @date November 9, 2013
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
	void genChanged( int value );

	public slots:

	void pixelsChanged( int value );
	void delayChanged( int value );
	void simulateGen( int value );
	void simulateGen();
	void resetChanged();
	void operationChanged( int value );

	protected:
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent( QPaintEvent *event );
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
	BaseStruct *current;
	QTimer *timer;

};

#endif
