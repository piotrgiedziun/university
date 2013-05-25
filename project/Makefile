GXX=g++
CFLAGS=-Wall
LIBS=-lncurses -lpthread

OBJS=snake.o map.o game.o

all: game clean

.o.cpp:
	$(GXX) $(CFLAGS) -c $<

game: $(OBJS)
	$(GXX) $(LIBS) $(OBJS) -o game

clean:
	rm *.o