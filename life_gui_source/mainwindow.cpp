#include <string.h>
#include <stdio.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	cts = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quitButton_clicked()
{
    exit(0);

}

void MainWindow::on_restartButton_clicked()
{
	emit resetChanged();
}

void MainWindow::on_playButton_clicked()
{
	if( cts ){
		ui->playButton->setText("Start");
		emit delayChanged( 0 );
		cts = false;
	}
	else{
		ui->playButton->setText("Stop");
		emit delayChanged( ui->delaySpinBox->value() );
		cts = true;
	}

}

void MainWindow::on_stepButton_clicked()
{
	emit simulateGen( 1 );
}

void MainWindow::on_delaySpinBox_valueChanged(int arg1)
{
	//emit delayChanged( arg1 );
}

void MainWindow::on_pixelSpinBox_valueChanged(int arg1)
{
	emit pixelsChanged( arg1 );
}

void MainWindow::gensChanged( int value ){
	char buffer[100];
	bzero( buffer, 100 );

	sprintf( buffer, "%d", value );
	ui->generationLabel->setText( buffer );
}

void MainWindow::setStartPixels( int value ){
	ui->pixelSpinBox->setValue( value );
}

void MainWindow::setStartDelay( int value ){
	ui->delaySpinBox->setValue( value );
}

void MainWindow::setStartGenerations( int value ){
	gensChanged( value );
}

