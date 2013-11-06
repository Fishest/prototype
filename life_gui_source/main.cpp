#include <QApplication>
#include <QLabel>

#include "LifeGUI.h"

int main( int argc, char **args){

	QApplication app(argc, args);
	LifeGUI *g = new LifeGUI();
	g->show();
	return app.exec();
}
