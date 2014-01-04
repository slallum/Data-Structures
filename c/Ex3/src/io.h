#ifndef IO_H_   
#define IO_H_

#define MAX_COMMAND_LENGTH 40

// commands
#define COMMAND_SET_STEPS "set_number_steps"
#define COMMAND_SUGGEST_MOVE "suggest_move"
#define COMMAND_ADD_DISC "add_disc"
#define COMMAND_QUIT "quit"
#define COMMAND_RESTART "restart_game"

// command codes
#define COMMAND_CODE_NOT_FOUND 0
#define COMMAND_CODE_SET_STEPS 1
#define COMMAND_CODE_SUGGEST_MOVE 2
#define COMMAND_CODE_ADD_DISC 3
#define COMMAND_CODE_QUIT 4
#define COMMAND_CODE_RESTART 5


// error messages
#define ERROR_MESSAGE_COMMAND_LINE_LENGTH_EXCEEDED "Error: command length must be less than or equal to 40 characters\n"
#define ERROR_MESSAGE_FIRST_COMMAND_SET_NUMBER_STEPS "Error: first command must be set_number_steps\n"
#define ERROR_MESSAGE_STEPS_NON_ZERO "Error: number of minimax steps must be non-zero\n"
#define ERROR_MESSAGE_STEPS_OVER_LIMIT "Error: cannot set number of steps - too many steps\n"
#define ERROR_MESSAGE_GAME_OVER "Error: game is over\n"
#define ERROR_MESSAGE_COMMAND_NOT_FOUND "Error: command not found\n"
#define ERROR_MESSAGE_COLUMN_NUMBER_NOT_VALID "Error: column number must be in range 1-7\n"
#define ERROR_MESSAGE_COLUMN_FULL "Error: column (%d) is full\n"

// in-game messages
#define MESSAGE_GAME_OVER_USER_WINS "Game over: you win\n"
#define MESSAGE_GAME_OVER_COMP_WINS "Game over: computer wins\n"
#define MESSAGE_GAME_RESTARTED "Game restarted\n"
#define MESSAGE_GAME_COMPUTER_MOVE "Computer move: add disc to column %d\n"


// CODES

// structs
typedef struct Command {
    int command_code; 
    int arg;
} command_t;

// functions
char *get_command_line();
command_t *parse_command_line(char *command_line);

char *get_first_word(const char *command_line);
int str_to_int(char *str, int start);

#endif /* IO_H_ */
