#ifndef LIFEGUI_H
#define LIFEGUI_H

#include <QColor>
#include <QImage>
#include <QWidget>

#include "../common/constants.h"
#include "../common/BaseStruct.h"
#include "../common/iRuleSet.h"

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
	Q_PROPERTY(QColor penColor READ penColor WRITE setPenColor)
	Q_PROPERTY(QImage image READ getImage WRITE setImage)
	Q_PROPERTY(int pixels READ numPixels WRITE setPixels)

	public:
	LifeGUI( QWidget *parent = 0 );
	virtual ~LifeGUI(){};

	void setPenColor( const QColor &newColor);
	QColor penColor() const {return curColor; }
	
	void setImage( const QImage &newImage );
	QImage getImage() const {return image;}
	QSize sizeHint() const;

	/**
	 * Runs the current Grid through a series of generation simulations. The simulation is done using the 
	 * RuleSet that has been defined through the setRuleSet function. The decoupling will allow for extendable
	 * support in the future of overlapping functionality.
	 *
	 * @param number The number of generations to run through.
	 */
	void runGenerations( int number );

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
	 * Sets the Rules that are used for progressing a Grid from Generation N to Generation N+1.
	 *
	 * @param base Pointer to the ruleset that should be used.
	 */
	void setRuleSet( iRuleSet *base );

	/**
	 * Gets a pointer to the RuleSet that is currently being used for the generation progression.
	 *
	 * @param Pointer to the RuleSet that is being used currently.
	 */
	iRuleSet* getRuleSet();

	/**
	 * Sets the number of pixels that are used when drawing a single cell of the Grid.
	 *
	 * @param pixel The number of pixels for a given cell, width.
	 */
	void setPixels( int pixel );

	/**
	 * Gets the number of pixels that are used when drawing a single cell of the Grid.
	 *
	 * @return The number of pixels being used as the width of a cell.
	 */
	int numPixels() const { return pixels; }

	protected:
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent( QPaintEvent *event );

	private:
	void init();

	/*
	   Updates the size of the image based on the setPixel size and the number
	   of cells currenty defined in the window.
	   */
	void updateImageSize();

	QColor curColor;
	QImage image;
	int pixels;
	int pixelHeight;
	int pixelWidth;
	int numElementsWidth;
	int numElementsHeight;
	BaseStruct *original;
	BaseStruct *current;
	iRuleSet *rules;

};

#endif
