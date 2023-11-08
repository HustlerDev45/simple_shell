#include "shell.h"

void exec_cmd(char *line)
{
	/* creation of a new process */
	pid_t pid = fork();
	/* here if fork fails it'll print an error msg and continue */
	if (pid < 0)
	{
		perror("fork");
		return;
	}

	/* the child process */
	if (pid == 0)
	{
		char *argv[] = {"/bin/sh", "-c", line, NULL};
		execv(argv[0], argv);
		perror("execv");
		exit(EXIT_FAILURE);
	}
	else
	{
		/* the parent proces waits for the child to finish */
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

	/* the loop that reads lines and execute them */
	while (1)
	{
		printf("$ ");
		rd = getline(&line, &lenght, stdin);
		/* Break the loop if getline fails */
		if (rd == -1)
			break;

		/* Add a blank line here */

		execute_command(line);
	}

	/* frees the memory allocated by getline */
	free(line);

	return (0);
}
