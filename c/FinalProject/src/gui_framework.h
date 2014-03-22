/*
 * gui_framework.h
 *
 *  Created on: Feb 21, 2014
 *      Author: shir
 */

#ifndef GUI_FRAMEWORK_H_
#define GUI_FRAMEWORK_H_

#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include "playit_conf.h"

/**
 * Representing a structure of a link in a linked list,
 * holding as a content a Control
 */
struct Link {
	struct Control* value;
	struct Link* next;
};

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
	int i;
	int j;
	int width;
	int height;
	struct Link* children_head;
	struct Control* parent;
	SDL_Surface* view;
	int (*on_select)(struct Control*);
	int (*draw)(struct Control*, struct Control*);
};

typedef struct Control Control;
typedef struct Link Link;

/**
 * Perform operations needed for the SDL framework to work
 * returns 1 if went smoothly, 0 o\w
 */
int init_fw();

/**
 * Creates control with elements that all the types need.
 */
Control* create_control(int x, int y, int i, int j, int width, int height,
		Link* children_head, SDL_Surface* view,
		int (*on_select)(struct Control*), int (*draw)(struct Control*, struct Control*));

/**
 * Creates the window component - should be one as root of UI Tree
 *
 * @param children	component's children
 */
Control* create_window(Link* children_head);

/**
 * Create a panel control
 *
 * @param children	Children controls to appear in the panel
 * @param x, y		Position, relative to parent
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_panel(int x, int y, int i, int j, int width, int height, char* bg_path,
		Link* children_head);

/**
 * Create a full screen panel control
 *
 * @param children	Children controls to appear in the panel
 * @param R, G, B	Background colour numbers parent(RGB) for the parts of the panel shown
 */
Control* create_fs_panel(char* bg_path, Link* children_head);

/**
 * Creates a label control
 *
 * @param label_path	Path to find pic representing the label.
 * 						Loads the pic and draws it.
 */
Control* create_label(int x, int y, int i, int j, int width, int height, char* label_path);

/**
 * Creates a button control
 *
 * @param label_path	Path to find pic representing the label.
 * @param children		Controls needed when button is selected.
 * 						Could be the destination control or controls to be freed.
 * @param on_select		Function to be called when the button is selected
 */
Control* create_button(int x, int y, int i, int j, int width, int height, char* label_path,
		int (*on_select)(struct Control*));

/**
 * Nothing happens on select
 */
int empty_select(Control* control);

/**
 * Draws given node as a node in a tree - first draws element,
 * then calls the draw function of all children
 */
int draw_node(Control* node, Control* parent);

/**
 * Draws given node's children -
 * calls the draw function of all children
 */
int draw_children(Control* node, Control* parent);

/**
 * Draws given leaf - just draws element,
 * ignoring any children that might be
 */
int draw_leaf(Control* leaf, Control* parent);

/**
 * Recursively reads UI tree until reaching the leaves,
 * then begins freeing their surfaces and themselves,
 * bottom up
 */
void free_tree(Control* root);

/**
 * Event handler
 */
int poll_event(Control* ui_tree);

/**
 * Find the element in the ui_tree containing the point x, y
 */
int clickElement(Control* ui_tree, int x, int y);

/**
 * Calls for window flip and checks for errors
 */
int flip(Control* window);

/**
 * Calls for window draw and checks for errors
 */
int draw(Control* window);


#endif /* GUI_FRAMEWORK_H_ */
