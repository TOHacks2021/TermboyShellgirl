CC=g++
CFLAGS=-pipe -O2 -Wall
LIBS=-lncurses

.PHONY: clean

%.o: %.c headers/%.h
	$(CC) $(CFLAGS) -c $<

tbsg: tbsg.cpp option.o levelread.o entity.o player.o render.o screens.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm tbsg *.o
