#include "main.h"
/**
 * cd_command - change the current working directory.
 * @directory: the directory path to which wants to change.
 * @av : program name.
 * @count : argument count.
 * Return: void
 */
void cd_command(char *directory, char *av[], int count)
{
	char cwd[PATH_MAX];

	if (directory == NULL)
	{
		if (chdir("/") != 0)
		{
			perror("cd");
		}
		return;
	}
	if (count > 2)
	{
		fprintf(stderr, "%s : cd : %s : too many arguments\n", av[0], directory);
	} else if (chdir(directory) != 0)
	{
		fprintf(stderr, "%s : cd : %s : No such file or directory\n", av[0],
				directory);
	} else
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
		}
	}
}
/**
 * getInput - reads user input from the command line
 * @line: A pointer to a string that stores the user's input.
 * @buffer: A pointer to a size_t variable for buffer management.
 * Return: void
 */
void getInput(char **line, size_t *buffer)
{
	ssize_t characters;

	if (*line)
	{
		free(*line);
		*line = NULL;
	}
	do {
		printf("$ ");
		characters = getline(line, buffer, stdin);
		if (characters == -1)
		{
			if (feof(stdin))
			{
				fprintf(stderr, "exit\n");
				free(*line); /* fix the still reachable data */
				exit(0);
			}
			perror("getline error during reading\n");
			exit(1);
		}
		rm_newline(*line);
	} while (!**line);
}
/**
 * tokenize_line - Splits a string into an array of tokens.
 * @pieces_array: A pointer to a pointer to an array of strings.
 * @line: The input string to be split into tokens.
 * @count: A pointer to an integer to store the number of tokens.
 * Return: void.
 */
void tokenize_line(char ***pieces_array, char *line, int *count)
{
	char *token = NULL;
	int i = 0, j, len;

	*count = nmb_pieces(line);
	*pieces_array = (char **)malloc(sizeof(char *) * (*count + 1));
	if (pieces_array == NULL)
	{
		perror("memory allocation error\n");
		return;
	}
	token = strtok(line, " ");
	while (token)
	{
		len = strlen(token);
		(*pieces_array)[i] = (char *)malloc(sizeof(char) * (len + 1));
		if ((*pieces_array)[i] == NULL)
		{
			perror("memory allocation error\n");
			for (j = 0; j < i; j++)
				free((*pieces_array)[j]);
			free(*pieces_array);
			return;
		}
		strcpy((*pieces_array)[i], token);
		i++;
		token = strtok(NULL, " ");
	}
	(*pieces_array)[i] = NULL;
}
/**
 * free_data - Frees allocated memory .
 * @pieces_array: A pointer to a pointer to an array of strings.
 * @line: A pointer to a string.
 * @i: the loop index for the array of strings.
 * @count: number of elements in the array of strings.
 */
void free_data(char ***pieces_array, char **line, int i, int count)
{
	for (i = 0; i < count; i++)
		free((*pieces_array)[i]);
	free(*pieces_array);
	free(*line);
	*line = NULL;
}
