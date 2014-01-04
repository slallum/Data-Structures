#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "io.h"

static int only_whitespaces(char *str);


int get_command_line(char *command_line)
{
    if ((command_line = (char*)malloc(sizeof(command_line))) == NULL) {
        perror("Error: standard function malloc has failed");
        return 0;
    }

    //char command_line[MAX_COMMAND_LENGTH+2]; /* Command line string includes the new line character ('\n') and a null character ('\0')  */
    while(1)
    {
        /* This function reads up to sizeof(fullcommand)-1 characters, or until it encounters the new line character. The function adds '\0' to the end of the array */
        if (fgets(command_line,sizeof(command_line),stdin)==NULL)
        {
            perror("Error: standard function fgets has failed"); /* error case */
            return 0;
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
            printf("Error: line command must have at least one non-whitespace character\n");
            continue; /* continue with  while(1) loop */
        }
        /*add code */
    }
    return 0;
}


int parse_command_line(char *command_line) {
    return -1;
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