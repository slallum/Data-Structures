#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"

static int only_whitespaces(char *str);

/*
 * getting a valid command line from the user
 * continues to run until gets a valid command line from the user
 * valid command line have no more than MAX_COMMAND_LENGTH charachters and not only whitespaces
 */
char *get_command_line() {
    char command_line[42];
    char *res;

    while(1)
    {
        /* This function reads up to sizeof(fullcommand)-1 characters, or until it encounters the new line character. The function adds '\0' to the end of the array */
        if (fgets(command_line,sizeof(command_line),stdin)==NULL)
        {
            perror("Error: standard function fgets has failed"); /* error case */
            return NULL;
        }

        /* # of characters (excluding '\n') in command_line is <=MAX_COMMAND_LENGTH iff the condition takes place. */
        if (command_line[sizeof(command_line)-2]!='\n'&&strlen(command_line)==MAX_COMMAND_LENGTH+1)
        {
            printf("Error: command length must be less than or equal to %d characters\n",MAX_COMMAND_LENGTH);
            while(getchar()!='\n'){} /* read the remaining characters */
            continue;/* continue with  while(1) loop */
        }
        /* Checks that command-line is composed only from whitespace characters */
        if (only_whitespaces(command_line))
        {
            printf("Error: command line must have at least one non-whitespace character\n");
            continue; /* continue with  while(1) loop */
        }
        res = &command_line[0];
        return res;
    }
}

/*
 * parses command line to a command_t struct which contains command code and argument
 * assumes the command line is a valid command line (not necessarily a command for connect4)
 */ 
command_t *parse_command_line(char *command_line) {
    command_t command = {0,0};
    char first[40];
    strcpy(first, command_line);
    char second[40];
    int i, j;
    command_t *res;

    for (i=0; i<40; i++) {
        // breaking the first command when reached to space or '\n'
        if (first[i] == ' ' || first[i] == '\n') {
            if (first[i] == ' ') {
                // now we'll get the second parameter, if it's exist
                for (j=i+1; j<40; j++) {
                    if (first[j] == '\n') {
                        second[j-(i+1)] = '\0';
                        break;
                    }
                    second[j-(i+1)] = first[j];
                }
            }
            first[i] = '\0';
            break;
        }
        first[i] = command_line[i];
    }
    // cool - we have the first and second parameter, now we'll get the proper code of the command
    // switch on the first word of the command
    if (strcmp(first, COMMAND_QUIT) == 0) {
        command.command_code = COMMAND_CODE_QUIT;
        // no argument
        command.arg = -1;
    }
    else if (strcmp(first, COMMAND_RESTART) == 0) {
        command.command_code = COMMAND_CODE_RESTART;
        // no argument
        command.arg = -1;
    }
    else if (strcmp(first, COMMAND_ADD_DISC) == 0) {
        command.command_code = COMMAND_CODE_ADD_DISC;
        command.arg = str_to_int(second, 0);
    }
    else if (strcmp(first, COMMAND_SUGGEST_MOVE) == 0) {
        command.command_code = COMMAND_CODE_SUGGEST_MOVE;
    }
    else if (strcmp(first, COMMAND_SET_STEPS) == 0) {
        command.command_code = COMMAND_CODE_SET_STEPS;
        command.arg = str_to_int(second, 0);
    }
    else {
        command.command_code = COMMAND_CODE_NOT_FOUND;
        // no argument
        command.arg = -1;
    }
    if ((res = (command_t*)malloc(sizeof(command_t))) == NULL) {
        perror("Error: standard function malloc has failed");
        return NULL;
    }
    *res = command;
    return res;
}


/* 
 * converts string to int from the index start
 * assumes the number stops at a space charachter (including '\n')
 */
int str_to_int(char *str, int start) {
    int i = start;
    int res = 0;

    while ((48 <= str[i] && str[i] <= 57) || isspace(str[i])) {
        if (!isspace(str[i])) {
            // str[i] - 48 gets us the actual value of the number
            res = res * 10 + (str[i] - 48);
        }
        i++;
    }
    return res;
}


// static functions

/*
 * checks if the string has only spaces in it (any kind of white space)
 */
static int only_whitespaces(char *str) {
    while (*str != '\0') {
        if (!isspace(*str)) {
            return 0;
        }
        str ++;
    }
    return 1;
}