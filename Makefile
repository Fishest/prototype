all: total.pro
	qmake-qt4 total.pro -o qmake_makefile
	make -f qmake_makefile

clean:
	rm life life_gui
	make clean -f qmake_makefile
	rm qmake_makefile

