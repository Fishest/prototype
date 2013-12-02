#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

/**
 * The MainWindow application is used as a control platform for the display. The display
 * will graphical show the contents of a Game of Life simulation. There are several parameters
 * to the Game of Life simulations that could be altered. This application provides an interface
 * through which those parameters can be altered. This application also allows for the implementation
 * of an automated generation progression. The control and interaction with the display is performed
 * through the use of signals and slots within the QT framework.
 *
 * @author Cameron Whipple
 * @date December 1, 2013
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * Sets the starting pixel count that is being used for visualizing the simulation.
     *
     * @param value Number of pixels
     */
	void setStartPixels( int value );

	/**
	 * Sets the amount of delay, in seconds, between generation progression.
	 *
	 * @param value Amount of delay, in seconds.
	 */
	void setStartDelay( int value );

	/**
	 * Sets the current generation count.
	 *
	 * @param value Current generation value.
	 */
	void setStartGenerations( int value );

signals:

	/**
	 * Signal that is emitted when the number of pixels has been changed in the interface.
	 *
	 * @param value Number of pixels that should be used.
	 */
	void pixelsChanged( int value );

	/**
	 * Signal that is emitted when the delay length has been changed within the GUI.
	 *
	 * @param value Amount of delay, in seconds, between generation progression.
	 */
	void delayChanged( int value );

	/**
	 * Signal that is emmitted when the simulation needs to progress forward in it's generations.
	 *
	 * @param value Number of generations to progress.
	 */
	void simulateGen( int value );

	/**
	 * Signal that is emitted when the simulation needs to be reset back to generation 0.
	 */
	void resetChanged();


public slots:

	//Called when generation value has changed
	/**
	 * Slot that is used for updating the generation label within the control display. The signal
	 * is typically emitted from the display when it has altered it's generation amount.
	 *
	 * @param value The current generation
	 */
	void gensChanged( int value );


private slots:

	/**
	 * This slot is called when the quit button is pressed on the control display.
	 */
    void on_quitButton_clicked();

    /**
     * This slot is called when the restart button from the control display is pressed.
     */
    void on_restartButton_clicked();

    /**
     * This slot is called when the start/stop button is pressed on the control display.
     */
    void on_playButton_clicked();

    /**
     * This slot is called when the step button is pressed on the control display.
     */
    void on_stepButton_clicked();

    /**
     * This slot is called when the value inside the spin box for the delay is changed in some way.
     * 
     * @param arg1 The new value present in the box.
     */
    void on_delaySpinBox_valueChanged(int arg1);

    /**
     * This slot is called when the value inside the spin box for the pixel count has changed in some way.
     *
     * @param arg1 The new value present in the box.
     */
    void on_pixelSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
	bool cts;
};

#endif // MAINWINDOW_H
