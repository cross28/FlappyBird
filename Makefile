
game: main.o Bird.o Collider.o Animation.o Tube.o
	g++ main.o Bird.o Collider.o Animation.o Tube.o -o game -lsfml-graphics -lsfml-window -lsfml-system

main.o: main.cpp
	g++ -c main.cpp

Bird.o: src/Bird.cpp include/Bird.h
	g++ -c src/Bird.cpp

Collider.o: src/Collider.cpp include/Collider.h
	g++ -c src/Collider.cpp

Animation.o: src/Animation.cpp include/Animation.h
	g++ -c src/Animation.cpp

Tube.o: src/Tube.cpp include/Tube.h
	g++ -c src/Tube.cpp

clean: 
	rm *.o game
