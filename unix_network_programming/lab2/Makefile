CC=gcc
CFLAGS= -Wall -std=gnu99

all: app1 app2

app1: app1.c
	$(CC) $(CFLAGS) -o $@ $^

app2: app2.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm app1 app2