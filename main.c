#include "main.h"
/**
 * main - Entry point of the shell program.
 * @ac: The number of command-line arguments.
 * @av: An array of strings representing the command-line arguments.
 * Return: 0 in success, or an error code if an error occurs.
 */
int main(int ac, char **av)
{
	int count = 0, i = 0, j = 0, val = 0, sp_count = 0,
	    (*validate_char)(char) = check_char;
	char *line = NULL, **pieces_array = NULL, *path = NULL;
	size_t buffer = 0;
	pid_t child;
	(void)ac;

	while (1)
	{
	getInput(&line, &buffer);
	sp_count = nmb_spaces(line);
	if (sp_count == 0)
	{
		free(line);
		line = NULL;
		continue;
	}
	tokenize_line(&pieces_array, line, &count);
	for (i = 0; i < count; i++) /* check characters*/
	{
		for (j = 0; pieces_array[i][j] != '\0'; j++)
		{
			if (!validate_char(pieces_array[i][j]))
			{
				perror("invalid character in input string\n");
				continue;
			}
		}
	}
	if (strcmp(pieces_array[0], "exit") == 0) /* handle built-ins*/
	{
		free_data(&pieces_array, &line, i, count);
		fprintf(stderr, "exit\n");
		exit(1);
	} else if (strcmp(pieces_array[0], "env") == 0)
	{
		print_env();
		free_data(&pieces_array, &line, i, count);
		continue;
	} else if (strcmp(pieces_array[0], "cd") == 0)
	{
		cd_command(pieces_array[1], av, count);
		free_data(&pieces_array, &line, i, count);
		continue;
	}
	path = _which(pieces_array[0]); /* handle path */
	if (path == NULL)
	{
		fprintf(stderr, "%s: %s: command not found\n", av[0], pieces_array[0]);
		for (i = 0; i < count; i++)
			free(pieces_array[i]);
		free(pieces_array);
		free(line);
		line = NULL;
		continue; /*output promt even if cmd don't exist*/
	}
	child = fork(); /* execute cmd */
	if (child == -1)
		perror("failed to fork\n");
	if (child == 0)
	{
		val = execve(path, pieces_array, NULL);
		if (val == -1)
		{
			perror("error executing\n");
			free_data(&pieces_array, &line, i, count);
			free(path);
			path = NULL;
			exit(1);
		}
	} else
		wait(NULL);
	for (i = 0; i < count; i++) /*free memory at the end */
		free(pieces_array[i]);
	free(pieces_array);
	if (path)
		free(path);
	}
	free(line);
	line = NULL;
	return (0);
}
