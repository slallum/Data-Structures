C_FLAGS = -std=c99 -Wall -g -pedantic-errors -lm
O_FILES = playit.o gui_framework.o playit_gui.o playit_brain.o playit_manager.o playit_brain.o

all: PlayIt
clean:
	-rm $(O_FILES) PlayIt

PlayIt: $(O_FILES)
	gcc -o PlayIt $(O_FILES) $(C_FLAGS) `sdl-config --libs`
	
playit.o:			playit.c playit.h gui_framework.h playit_gui.h
	gcc $(C_FLAGS) -c playit.c -o playit.o `sdl-config --cflags`
	
gui_framework.o:	gui_framework.c gui_framework.h
	gcc $(C_FLAGS) -c gui_framework.c `sdl-config --cflags` 
	
playit_gui.o:		playit_gui.c playit_gui.h playit_conf.h playit_manager.h gui_framework.h
	gcc $(C_FLAGS) -c playit_gui.c `sdl-config --cflags`

playit_manager.o:	playit_manager.c playit_manager.h playit_gui.h playit_brain.h playit_conf.h
	gcc $(C_FLAGS) -c playit_manager.c `sdl-config --cflags`

playit_brain.o:		playit_brain.c playit_brain.h playit_conf.h
	gcc $(C_FLAGS) -c playit_brain.c `sdl-config --cflags`
