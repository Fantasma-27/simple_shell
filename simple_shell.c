#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/* Function prototypes */
char **parse_input(char *input);

/**
* main - A simple UNIX command line interpreter with argument support.
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
char **args;

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

/* Parse the input into arguments */
args = parse_input(input);
if (args == NULL)
{
perror("parse_input");
free(input);
exit(EXIT_FAILURE);
}

/* Create a new process */
pid = fork();
if (pid == -1)
{
perror("fork");
free(input);
exit(EXIT_FAILURE);
}

if (pid == 0)  /* Child process */
{
/* Execute the command */
execvp(args[0], args);
/* If execvp returns, it must have failed */
perror("Execution error");
exit(EXIT_FAILURE);
}
else  /* Parent process */
{
/* Wait for the child process to finish */
waitpid(pid, &status, 0);
}

/* Free the allocated memory for arguments */
free(args);
}

free(input);
return (0);
}

/**
* parse_input - Split input string into arguments.
* @input: The input string to parse.
*
* Return: An array of arguments or NULL on failure.
*/
char **parse_input(char *input)
{
char **args = NULL;
char *token = NULL;
size_t count = 0;
size_t bufsize = 64; /* Initial buffer size */

/* Allocate initial buffer */
args = malloc(bufsize * sizeof(char *));
if (args == NULL)
{
perror("malloc");
return (NULL);
}

token = strtok(input, " ");
while (token != NULL)
{
args[count] = token;
count++;

/* Reallocate buffer if needed */
if (count >= bufsize)
{
bufsize *= 2;
args = (char **)realloc(args, bufsize * sizeof(char *));
if (args == NULL)
{
perror("realloc");
return (NULL);
}
}

token = strtok(NULL, " ");
}

args[count] = NULL; /* Null-terminate the array */

return (args);
}
