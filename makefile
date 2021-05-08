CC=g++
CFLAGS=-pipe -O2 -Wall
LIBS=

.PHONY: clean

%.o: %.c headers/%.h
	$(CC) $(CFLAGS) -c $<

tbsg: tbsg.cpp option.o levelread.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm tbsg *.o
