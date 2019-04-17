INCLUDE_SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/usr/include/SFML
CC=g++
CFLAGS= -Wall -g
FILES= ./source/main.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp
GAMEFILES= ./source/testGame.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp
GAMEFILES2= ./source/test2.cpp ./source/GameEngine.cpp ./source/Scene.cpp ./source/View.cpp ./source/Object.cpp ./source/Sprite.cpp ./source/Globals.cpp ./source/HitBox.cpp

kool: ./source/main.cpp
	$(CC) $(CFLAGS) -o engine $(FILES) $(INCLUDE_SFML)

testGame: ./source/testGame.cpp ./source/testObj.cpp 
	$(CC) $(CFLAGS) -o testGame $(GAMEFILES) $(INCLUDE_SFML)

test2: ./source/test2.cpp ./source/testObj2.cpp 
	$(CC) $(CFLAGS) -o testGame2 $(GAMEFILES2) $(INCLUDE_SFML)

clean:
	rm engine testGame testGame2
