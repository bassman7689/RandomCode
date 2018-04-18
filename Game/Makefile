SRC=src
FILES=$(SRC)/Shader.cpp $(SRC)/Game.cpp
CPP=g++
INCLUDES=-I/usr/local/include -I/opt/X11/include -I include/
LIBS=-L/usr/local/lib -L/opt/X11/lib
CPPFLAGS=-w -std=c++11
LDFLAGS=-framework OpenGL -lglfw -lglew

all:
	g++ $(INCLUDES) $(LIBS) $(CPPFLAGS) $(LDFLAGS) $(FILES) -o game

.PHONY: clean
clean:
	rm -f *.o game
