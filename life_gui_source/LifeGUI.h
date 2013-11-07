#ifndef LIFEGUI_H
#define LIFEGUI_H

#include <QColor>
#include <QImage>
#include <QWidget>

#include "../common/constants.h"
#include "../common/BaseStruct.h"
#include "../common/iRuleSet.h"

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

	void runGenerations( int number );

	void setStruct( BaseStruct *base );
	BaseStruct *getStruct();

	void setRuleSet( iRuleSet *base );
	iRuleSet* getRuleSet();

	void setPixels( int pixel );
	int numPixels() const { return pixels; }

	protected:
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent( QPaintEvent *event );

	private:
	void init();
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
