#include <QtGui>

#include "LifeGUI.h"
#include "../common/Point.h"
#include "../common/constants.h"
#include "../common/Grid.h"

LifeGUI::LifeGUI( QWidget *parent ) : QWidget( parent ){
	setAttribute( Qt::WA_StaticContents );
	setSizePolicy( QSizePolicy::Minimum, QSizePolicy::Minimum );
	init();
}

void LifeGUI::init(){

	pixels = 10;
	current = NULL;
	original = NULL;
	rules = NULL;
	pixelHeight = 0;
	pixelWidth = 0;

	updateImageSize();
}

void LifeGUI::updateImageSize(){

	if( current == NULL ){
		image = QImage( 10, 10, QImage::Format_ARGB32);
		pixelHeight = 10;
		pixelWidth = 10;

		return;
	}

	numElementsWidth = current->getWindow().xVals.getSecond() - current->getWindow().xVals.getFirst() + 1;
	numElementsHeight = current->getWindow().yVals.getSecond() - current->getWindow().yVals.getFirst() + 1;

	pixelWidth = numElementsWidth * pixels;
	pixelHeight = numElementsHeight * pixels;

	if( pixels >= 4 ){
		pixelWidth += ( numElementsWidth - 1 );
		pixelHeight += ( numElementsHeight - 1 );
	}

	image = QImage( pixelWidth, pixelHeight, QImage::Format_ARGB32 );
}

void LifeGUI::setPenColor( const QColor &newColor){
	curColor = newColor;
}

void LifeGUI::setPixels( int pixel ){

	if( pixel < 1 )
		pixel = 1;

	if( pixel != pixels ){
		pixels = pixel;
		updateImageSize();
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
	QSize size( pixelWidth, pixelHeight );
	return size;
}

void LifeGUI::mousePressEvent( QMouseEvent *event ){
}

void LifeGUI::mouseMoveEvent(QMouseEvent *event){
}

void LifeGUI::paintEvent( QPaintEvent *event ){

	BaseStruct *pointer = current;

	QPainter painter( this );

	//This function will take the content from the BaseStruct and will
	//go about updating the image format with the content.
	int index = 0;
	int rowIndex = 0;
	int colIndex = 0;

	//Set pen to black to draw the grid lines
	painter.setPen( QColor( 0, 0, 0) );

	int placeIndex = pixels;
	//Draw the vertical lines on the image first.
	for( index = 0; index < numElementsWidth && pixels >= 4 ; index++ ){
		painter.drawLine( pixels + (index *(1 + pixels)) , 0, pixels + (index *(1 + pixels)) , pixelHeight  );
	}

	//Draw the horizontal lines on the image
	for( index = 0; index < numElementsHeight && pixels >= 4; index++){
		painter.drawLine( 0, pixels + (index *(1 + pixels)) , pixelWidth, pixels + (index *(1 + pixels)) );
	}

	int basePointX = pointer->getWindow().xVals.getFirst();
	int basePointY = pointer->getWindow().yVals.getSecond();

	//Fill in the rectangles content
	for( rowIndex = 0; rowIndex < numElementsHeight; rowIndex++ ){

		int offset = pixels;
		if( pixels >= 4 )
			offset++;

		int startY = rowIndex * offset;

		for( colIndex = 0; colIndex < numElementsWidth; colIndex++ ){

			int startX = colIndex * offset;
			Point temp( basePointX + colIndex , basePointY - rowIndex );

			Grid::cell_state state = pointer->getGrid().get( temp );
			Color colorVal = pointer->getColor( state );

			painter.fillRect( startX, startY, pixels, pixels, QBrush( QColor( colorVal.getRed(), colorVal.getGreen(), colorVal.getBlue() ) ) );
		}
	}

	painter.end();
}

void LifeGUI::setStruct( BaseStruct *newBase ){

	if( newBase == NULL )
		return;

	if( current != NULL )
		delete current;
	if( original != NULL )
		delete original;

	current = NULL;
	original = NULL;

	original = newBase;
	current = original->duplicate();

	update();
	updateGeometry();
}

BaseStruct* LifeGUI::getStruct(){
	return current;
}

void LifeGUI::setRuleSet( iRuleSet *ruleset ){

	if( ruleset == NULL )
		return;

	rules = ruleset;
}

iRuleSet* LifeGUI::getRuleSet(){
	return rules;
}

void LifeGUI::runGenerations( int number ){

	if( number < 0 )
		return;

	Grid tGrid = rules->simulateGenerations( current->getGrid(), number, current->getTerrain() );
	current->setGrid( tGrid );

	update();
	updateGeometry();
}

