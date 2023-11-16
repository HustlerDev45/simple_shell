#include "shell.h"

/**
 * exec_cmd - Execute a command.
 * @line: The command to be executed.
 */
void exec_cmd(char *line)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		char *argv[] = {"/bin/sh", "-c", line, NULL};
		execv(argv[0], argv);
		perror("execv");
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - Entry point.
 * @$: Prompt to be displayed.
 *
 * Return: Always 0 (Success), otherwise EXIT_FAILURE on failure.
 */
int main(void)
{
	char *line = NULL;
	size_t lenght = 0;
	ssize_t rd;

	while (1)
	{
		printf("$ ");
		rd = getline(&line, &lenght, stdin);
		if (rd == -1)
			break;

		execute_command(line);
	}

	free(line);

	return (0);
}
