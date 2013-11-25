CFLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = board.o game.o nim.o

all	: nim
clean :
		  -rm $(O_FILES) nim

nim.o: nim.c board.h game.h nim.h
		  gcc $(CFLAGS) -c nim.c -o nim.o

board.o: board.c board.h
		  gcc $(CFLAGS) -c board.c -o board.o

game.o: game.c board.h game.h
		  gcc $(CFLAGS) -c game.c -o game.o

nim: $(O_FILES)
		  gcc $(CFLAGS) -o $^