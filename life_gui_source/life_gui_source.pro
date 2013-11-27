TARGET = ../life_gui
SOURCES = LifeGUI.cpp life_gui.cpp mainwindow.cpp
HEADERS = LifeGUI.h mainwindow.h
FORMS    += mainwindow.ui
INCLUDEPATH += ../common
LIBS += -L../common -lcommon
