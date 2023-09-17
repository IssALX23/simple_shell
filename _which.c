#include "main.h"
/**
 * _which : returns the path of the input command
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
	{
		perror("failed to allocate memory in _which\n");
		return (NULL);
	}
	snprintf(new_cmd, size, "which ");
	if (cmd)
		strcat(new_cmd, cmd);
	fp = popen(new_cmd, "r");
	if (fp == NULL)
	{
		perror("failed to open file\n");
		free(new_cmd);
		return (NULL);
	}
	if (fgets(buffer, sizeof(buffer), fp) != NULL)
	{
		count = strlen(buffer);
		if (buffer[count - 1] == '\n')
			buffer[count - 1] = '\0';
		new_buff = (char *)malloc(strlen(buffer) + 1);
		if (!new_buff)
		{
			perror("failed to allocate memory to new_buff\n");
			free(new_cmd);
			return (NULL);
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
