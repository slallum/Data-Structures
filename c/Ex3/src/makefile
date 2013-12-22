CFLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = board.o connect4.o game.o interpreter.o tree.o

all: connect4
test: scoring.test
clean:
	-rm $(O_FILES) connect4

connect4.o: connect4.c board.h game.h connect4.h tree.h interpreter.h scoring.h
	gcc $(CFLAGS) -c connect4.c -o connect4.o

board.o: board.c board.h
	gcc $(CFLAGS) -c board.c -o board.o

interpreter.o: interpreter.c interpreter.h game.h
	gcc $(CFLAGS) -c interpreter.c -o interpreter.o

game.o: game.c board.h game.h tree.h board.h
	gcc $(CFLAGS) -c game.c -o game.o

tree.o: tree.c tree.h game.h board.h
	gcc $(CFLAGS) -c tree.c -o tree.o

scoring.o: scoring.c scoring.h
	gcc $(CFLAGS) -c scoring.c -o scoring.o

scoring.test.o: scoring.test.c scoring.h
	gcc $(CFLAGS) -c scoring.test.c -o scoring.test.o
	
scoring.test: scoring.test.o scoring.o
	gcc $(CFLAGS) -o $@ $^

connect4: $(O_FILES)
	gcc $(CFLAGS) -o $@ $^
