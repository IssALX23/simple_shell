#include "main.h"
/**
 * print_err_msg - prints error message
 * @x: integer
 *
 * Return: void
 */
void print_err_msg(int x)
{
	if (x == 1)
	{
		perror("failed to allocate memory");
		return;
	} else if (x == 2)
	{
		perror("failed to open file\n");
		return;
	}
}
/**
 * _which - returns the path of the input command
 * @cmd: input string
 *
 * Return: string of the path or NULL
 */
char *_which(char *cmd)
{
	char *new_cmd = NULL, buffer[1024], *new_buff = NULL;
	int count = 0;
	size_t size = strlen("which ") + 1;
	FILE *fp;

	if (!cmd)
		return (NULL);
	size += strlen(cmd);
	new_cmd = (char *)malloc(size);
	if (!new_cmd)
		print_err_msg(1);
	snprintf(new_cmd, size, "which ");
	if (cmd)
		strcat(new_cmd, cmd);
	fp = popen(new_cmd, "r");
	if (fp == NULL)
	{
		free(new_cmd);
		print_err_msg(2);
	}
	if (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		count = strlen(buffer);
		if (buffer[count - 1] == '\n')
			buffer[count - 1] = '\0';
		new_buff = (char *)malloc(strlen(buffer) + 1);
		if (!new_buff)
		{
			free(new_cmd);
			print_err_msg(1);
		}
		strcpy(new_buff, buffer);
		pclose(fp);
		free(new_cmd);
		return (new_buff);
	}
	free(new_cmd);
	pclose(fp);
	return (new_buff);
}
