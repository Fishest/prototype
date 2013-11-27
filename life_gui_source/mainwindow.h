#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

	void setStartPixels( int value );
	void setStartDelay( int value );
	void setStartGenerations( int value );

signals:
	void pixelsChanged( int value );
	void delayChanged( int value );
	void simulateGen( int value );
	void resetChanged();
	void operationChanged( int value );


public slots:

	//Called when generation value has changed
	void gensChanged( int value );


private slots:
    void on_quitButton_clicked();

    void on_restartButton_clicked();

    void on_playButton_clicked();

    void on_stepButton_clicked();

    void on_delaySpinBox_valueChanged(int arg1);

    void on_pixelSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
	bool cts;
};

#endif // MAINWINDOW_H
