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
	pixelHeight = 0;
	pixelWidth = 0;
	timer = NULL;

	updateImageSize();
}

void LifeGUI::updateImageSize(){

	if( current == NULL ){
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

	//image = QImage( pixelWidth, pixelHeight, QImage::Format_ARGB32 );
}

//Tells the QT what size the widge should be
//Should calculate the width given the pixel size
//and the presence of lines.
QSize LifeGUI::sizeHint() const{
	QSize size( pixelWidth, pixelHeight );
	return size;
}

void LifeGUI::mousePressEvent( QMouseEvent *event ){
	this->simulateGen( 1 );
	updateImageSize();
	update();
	updateGeometry();
}

void LifeGUI::mouseMoveEvent(QMouseEvent *event){
}

void LifeGUI::resizeEvent( QResizeEvent *event ){
	updateImageSize();
	update();
	updateGeometry();
}

void LifeGUI::paintEvent( QPaintEvent *event ){

	BaseStruct *pointer = current;

	QPainter painter( this );

	this->setFixedHeight( pixelHeight );
	this->setFixedWidth( pixelWidth );

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

	current = newBase;

	this->setWindowTitle( current->getName().c_str() );

	update();
	updateGeometry();
}

BaseStruct* LifeGUI::getStruct(){
	return current;
}

void LifeGUI::pixelsChanged( int value ){
	pixels = value;

	updateImageSize();
	updateGeometry();
	update();
}

void LifeGUI::delayChanged( int value ){
	delay = value;
	simulateGen( 1 );
}

void LifeGUI::simulateGen(){
	simulateGen( 1 );
}

void LifeGUI::simulateGen( int value ){

	
	current->simulateGenerations( value, current->getTerrain() );
	emit genChanged( current->getGeneration() );

	updateImageSize();
	update();
	updateGeometry();

	if( timer != NULL && timer->isActive() )
		timer->stop();
	if( delay > 0 ){

		if( timer != NULL ){
			delete timer;
			timer = NULL;
		}

		timer = new QTimer(this);
		connect( timer, SIGNAL(timeout()), this, SLOT(simulateGen()));
		timer->start( delay * 1000 );
	}
	
}

void LifeGUI::resetChanged(){
	current->resetSimulation();
	emit genChanged( current->getGeneration() );

	updateImageSize();
	update();
	updateGeometry();
}

void LifeGUI::operationChanged( int value ){
	//This will need to switch between the pause or constant flowing
	//visualization
}

