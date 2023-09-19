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
		valid_chars = 1;
		for (i = 0; i < count; i++) /* check characters*/
		{
			for (j = 0; pieces_array[i][j] != '\0'; j++)
			{
				if (!validate_char(pieces_array[i][j]))
				{
					fprintf(stderr, "%s: %s :invalid character in input string\n",
							av[0], pieces_array[0]);
					valid_chars = 0;
					break;
				}
			}
			if (!valid_chars)
			{
				break;
			}
		}
		if (!valid_chars)
		{
			free_data(&pieces_array, &line, i, count);
			continue;
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
		if ((_execute_cmd(pieces_array[0], &pieces_array,
						av[0], &line, count)) != 0)
		{
			continue;
		}
		free_data(&pieces_array, &path, i, count);
	}
	free_data(NULL, &line, i, count);
	return (0);
}
