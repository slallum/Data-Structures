#include "connect4.h"

int main()
{
	char command_line[num_char+2]; /* Command line string includes the new line character ('\n') and a null character ('\0')  */

	while(1)
	{
		/* This function reads up to sizeof(fullcommand)-1 characters, or until it encounters the new line character. The function adds '\0' to the end of the array */
		if (fgets(command_line,sizeof(command_line),stdin)==NULL)
		{
			perror("Error: standard function fgets has failed"); /* error case */
			break; /* breaks the while(1) loop */
		}
		/* # of characters (excluding '\n') in command_line is <=num_char iff the condition takes place. */
		if (command_line[sizeof(command_line)-2]!='\n'&&strlen(command_line)==num_char+1)
		{
			printf("Error: command length must be less than or equal to %d characters\n",num_char);
			while(getchar()!='\n'){} /* read the remaining characters */
			continue;/* continue with  while(1) loop */
		}
		/* Checks that command-line is composed only from whitespace characters */
		if(only_whitespaces(command_line))
		{
			printf("Error: line command must have at least one non-whitespace character\n");
			continue; /* continue with  while(1) loop */
		}
		/*add code */
	}
	return 0;
}

int only_whitespaces(char * str)
{
	/* add code */
	return 1;
}
