CC=g++
CFLAGS=-pipe -O2 -Wall
LIBS=-lmenu -lncurses

.PHONY: clean

%.o: %.c headers/%.h
	$(CC) $(CFLAGS) -c $<

tbsg: tbsg.cpp option.o levelread.o entity.o render.o screens.o utils.o headers/config.h
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm tbsg *.o
