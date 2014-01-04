#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"

static int only_whitespaces(char *str);


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


command_t *parse_command_line(char *command_line) {
    int i;
    char first_word[MAX_COMMAND_LENGTH];
    command_t command;
    //command_t *res;
    //debug
    printf("2: %s", command_line);
    for (i=0; i<MAX_COMMAND_LENGTH; i++) {
        printf("%c\n", command_line[i]);
        if (isspace(command_line[i])) {
            break;
        }
        first_word[i] = command_line[i];
    }
    //debug
    printf("3: %s", command_line);
    printf("first word: %s", first_word);
    // switch
    if (strcmp(first_word, COMMAND_QUIT)) {
        command.command_code = COMMAND_CODE_QUIT;
        // no argument
        command.arg = -1;
    }
    else if (strcmp(first_word, COMMAND_RESTART)) {
        command.command_code = COMMAND_CODE_RESTART;
        // no argument
        command.arg = -1;
    }
    else if (strcmp(first_word, COMMAND_ADD_DISC)) {
        command.command_code = COMMAND_CODE_ADD_DISC;
        command.arg = str_to_int(command_line, strlen(COMMAND_ADD_DISC)+1);
    }
    else if (strcmp(first_word, COMMAND_SUGGEST_MOVE)) {
        command.command_code = COMMAND_CODE_SUGGEST_MOVE;
    }
    else if (strcmp(first_word, COMMAND_SET_STEPS)) {
        command.command_code = COMMAND_CODE_SET_STEPS;
        command.arg = str_to_int(command_line, strlen(COMMAND_SET_STEPS)+1);
    }
    else {
        command.command_code = COMMAND_CODE_NOT_FOUND;
        // no argument
        command.arg = -1;
    }
    return NULL;
    // if ((res = (command_t*)malloc(sizeof(command_t))) == NULL) {
    //     return NULL;
    // }
    // *res = command;
    // //debug
    // printf("%d %d", res->command_code, res->arg);
    // return res;
}

static int only_whitespaces(char *str) {
    while (*str != '\0') {
        if (!isspace(*str)) {
            return 0;
        }
        str ++;
    }
    return 1;
}


int str_to_int(char *str, int start) {
    int i = start;
    int res = 0;

    while ((48 <= str[i] && str[i] <= 57) || isspace(str[i])) {
        if (!isspace(str[i])) {
            res = res * 10 + (str[i] - 48);
        }
        i++;
    }
    return res;
}