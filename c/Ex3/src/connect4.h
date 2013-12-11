#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<stdarg.h>

#define num_char 40 /* # of characters in command  */

struct element_s {
	struct vertex_s		*node;

	struct element_s	*next;
	struct element_s	*prev;
};

typedef struct element_s *  element;
typedef int** board_t;

struct linked_list_s {
	element head;
	element tail;
};

typedef struct linked_list_s *  linked_list;

struct vertex_s {
	unsigned int	mov_col;
	board_t			game_state;
	int				score;

	linked_list		edges;
};

typedef struct  vertex_s * vertex;

int only_whitespaces(char * str);
