CC=g++
CFLAGS=-pipe -O2 -Wall -Wno-write-strings -g
LIBS=-ltinfo -lmenu -lncurses
DEPS=levelread.o entity.o render.o screens.o utils.o headers/config.h
PREFIX=/usr

.PHONY: install uninstall clean

%.o: %.c headers/%.h
	$(CC) $(CFLAGS) -c $<

tbsg: tbsg.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

install: tbsg
	mkdir -p "$(PREFIX)/share/tbsg"; \
	cp -r levels "$(PREFIX)/share/tbsg"; \
	mkdir -p "$(PREFIX)/bin"; \
	cp -f tbsg play_tbsg "$(PREFIX)/bin"
	chmod 775 "$(PREFIX)/bin/tbsg" "$(PREFIX)/bin/play_tbsg" 

uninstall:
	rm -rf "$(PREFIX)/share/tbsg" "$(PREFIX)/bin/tbsg" "$(PREFIX)/bin/play_tbsg"

clean:
	rm tbsg *.o
