INCLUDE_SFML= -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -I/usr/include/SFML/
CC=g++
CFLAGS= -Wall -g
FILES= ./source/main.cpp

kool: ./source/main.cpp
	$(CC) $(CFLAGS) -o engine $(FILES) $(INCLUDE_SFML)

clean:
	rm engine
