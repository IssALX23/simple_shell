#include "main.h"
/**
 * rm_newline - remoe newline from the end of string
 * @str: input string
 *
 * Return: void
 */
void rm_newline(char *str)
{
	int count = strlen(str);

	if (str[count - 1] == '\n')
		str[count - 1] = '\0';
}
/**
 * nmb_pieces - counts tokens in string
 * @str: input string
 *
 * Return: count of pieces or tokens
 */
int nmb_pieces(char *str)
{
	int count = 0;
	char *piece;
	char *copy = strdup(str);

	piece = strtok(copy, " ");
	while (piece != NULL)
	{
		count++;
		piece = strtok(NULL, " ");
	}
	free(copy);
	return (count);
}
/**
 * nmb_spaces - counts spaces in string
 * @str: input string
 *
 * Return: count of spaces
 */
int nmb_spaces(char *str)
{
	int len = strlen(str), i = 0, sp_count = 0;

	while (str[i] && i < len)
	{
		if (!isspace(str[i]))
		{
			sp_count = 1;
			break;
		}
		i++;
	}
	return (sp_count);
}
/**
 * check_char - check if characters are valid
 * @c: input character
 *
 * Return: 1 if success or 0 if fails
 */
int check_char(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9') || c == ' ' || c == '.'
			|| c == '_' || c == '-' || c == '/');
}
/**
 * print_env - print envirment
 *
 * Return: void
 */
void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}
