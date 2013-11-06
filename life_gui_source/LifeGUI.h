#ifndef LIFEGUI_H
#define LIFEGUI_H

#include <QColor>
#include <QImage>
#include <QWidget>

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
	void setPixels( int pixel );
	int numPixels() const { return pixels; }
	void setImage( const QImage &newImage );
	QImage getImage() const {return image;}
	QSize sizeHint() const;

	protected:
	void mousePressEvent( QMouseEvent *event );
	void mouseMoveEvent(QMouseEvent *event);
	void paintEvent( QPaintEvent *event );

	private:
	QColor curColor;
	QImage image;
	int pixels;

};

#endif
