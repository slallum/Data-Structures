CFLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = board.o connect4.o game.o interpreter.o tree.h

all: connect4
clean:
	-rm $(O_FILES) connect4

connect4.o: connect4.c board.h game.h connect4.h tree.h interpreter.h
	gcc $(CFLAGS) -c connect4.c -o connect4.o

board.o: board.c board.h
	gcc $(CFLAGS) -c board.c -o board.o

interpreter.o: interpreter.c interpreter.h game.h
	gcc $(CFLAGS) -c interpreter.c -o interpreter.o

game.o: game.c board.h game.h tree.h board.h
	gcc $(CFLAGS) -c game.c -o game.o

tree.o: tree.c tree.h game.h board.h
	gcc $(CFLAGS) -c game.c -o game.o

connect4: $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
