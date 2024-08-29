#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
* main - A simple UNIX command line interpreter.
* @argc: Number of arguments.
* @argv: Array of argument strings.
*
* Return: 0 on success.
*/
int main(int argc, char **argv)
{
char *input = NULL;
size_t len = 0;
ssize_t read;
pid_t pid;
int status;

(void)argc;  /* Unused parameter */
(void)argv;  /* Unused parameter */

while (1)
{
/* Display the prompt */
printf("#cisfun$ ");
fflush(stdout);

/* Read user input */
read = getline(&input, &len, stdin);
if (read == -1)
{
if (feof(stdin))  /* End of file (Ctrl+D) */
{
free(input);
printf("\n");
exit(EXIT_SUCCESS);
}
perror("getline");
exit(EXIT_FAILURE);
}

/* Remove newline character from input */
if (input[read - 1] == '\n')
{
input[read - 1] = '\0';
}

/* Check for exit command */
if (strcmp(input, "exit") == 0)
{
free(input);
printf("\n");
exit(EXIT_SUCCESS);
}

/* Create a new process */
pid = fork();
if (pid == -1)
{
perror("fork");
exit(EXIT_FAILURE);
}

if (pid == 0)  /* Child process */
{
/* Execute the command */
execlp(input, input, (char *)NULL);
/* If execlp returns, it must have failed */
perror("Execution error");
exit(EXIT_FAILURE);
}
else  /* Parent process */
{
/* Wait for the child process to finish */
waitpid(pid, &status, 0);
}
}

free(input);
return (0);
}
