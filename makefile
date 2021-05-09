CC=g++
CFLAGS=-pipe -O2 -Wall -Wno-write-strings
LIBS=-lmenu -lncurses

DEPS=option.o levelread.o entity.o render.o screens.o utils.o headers/config.h

.PHONY: clean

%.o: %.c headers/%.h
	$(CC) $(CFLAGS) -c $<

tbsg: tbsg.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

nick: nick.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm tbsg nick *.o
