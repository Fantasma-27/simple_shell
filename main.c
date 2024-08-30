#include "main.h"
#include <sys/wait.h>  /* For wait */
#include <unistd.h>    /* For fork, execve, and related syscalls */
#include <stdlib.h>    /* For exit */
#include <stdio.h>     /* For write and perror */
#include <string.h>    /* For strcmp */

/**
* handle_exit - Handles the 'exit' command
*
* @line: The input line to check
*/
void handle_exit(char *line)
{
    if (strcmp(line, "exit") == 0)
    {
        free(line);
        exit(EXIT_SUCCESS);
    }
}

/**
* read_input - Reads a line of input from stdin
*
* Return: Pointer to the input line, or NULL if an error occurs
*/
char *read_input(void)
{
    char *line = NULL;
    size_t len = 0;

    write(STDOUT_FILENO, "($) ", 4);
    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return (NULL);
    }

    /* Remove trailing newline character */
    if (line[strlen(line) - 1] == '\n')
        line[strlen(line) - 1] = '\0';

    return (line);
}

/**
* main - Entry point of the shell program
*
* Return: Always 0 (Success)
*/
int main(void)
{
    char *line;
    char *args[2];

    while (1)
    {
        line = read_input();
        if (line == NULL)
            exit(EXIT_SUCCESS);

        handle_exit(line);

        /* Prepare the argument vector for the command */
        args[0] = line;
        args[1] = NULL;

        /* Execute the command */
        execute_command(args);
    }

    return (0);
}
