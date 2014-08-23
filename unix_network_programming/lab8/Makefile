CC=gcc
CFLAGS= -Wall -std=gnu99 
LFLAGS = -lpthread -D _POSIX_C_SOURCE=200809L
ifeq ($(OS),Linux)
LFLAGS += -lrt
endif

all: server client

server: server.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

client: client.c
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

clean:
	rm -f *.o
	rm server client