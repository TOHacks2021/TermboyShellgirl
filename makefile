CC=g++
CFLAGS=-pipe -O2 -Wall -Wno-write-strings -g
LIBS=-lmenu -lncurses

DEPS=levelread.o entity.o render.o screens.o utils.o headers/config.h

.PHONY: clean

%.o: %.c headers/%.h
	$(CC) $(CFLAGS) -c $<

tbsg: tbsg.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm tbsg *.o
