#ifndef MAIN_H
#define MAIN_H

#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

extern char **environ;
extern int command_failed;

char *_which(char *cmd);
char *_print_env(void);
void get_name(char *name);
void print_env(void);
int check_char(char c);
int nmb_spaces(char *str);
int nmb_pieces(char *str);
void rm_newline(char *str);
void cd_command(char *directory, char *av[], int count);
void getInput(char **line, size_t *buffer);
void tokenize_line(char ***pieces_array, char *line, int *count);
int _execute_cmd(char *command, char ***pieces_array,
		char *program_name, char **line, int count);
void free_data(char ***pieces_array, char **line, int i, int count);
void check_builtins(int checker, char ***pieces_array, char **line, int i,
		int count, char **av);
#endif
