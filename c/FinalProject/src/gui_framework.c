/*
 * gui_framework.c
 *
 *  Created on: Feb 22, 2014
 *      Author: shir
 */

#include "gui_framework.h"

/**
 * Perform operations needed for the SDL framework to work
 * returns 1 if went smoothly, 0 o\w
 */
int init_fw() {
	// Initialize SDL and make sure it quits
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error: Unable to init SDL: %s\n", SDL_GetError());
		return 0;
	}
	atexit(SDL_Quit);
	return 1;
}

/**
 * Creates control with elements that all the types need.
 */
Control* create_control(int x, int y, int width, int height, Control* parent,
		Control** children, SDL_Surface* view,
		void (*on_select)(struct Control*), void (*draw)(struct Control*)) {
	int i;
	Control* new_control = (Control*) malloc(sizeof(Control));
	new_control->x = x;
	new_control->y = x;
	new_control->width = width;
	new_control->height = height;
	new_control->parent = parent;
	new_control->children = children;
	new_control->on_select = on_select;
	new_control->draw = draw;
	if (children != NULL) {
		for (i = 0; i < sizeof(children) / sizeof(Control*); i++) {
			new_control->children[i]->parent = new_control;
		}
	}
	return new_control;
}

/**
 * Creates the window component - should be one as root of UI Tree
 *
 * @param children	component's children
 */
Control* create_window(Control** children) {
	SDL_WM_SetCaption(HEADING, HEADING);
	SDL_Surface* view = SDL_SetVideoMode(WIN_W, WIN_H, 0,
			SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (view == NULL ) {
		printf("Error: Failed to set video mode: %s\n", SDL_GetError());
		return NULL ;
	}
	return create_control(0, 0, WIN_W, WIN_H, NULL, children, view, NULL,
			draw_children);
}

/**
 * Create a panel control
 *
 * @param children	Children controls to appear in the panel
 * @param x, y		Position, relative to parent
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_panel(Control* window, int x, int y, int width, int height,
		char* bg_path, Control* parent, Control** children) {
	return create_control(x, y, width, height, parent, children,
			SDL_LoadBMP(bg_path), NULL, draw_node);
}

/**
 * Create a full screen panel control
 *
 * @param children	Children controls to appear in the panel
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_fs_panel(Control* window, char* bg_path, Control* new_parent,
		Control** new_children) {
	return create_panel(window, 0, 0, WIN_W, WIN_H, bg_path, new_parent, new_children);
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
			SDL_LoadBMP(label_path), empty_select, draw_leaf);
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
			SDL_LoadBMP(label_path), on_select, draw_leaf);
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
	draw_children(node);
	draw_leaf(node);
}

/**
 * Draws given node's children -
 * calls the draw function of all children
 */
void draw_children(Control* node) {

	int i;
	int children_num = sizeof(node->children) / sizeof(Control*);

	for (i = 0; i < children_num; i++) {
		node->children[i]->draw(node->children[i]);
	}
}

/**
 * Draws given leaf - just draws element,
 * ignoring any children that might be
 */
void draw_leaf(Control* leaf) {
	SDL_BlitSurface(leaf->view, NULL, leaf->parent->view, NULL );
}

/**
 * Recursively reads UI tree until reaching the leaves,
 * then begins freeing their surfaces and themselves,
 * bottom up
 */
void free_tree(Control* root) {
	int i;
	int children_num = sizeof(root->children) / sizeof(Control*);
	for (i = 0; i < children_num; i++) {
		free_tree(root->children[i]);
	}
	SDL_FreeSurface(root->view);
	free(root);
}
