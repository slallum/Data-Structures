CFLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = board.o Connect4.o game.o interpreter.o tree.o scoring.o io.o

all: Connect4
test: scoring.test
clean:
	-rm $(O_FILES) Connect4

Connect4.o: Connect4.c board.h game.h Connect4.h tree.h interpreter.h scoring.h
	gcc $(CFLAGS) -c Connect4.c -o Connect4.o

board.o: board.c board.h
	gcc $(CFLAGS) -c board.c -o board.o

tree.o: tree.c tree.h game.h board.h
	gcc $(CFLAGS) -c tree.c -o tree.o

game.o: game.c board.h game.h tree.h board.h
	gcc $(CFLAGS) -c game.c -o game.o

io.o: io.c io.h
	gcc $(CFLAGS) -c io.c -o io.o

interpreter.o: interpreter.c interpreter.h io.h game.h
	gcc $(CFLAGS) -c interpreter.c -o interpreter.o

scoring.o: scoring.c scoring.h
	gcc $(CFLAGS) -c scoring.c -o scoring.o

Connect4: $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
