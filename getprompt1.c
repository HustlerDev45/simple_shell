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

	args[0] = command;
	args[1] = NULL;
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		return (1);
	}
	if (child_pid == 0)
	{
		if (execve(args[0], args, env) == -1)
		{
			perror("Error");
			return (1);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}

/**
 * prompt - Simple_shell UNIX command interpreter.
 * @argc: Number of arguments.
 * @argv: Array.
 * @env: Array of environment variables.
 *
 * Return: Always 0 (Success), 1 on failure.
 *
 */
int prompt(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t lenght = 0;
	ssize_t nrd;
	char *token;

	(void)argc;
	(void)argv;

	while (1)
	{
		printf("$ ");
		nrd = getline(&line, &lenght, stdin);
		if (nrd == -1)
		{
			free(line);
			printf("\n");
			exit(0);
		}
		line[nrd - 1] = '\0';
		token = strtok(line, " ");
		if (token == NULL)
			continue;

		if (exe_cmd(token, env) != 0)
		{
			free(line);
			exit(1);
		}
	}
	free(line);
	return (0);
}
