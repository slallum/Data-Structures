/*
 * gui_framework.h
 *
 *  Created on: Feb 21, 2014
 *      Author: shir
 */

#ifndef GUI_FRAMEWORK_H_
#define GUI_FRAMEWORK_H_

#include <SDL.h>
#include <SDL_video.h>
#include <stdio.h>

/**
 * Generic control differentiated by content:
 * 1. Label		- view only
 * 2. Button	- view, on_select (holds logic for creating next view)
 * 3. Panel		- view (serving as background), children
 * 4. Window	- view, children
 */
struct Control {
	int x;
	int y;
	int width;
	int height;
	struct Control* parent;
	struct Control** children;
	SDL_Surface* view;
	void (*on_select)(struct Control*);
	void (*draw)(struct Control*);
};

typedef struct Control Control;

/**
 * Creates control with elements that all the types need.
 */
Control* create_control(int x, int y, int width, int height, Control* parent);

/**
 * Creates the window component - should be one as root of UI Tree
 *
 * @param children	component's children
 */
Control* create_window(Control* children);

/**
 * Create a panel control
 *
 * @param children	Children controls to appear in the panel
 * @param x, y		Position, relative to parent
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_panel(int x, int y, int width, int height, Control* new_parent,
		Control** new_children, int R, int G, int B);

/**
 * Creates a label control
 *
 * @param label_path	Path to find pic representing the label.
 * 						Loads the pic and draws it.
 */
Control* create_label(int x, int y, int width, int height, char* label_path,
		Control* parent);

/**
 * Creates a button control
 *
 * @param label_path	Path to find pic representing the label.
 * @param children		Controls needed when button is selected.
 * 						Could be the destination control or controls to be freed.
 * @param on_select		Function to be called when the button is selected
 */
Control* create_button(int x, int y, int width, int height, char* label_path,
		Control* parent, void (*on_select)(struct Control*));

/**
 * Nothing happens on select
 */
void empty_select(Control* control);

/**
 * Draws given node as a node in a tree - first draws element,
 * then calls the draw function of all children
 */
void draw_node(Control* node);

/**
 * Draws given leaf - just draws element,
 * ignoring any children that might be
 */
void draw_leaf(Control* leaf);

#endif /* GUI_FRAMEWORK_H_ */
