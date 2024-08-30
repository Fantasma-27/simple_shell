#include "main.h"
#include <sys/wait.h>  /* For wait */
#include <unistd.h>    /* For fork, execve, and related syscalls */
#include <stdlib.h>    /* For exit */
#include <stdio.h>     /* For perror */

/**
* execute_command - Executes a command using execve
* @argv: Argument vector containing the command and its arguments
*
* Description: This function creates a child process to execute the
*              command entered by the user. If the command cannot
*              be executed, it prints an error message.
*/
void execute_command(char **argv)
{
pid_t pid;
int status;

/* Fork a child process */
pid = fork();
if (pid == -1) /* Handle fork failure */
{
perror("Error");
exit(EXIT_FAILURE);
}
else if (pid == 0) /* Child process */
{
/* Execute the command */
if (execve(argv[0], argv, NULL) == -1)
{
perror(argv[0]);
exit(EXIT_FAILURE); /* Exit if execution fails */
}
}
else /* Parent process */
{
wait(&status); /* Wait for the child process to finish */
}
}
