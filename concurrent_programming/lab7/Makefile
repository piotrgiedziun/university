GXX=gcc
CFLAGS=-Wall
LIBS=-lrt

all: udp_serw udp_cli

.o.cpp:
	$(GXX) $(CFLAGS) -c $<

udp_serw: udp_serw.c static.h
	$(GXX) $(LIBS) udp_serw.c -o udp_serw

udp_cli: udp_cli.c static.h
	$(GXX) $(LIBS) udp_cli.c -o udp_cli
