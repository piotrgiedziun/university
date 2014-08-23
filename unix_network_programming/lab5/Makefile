CC=gcc
CFLAGS= -Wall -std=gnu99 
LFLAGS = -lpthread -D _POSIX_C_SOURCE=200809L
ifeq ($(OS),Linux)
LFLAGS += -lrt
endif

all: app1

app1: app1.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o
	rm app1