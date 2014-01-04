#ifndef IO_H_
#define IO_H_

#define MAX_COMMAND_LENGTH 40

// error messages
#define ERROR_MESSAGE_COMMAND_LINE_LENGTH_EXCEEDED "Error: command length must be less than or equal to 40 characters\n"
#define ERROR_MESSAGE_FIRST_COMMAND_SET_NUMBER_STEPS "Error: first command must be set_number_steps\n"
#define ERROR_MESSAGE_STEPS_NON_ZERO "Error: number of minimax steps must be non-zero\n"
#define ERROR_MESSAGE_STEPS_OVER_LIMIT "Error: cannot set number of steps – too many steps\n"

// in-game messages
#define MESSAGE_GAME_OVER_USER_WINS "Game over: you win\n"
#define MESSAGE_GAME_OVER_COMP_WINS "Game over: computer wins\n"
#define MESSAGE_GAME_RESTARTED "Game restarted\n"

// CODES

// structs
typedef struct Command {
    int command_code; 
    int arg;
} command_t;

// functions
int get_command_line(char *command_line);
int parse_command_line(char *command_line);


#endif /* IO_H_ */
