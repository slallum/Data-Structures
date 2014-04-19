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
	atexit(TTF_Quit);
	TTF_Init();
	return 1;
}

/**
 * Creates control with elements that all the types need.
 */
Control* create_control(int x, int y, int i, int j, int width, int height,
		Link* children_head, SDL_Surface* view,
		int (*on_select)(struct Control*),
		int (*draw)(struct Control*, struct Control*)) {
	Control* new_control = (Control*) malloc(sizeof(Control));
	if (new_control == NULL) {
		printf("ERROR: Failed to create new gui control");
		return NULL;
	}
	new_control->x = x;
	new_control->y = y;
	new_control->i = i;
	new_control->j = j;
	new_control->width = width;
	new_control->height = height;
	new_control->children_head = children_head;
	new_control->parent = NULL;
	new_control->view = view;
	new_control->on_select = on_select;
	new_control->draw = draw;
	while ((children_head != NULL )&& (children_head->value != NULL)){
		children_head->value->parent = new_control;
		children_head = children_head->next;
	}
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
	return create_control(0, 0, 0, 0, WIN_W, WIN_H, children_head, view,
			empty_select, draw_children);
}

/**
 * Create a panel control
 *
 * @param children	Children controls to appear in the panel
 * @param x, y		Position, relative to parent
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_panel(int x, int y, int i, int j, int width, int height,
		char* bg_path, Link* children_head) {
	Control* panel;
	SDL_Surface *img;
	if (children_head == NULL) {
		return NULL;
	}
	img = load_image(bg_path);
	if (img == NULL ) {
		printf("Error: failed to load image: %s\n", SDL_GetError());
		return NULL ;
	}
	panel = create_control(x, y, i, j, width, height, children_head, img,
			empty_select, draw_node);
	if (panel == NULL) {
		free_UI_children(children_head);
	}
	return panel;
}

/**
 * Create a full screen panel control
 *
 * @param children	Children controls to appear in the panel
 * @param R, G, B	Background colour numbers (RGB) for the parts of the panel shown
 */
Control* create_fs_panel(char* bg_path, Link* children_head) {

	return create_panel(0, 0, 0, 0, WIN_W, WIN_H, bg_path, children_head);
}

/**
 * Creates a label control
 *
 * @param label_path	Path to find pic representing the label.
 * 						Loads the pic and draws it.
 */
Control* create_label(int x, int y, int i, int j, int width, int height, char* label_path) {
	SDL_Surface *img = load_image(label_path);
	if (img == NULL ) {
		img = create_text(label_path, width, height);
		if (img == NULL) {
			return 0;
		}
	}
	return create_control(x, y, i, j, width, height, NULL, img, empty_select,
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
Control* create_button(int x, int y, int i, int j, int width, int height, char* label_path,
		int (*on_select)(struct Control*)) {
	SDL_Surface *img = load_image(label_path);
	if (img == NULL ) {
		// Could not load image - assume it is meant to be text
		img = create_text(label_path, width, height);
		if (img == NULL) {
			return 0;
		}
	}
	return create_control(x, y, i, j, width, height, NULL, img, on_select, draw_leaf);
}

/**
 * Creates a text element with given title
 * Uses a plain pre-defined background and creates title on the fly
 */
SDL_Surface* create_text(char* title, int width, int height) {
	SDL_Surface *text_image, *img;
	SDL_Color text_color;
	TTF_Font *text_font =  TTF_OpenFont(TEXT_FONT, TEXT_SIZE);
	if (text_font == NULL) {
		printf("Error: failed to load font: %s\n", TEXT_FONT);
		return NULL;
	}
	text_color.r = 0xe0;
	text_color.g = 0xbc;
	text_color.b = 0xe0;
	text_image = TTF_RenderText_Solid(text_font, title, text_color);
	if (text_image == NULL) {
		printf("Error: Failed to create text image for %s", title);
		return NULL;
	}
	// Determine whether text is a tile or a button
	if (strlen(title) == 1) {
		img = load_image(TEXT_CHAR_BG);
	} else {
		img = load_image(TEXT_BG);
	}
	if (img == NULL ) {
		printf("Error: failed to load image: %s\n", SDL_GetError());
		return NULL ;
	}
	SDL_Rect rect = { (width - (strlen(title) * 17)) / 2 , 8, strlen(title) * 17, height - 16 };
	// Text titles come from dynamic allocation and must be freed, once used
	free(title);
	if (SDL_BlitSurface(text_image, 0, img, &rect) != 0) {
		printf("Error: Failed blit text to bg: %s\n", SDL_GetError());
		return NULL;
	}
	SDL_free(text_font);
	SDL_FreeSurface(text_image);
	return img;
}

/**
 * Nothing happens on select
 */
int empty_select(Control* control) {
	return 0;
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
void free_UI_tree(Control* root) {

	if (root != NULL) {
		free_UI_children(root->children_head);
		SDL_FreeSurface(root->view);
		root->parent = NULL;
		free(root);
	}
}

/**
 * Frees all elements in linked list of children
 */
void free_UI_children(Link* head) {
	Link *prev;
	while ((head != NULL) && (head->value != NULL)) {
		prev = head;
		head = prev->next;
		prev->next = NULL;
		free_UI_tree(prev->value);
		free(prev);
	}
}

/**
 * Event handler
 */
int poll_event(Control* ui_tree) {

	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		switch (e.type) {
		case (SDL_QUIT):
			return 1;
		case (SDL_MOUSEBUTTONUP):
			return clickElement(ui_tree, e.button.x, e.button.y);
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
int clickElement(Control* ui_tree, int x, int y) {

	Link* head = ui_tree->children_head;
	int ret = -1;
	if ((ui_tree->x <= x) && (ui_tree->x + ui_tree->width >= x)
				&& (ui_tree->y <= y) && (ui_tree->y + ui_tree->height >= y)) {
		if (head == NULL) {
			return ui_tree->on_select(ui_tree);
		}
		while ((ret == -1) && (head != NULL )) {
			ret = clickElement(head->value, x - ui_tree->x, y - ui_tree->y);
			head = head->next;
		}
		if (ret == -1) {
			return 0;
		}
	}
	return ret;
}

/**
 * Calls for window flip and checks for errors
 */
int flip(Control* window) {
	if (SDL_Flip(window->view) != 0) {
		printf("Error: Failed to flip buffer: %s\n", SDL_GetError());
		return 0;
	}
	return 1;
}

/**
 * Calls for window draw and checks for errors
 */
int draw(Control* window) {
	if (!window->draw(window, NULL )) {
		printf("Error: Failed to screen\n");
		return 0;
	}
	return 1;
}

/**
 * Attaches given file name to constant images path
 * in order to create a full path to the image.
 * Then loads the image, using sdl
 */
SDL_Surface *load_image(char* file_name) {
	SDL_Surface *img, *final_img;
	char* path = (char*) malloc(strlen(IMGS_PATH) + strlen(file_name) + 1);
	if (path == NULL) {
		printf("Error: Failed to create path for %s", file_name);
		return NULL;
	}
	strcpy(path, IMGS_PATH);
	strcat(path, file_name);
	img = SDL_LoadBMP(path);
	free(path);
	final_img = SDL_DisplayFormat(img);
	SDL_FreeSurface(img);
	return final_img;
}

