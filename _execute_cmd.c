#include "main.h"
/**
 * execute_cmd - checks path and execute command
 * @command: string
 * @pieces_array: pointer to an array of pointers
 * @program_name: string
 * @line: string
 * @count: integer
 *
 * Return: integer
 */
int _execute_cmd(char *command, char ***pieces_array,
		char *program_name, char **line, int count)
{
	char *path = _which(command);
	int i = 0, val = 0;
	pid_t child;

	if (path == NULL)
	{
		fprintf(stderr, "%s: %s: command not found\n", program_name, command);
		for (i = 0; i < count; i++)
			free(*pieces_array[i]);
		free(*pieces_array);
		return (2);
	}
	child = fork();
	if (child == -1)
	{
		perror("failed to fork\n");
		exit(0);
	}

	if (child == 0)
	{
		val = execve(path, *pieces_array, environ);
		if (val == -1)
		{
			perror("error executing\n");
			free(*line);
			for (i = 0; i < count; i++)
				free(*pieces_array[i]);
			free(*pieces_array);
			free(path);
			exit(0);
		}
	} else
	{
		wait(NULL);
		free(path);
	}
	return (0);
}
