#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * @information: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *information, char *path)
{
	struct stat st;

	(void)information;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstring: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstring, int start, int stop)
{
	static char buffer[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstring[i] != ':')
			buffer[k++] = pathstring[i];
	buffer[k] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * @information: the info struct
 * @pathstring: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *information, char *pathstring, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstring)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstring[i] || pathstring[i] == ':')
		{
			path = dup_chars(pathstring, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(information, path))
				return (path);
			if (!pathstring[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}
