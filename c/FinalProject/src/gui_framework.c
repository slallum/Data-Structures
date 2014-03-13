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
Control* create_control(int x, int y, int width, int height,
		Link* children_head, SDL_Surface* view,
		void (*on_select)(struct Control*),
		int (*draw)(struct Control*, struct Control*)) {
	Control* new_control = (Control*) malloc(sizeof(Control));
	new_control->x = x;
	new_control->y = y;
	new_control->width = width;
	new_control->height = height;
	new_control->children_head = children_head;
	new_control->view = view;
	new_control->on_select = on_select;
	new_control->draw = draw;
	return new_control;
}

/**
 * Creates the window component - should be one as root of UI Tree
 *
 * @param children	component's children
 */
Control* create_window(Link* children_head) {
	SDL_WM_SetCaption(HEADING, HEADING);
	SDL_Surface* view = SDL_SetVideoMode(WIN_W, WIN_H, 0,
			SDL_HWSURFACE | SDL_DOUBLEBUF);
	if (view == NULL ) {
		printf("Error: Failed to set video mode: %s\n", SDL_GetError());
		return NULL ;
	}
	return create_control(0, 0, WIN_W, WIN_H, children_head, view, NULL,
			draw_children);
}

/**
 * Create a panel control
 *
 * @param children	Children controls to appear in the panel
 * @param x, y		Position, relative to parent
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_panel(int x, int y, int width, int height, char* bg_path,
		Link* children_head) {
	SDL_Surface *img = SDL_LoadBMP(bg_path);
	if (img == NULL ) {
		printf("Error: failed to load image: %s\n", SDL_GetError());
		return NULL ;
	}
	img = SDL_DisplayFormat(img);
	return create_control(x, y, width, height, children_head, img, NULL,
			draw_node);
}

/**
 * Create a full screen panel control
 *
 * @param children	Children controls to appear in the panel
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_fs_panel(char* bg_path, Link* children_head) {
	return create_panel(0, 0, WIN_W, WIN_H, bg_path, children_head);
}

/**
 * Creates a label control
 *
 * @param label_path	Path to find pic representing the label.
 * 						Loads the pic and draws it.
 */
Control* create_label(int x, int y, int width, int height, char* label_path) {
	SDL_Surface *img = SDL_LoadBMP(label_path);
	if (img == NULL ) {
		printf("Error: failed to load image: %s\n", SDL_GetError());
		return NULL ;
	}
	img = SDL_DisplayFormat(img);
	return create_control(x, y, width, height, NULL, img, empty_select,
			draw_leaf);
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
		void (*on_select)(struct Control*)) {
	SDL_Surface *img = SDL_LoadBMP(label_path);
	if (img == NULL ) {
		printf("Error: Failed to load image: %s\n", SDL_GetError());
		return NULL ;
	}
	img = SDL_DisplayFormat(img);
	return create_control(x, y, width, height, NULL, img, on_select, draw_leaf);
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
int draw_node(Control* node, Control* parent) {
	if (draw_children(node, NULL )) {
		return draw_leaf(node, parent);
	}
	return 0;
}

/**
 * Draws given node's children -
 * calls the draw function of all children
 */
int draw_children(Control* node, Control* parent) {

	int orderly = 1;
	Link* head = node->children_head;
	while (orderly && (head != NULL )) {
		if (head->value == NULL ) {
			orderly = 0;
		} else {
			orderly = head->value->draw(head->value, node);
		}
		head = head->next;
	}
	return orderly;
}

/**
 * Draws given leaf - just draws element,
 * ignoring any children that might be
 */
int draw_leaf(Control* leaf, Control* parent) {
	SDL_Rect to_place = { leaf->x, leaf->y, leaf->width, leaf->height };
	if (SDL_BlitSurface(leaf->view, 0, parent->view, &to_place) != 0) {
		printf("Error: Failed to blit image: %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}

/**
 * Recursively reads UI tree until reaching the leaves,
 * then begins freeing their surfaces and themselves,
 * bottom up
 */
void free_tree(Control* root) {
	Link* prev;
	Link* next = root->children_head;
	while (next != NULL ) {
		free_tree(next->value);
		prev = next;
		next = prev->next;
		free(next);
	}
	SDL_FreeSurface(root->view);
	free(root);
}

int poll_event(Control* ui_tree) {

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case (SDL_QUIT):
			return 1;
		case (SDL_MOUSEBUTTONUP):
			clickElement(ui_tree, e.button.x, e.button.y);
			break;
		default:
			break;
		}
	}
	SDL_Delay(15);
	return 0;
}

/**
 * Find the element in the ui_tree containing the point x, y
 */
void clickElement(Control* ui_tree, int x, int y) {

	Link* head = ui_tree->children_head;
	if (head == NULL ) {
		if ((head->value->x <= x) && (head->value->x + head->value->width >= x)
				&& (head->value->y <= y)
				&& (head->value->y + head->value->height >= y)) {
			head->value->on_select(head->value);
		}
	}
	while (head != NULL ) {
		clickElement(head->value, x, y);
		head = head->next;
	}
}

