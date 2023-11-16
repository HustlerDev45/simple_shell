#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void exec_cmd(char *line);
int main(void);
int exe_cmd(char *command, char **env);
int prompt(int argc, char **argv, char **env);

#endif
