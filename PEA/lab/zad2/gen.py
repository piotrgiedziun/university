#!/usr/bin/python
#-*- coding: utf-8 -*-
import sys, random

if len(sys.argv) >= 2:
	inst_size = int(sys.argv[1])
else:
	inst_size = int(raw_input("Rozmiar instancji: "))

if len(sys.argv) >= 3:
	time_size = int(sys.argv[2])
else:
	time_size = int(raw_input("Przedział czasu: 1-"))

f = open("input.txt", "w")
for i in range(0, inst_size):
	f.write("%d\n" % (random.randint(1, time_size),))
f.close()