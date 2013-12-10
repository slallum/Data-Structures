CFLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = board.o game.o nim.o ai_nim.o

all: nim
clean:
	-rm $(O_FILES) nim

nim.o: nim.c board.h game.h nim.h ai_nim.h
	gcc $(CFLAGS) -c nim.c -o nim.o

ai_nim.o: ai_nim.c ai_nim.h game.h
	gcc $(CFLAGS) -c ai_nim.c -o ai_nim.o

board.o: board.c board.h
	gcc $(CFLAGS) -c board.c -o board.o

game.o: game.c board.h game.h
	gcc $(CFLAGS) -c game.c -o game.o

nim: $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
