#include "main.h"
/**
 * check_dir - checks if given path is a directory
 * @str: input string for path
 *
 * Return: 0 when found or 2 when not found
 */
int check_dir(char *str)
{
        const char *path = str;
        struct stat info;
        int result = stat(path, &info);

        if (result == 0 && S_ISDIR(info.st_mode))
                return 0;
        else
                return (2);
}
/**
 * is_numeric - check is string is numeric
 * @str: input strin
 *
 * Return: 0 if not numeric and 1 if it is
 */
int is_numeric(const char *str) {
	int i = 0;

	if (str[i] == '-')
	{
		i++;
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return 0;
		i++;
	}
	return 1;
}
