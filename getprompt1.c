#include "shell.h"

/**
 * exe_cmd - Execute a command.
 * @command: Command to be executed.
 * @env: Array of environment variables.
 *
 * Return: Always 0 (Success), 1 on failure.
 *
 */
int exe_cmd(char *command, char **env)
{
	char *args[2];
	int status;
	pid_t child_pid;

	args[0] = command; /* assign command to args[0] */
	args[1] = NULL; /* assign NULL to args[1] */
	child_pid = fork(); /* create a child process */
	if (child_pid == -1) /* check for error */
	{
		perror("Error");
		return (1);
	}
	if (child_pid == 0) /* child process */
	{
		if (execve(args[0], args, env) == -1) /* execute command */
		{
			perror("Error"); /* print error if command not found */
			return (1);
		}
	}
	else /* parent process */
	{
		wait(&status); /* wait for child to finish */
	}
	return (0);
}

/**
 * main - Simple_shell UNIX command interpreter.
 * @argc: Number of arguments.
 * @argv: Array.
 * @env: Array of environment variables.
 *
 * Return: Always 0 (Success), 1 on failure.
 *
 */
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t lenght = 0;
	ssize_t nrd;
	char *token;

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("$ "); /* print prompt */
		nrd = getline(&line, &lenght, stdin); /* reads line from stdin */
		if (nrd == -1) /* checks for end of file */
		{
			free(line);
			printf("\n");
			exit(0);
		}
		line[nrd - 1] = '\0'; /* remove newline character */
		token = strtok(line, " "); /* split line by space */
		if (token == NULL) /* check for empty line */
			continue;

		if (exe_cmd(token, env) != 0) /* execute command */
		{
			free(line);
			exit(1);
		}
	}
	free(line);
	return (0);
}
