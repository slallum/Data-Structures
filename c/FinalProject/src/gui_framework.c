/*
 * gui_framework.c
 *
 *  Created on: Feb 22, 2014
 *      Author: shir
 */

#include "gui_framework.h"

#define WIN_W 640
#define WIN_H 480

#define HEADING "Play it!"

extern Control* window;

/**
 * Creates control with elements that all the types need.
 */
Control* create_control(int x, int y, int width, int height, Control* parent,
		Control** children, SDL_Surface* view,
		void (*on_select)(struct Control*), void (*draw)(struct Control*)) {
	Control* new_control = (Control*) malloc(sizeof(Control));
	new_control->x = x;
	new_control->y = x;
	new_control->width = width;
	new_control->height = height;
	new_control->parent = parent;
	new_control->on_select = on_select;
	new_control->draw = draw;
	return new_control;
}

/**
 * Creates the window component - should be one as root of UI Tree
 *
 * @param children	component's children
 */
Control* create_window(Control* children) {
	SDL_WM_SetCaption(HEADING, HEADING);
	SDL_Surface* view = SDL_SetVideoMode(WIN_W, WIN_H, 0,
			SDL_HWSURFACE | SDL_DOUBLEBUF);
	window = create_control(0, 0, WIN_W, WIN_H, NULL, children, view, NULL,
			draw_node);
	return window;
}

/**
 * Create a panel control
 *
 * @param children	Children controls to appear in the panel
 * @param x, y		Position, relative to parent
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_panel(int x, int y, int width, int height, Control* parent,
		Control** children, int R, int G, int B) {
	SDL_Surface* view = &(SDL_Rect ) { 0, 0, width, height };
	SDL_fillRect(view, NULL, SDL_MapRGB(window->view->format, R, G, B));
	return create_control(x, y, width, height, parent, children, view, NULL,
			draw_node);
}

/**
 * Creates a label control
 *
 * @param label_path	Path to find pic representing the label.
 * 						Loads the pic and draws it.
 */
Control* create_label(int x, int y, int width, int height, char* label_path,
		Control* parent) {

	return create_control(x, y, width, height, parent, NULL,
			SDL_LoadIMG(label_path), empty_select, draw_leaf);
}

/**
 * Creates a button control
 *
 * @param label_path	Path to find pic representing the label.
 * @param children		Controls needed when button is selected.
 * 						Could be the destination control or controls to be freed.
 * @param on_select		Function to be called when the button is selected
 */
Control* create_button(int x, int y, int width, int height, char* label_path,
		Control* parent, void (*on_select)(struct Control*)) {

	return create_control(x, y, width, height, parent, NULL,
			SDL_LoadIMG(label_path), on_select, draw_leaf);
}

/**
 * Nothing happens on select
 */
void empty_select(Control* control) {

}

/**
 * Draws given node as a node in a tree - first draws element,
 * then calls the draw function of all children
 */
void draw_node(Control* node) {
	int i;
	int children_num = sizeof(node->children) / sizeof(Control*);

	draw_leaf(node);
	for (i = 0; i < children_num; i++) {
		node->children[i]->draw(node->children[i]);
	}
}

/**
 * Draws given leaf - just draws element,
 * ignoring any children that might be
 */
void draw_leaf(Control* leaf) {
	SDL_BlitSurface(leaf->view, NULL, leaf->parent, NULL);
}
