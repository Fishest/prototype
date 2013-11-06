#include <QtGui>

#include "LifeGUI.h"

LifeGUI::LifeGUI( QWidget *parent ) : QWidget( parent ){
	setAttribute( Qt::WA_StaticContents );
	setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
	curColor = Qt::black;
	pixels = 8;

	image = QImage( 16, 16, QImage::Format_ARGB32);
	image.fill(qRgba(0,0,0,0));
}

void LifeGUI::setPenColor( const QColor &newColor){
	curColor = newColor;
}

void LifeGUI::setPixels( int pixel ){
	if( pixel < 1 )
		pixel = 1;

	if( pixel != pixels ){
		pixels = pixel;
		update();
		updateGeometry();
	}
}

void LifeGUI::setImage( const QImage &newImage ){
	if( newImage != image ){
		image = newImage.convertToFormat( QImage::Format_ARGB32 );
		update();
		updateGeometry();
	}
}

//Tells the QT what size the widge should be
//Should calculate the width given the pixel size
//and the presence of lines.
QSize LifeGUI::sizeHint() const{
	//TODO Will need to redo this function for sure.
	QSize size = pixels * image.size();
	return size;
}

void LifeGUI::mousePressEvent( QMouseEvent *event ){
}

void LifeGUI::mouseMoveEvent(QMouseEvent *event){
}

void LifeGUI::paintEvent( QPaintEvent *event ){

	QPainter painter( this );

	painter.setPen( QColor( 125,64,78 ) );
	painter.drawLine( 0, 0, 15, 15);
}
