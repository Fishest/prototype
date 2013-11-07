all: total.pro
	qmake-qt4 total.pro -o qmake_makefile
	make -f qmake_makefile

clean:
	rm -f life life_gui
	make clean -f qmake_makefile
	find . -iname "qmake_makefile" -exec rm {} \;
	rm common/libcommon.a


