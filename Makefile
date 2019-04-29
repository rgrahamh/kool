INCLUDE_SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/usr/include/SFML
CC=g++
CFLAGS= -Wall -g
OPTS = -I"./source/irrKlang-64bit-1.6.0/include" -L"/usr/lib" ./source/irrKlang-64bit-1.6.0/bin/linux-gcc-64/libIrrKlang.so -pthread
FILES= ./source/main.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp
GAMEFILES= ./source/testGame.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp
GAMEFILES2= ./source/test2.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp
ADAMGAMEFILES= ./source/adam/main.cpp ./source/adam/gameobjects.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp ./source/adam/scenes.cpp
JGAMEFILES= ./source/jeremiah/main.cpp ./source/jeremiah/game.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp

kool: ./source/main.cpp
	$(CC) $(CFLAGS) -o engine $(FILES) $(INCLUDE_SFML) $(OPTS)

testGame: ./source/testGame.cpp ./source/testObj.cpp 
	$(CC) $(CFLAGS) -o testGame $(GAMEFILES) $(INCLUDE_SFML) $(OPTS)

test2: ./source/test2.cpp ./source/testObj2.cpp 
	$(CC) $(CFLAGS) -o testGame2 $(GAMEFILES2) $(INCLUDE_SFML)

adam: ./source/adam/main.cpp ./source/adam/gameobjects.cpp
	$(CC) $(CFLAGS) -o adam $(ADAMGAMEFILES) $(INCLUDE_SFML) $(OPTS)

jeremiah: ./source/jeremiah/main.cpp ./source/jeremiah/game.cpp
	$(CC) $(CFLAGS) -o j $(JGAMEFILES) $(INCLUDE_SFML)

clean:
	rm engine testGame testGame2
