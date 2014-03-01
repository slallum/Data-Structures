#all: sdl_test
#
#clean:
#	-rm sdl_test.o sdl_test
#
#sdl_test: sdl_test.o
#	gcc  -o sdl_test sdl_test.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs`
#
#sdl_test.o: sdl_test.c
#	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm sdl_test.c `sdl-config --cflags`

C_FLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = PlayIt.o gui_framework.o playit_gui.o

all: PlayIt
clean:
	-rm $(O_FILES) PlayIt

PlayIt: $(O_FILES)
	gcc -o PlayIt $(O_FILES) $(C_FLAGS) `sdl-config --libs`
	
PlayIt.o:			PlayIt.c PlayIt.h gui_framework.h playit_gui.h
	gcc $(C_FLAGS) -c PlayIt.c -o PlayIt.o `sdl-config --cflags`
	
gui_framework.o:	gui_framework.c gui_framework.h
	gcc $(C_FLAGS) -c gui_framework.c `sdl-config --cflags` 
	
playit_gui.o:		playit_gui.c playit_gui.h
	gcc $(C_FLAGS) -c playit_gui.c `sdl-config --cflags`

