CF=-c -ggdb -Wall

OBJECTS=objects/Life.o\
		objects/BaseStruct.o\
		objects/Color.o\
		objects/CustomException.o\
		objects/FileParser.o\
		objects/Grid.o\
		objects/LifeStruct.o\
		objects/Point.o\
		objects/Token.o\
		objects/LifeRuleSet.o\
		objects/AsciiVisual.o

apps: life

life: $(OBJECTS)
	g++ -o life $(OBJECTS)

life_gui:

objects/Life.o: FileParser.h Point.h LifeRuleSet.h constants.h Life.cpp
	g++ $(CF) -o objects/Life.o Life.cpp

objects/BaseStruct.o: BaseStruct.h CustomException.h BaseStruct.cpp
	g++ $(CF) -o objects/BaseStruct.o BaseStruct.cpp

objects/Color.o: Color.h Color.cpp
	g++ $(CF) -o objects/Color.o Color.cpp

objects/CustomException.o: CustomException.h CustomException.cpp
	g++ $(CF) -o objects/CustomException.o CustomException.cpp

objects/FileParser.o: Grid.h Point.h CustomException.h FileParser.h LifeStruct.h Token.h FileParser.cpp
	g++ $(CF) -o objects/FileParser.o FileParser.cpp

objects/Grid.o: Grid.h Point.h CustomException.h Grid.cpp
	g++ $(CF) -o objects/Grid.o Grid.cpp

objects/LifeStruct.o: BaseStruct.h LifeStruct.h LifeStruct.cpp
	g++ $(CF) -o objects/LifeStruct.o LifeStruct.cpp

objects/Point.o: Point.h Point.cpp
	g++ $(CF) -o objects/Point.o Point.cpp

objects/Token.o: Token.h Token.cpp
	g++ $(CF) -o objects/Token.o Token.cpp

objects/LifeRuleSet.o: LifeRuleSet.h LifeRuleSet.cpp
	g++ $(CF) -o objects/LifeRuleSet.o LifeRuleSet.cpp

objects/AsciiVisual.o: AsciiVisual.h visuals.h AsciiVisual.cpp
	g++ $(CF) -o objects/AsciiVisual.o AsciiVisual.cpp

clean:
	rm -rf objects/*
	rm -rf life