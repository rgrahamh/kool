INCLUDE_SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/usr/include/SFML
CC=g++
CFLAGS= -Wall -g
OPTS = -I"../irrKlang-64bit-1.6.0/include" -L"/usr/lib" ../irrKlang-64bit-1.6.0/bin/linux-gcc-64/libIrrKlang.so -pthread
FILES= ./source/main.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp
GAMEFILES= ./source/testGame.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp

kool: ./source/main.cpp
	$(CC) $(CFLAGS) -o engine $(FILES) $(INCLUDE_SFML) $(OPTS)

testGame: ./source/testGame.cpp ./source/testObj.cpp 
	$(CC) $(CFLAGS) -o testGame $(GAMEFILES) $(INCLUDE_SFML) $(OPTS)

clean:
	rm engine
