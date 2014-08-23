CC=gcc
CFLAGS= -Wall -std=gnu99 

all: app1 app2

app1: app1.c
	$(CC) $(CFLAGS) -o $@ $^ -lrt -lpthread -D _POSIX_C_SOURCE=200809L

app2: app1.c
	$(CC) $(CFLAGS) -o $@ $^ -lrt -lpthread -D _POSIX_C_SOURCE=200809L -D SEMAPHORES

clean:
	rm -f *.o
	rm app1 app2