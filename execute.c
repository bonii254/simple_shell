#include "shell.h"

/**
  * is_current_dir -  check character at a specific index in a given string
  * path represents a current directory indicator.
  * @path:  a pointer to a character array
  * @i: pointer to an integer
  *
  * Return: 0 on success.
  */

int is_current_dir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);
	while (path[*i] != ':' && path[*i])
		*i += 1;
	if (path[*i])
		*i += 1;
	return (0);
}


/**
  * _locate - locate the full path of an executable command
  * @cmd: pointer to commands.
  * @_environ: pointer to environment.
  *
  * Return: return cmd or NULL.
  */

char *_locate(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_dir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}


/**
  * is_executable - check if the given input command is an executable file.
  * @arg: pointer to structure.
  *
  * Return: 0 if file exit and executable.
  */

int is_executable(shell_struct *arg)
{
	struct stat st;
	int i;
	char *input;

	input = arg->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);
	if (stat(input + i, &st) == 0)
		return (i);
	get_error(arg, 127);
	return (-1);
}


/**
  * cmd_check_error - check if a command is an executable file.
  * @dir: full path of the command.
  * @arg: pointer to structure.
  *
  * Return: 0 on success.
  */

int cmd_check_error(char *dir, shell_struct *arg)
{
	if (dir == NULL)
	{
		get_error(arg, 127);
		return (1);
	}
	if (_strcmp(arg->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(arg, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(arg->args[0], X_OK) == -1)
		{
			get_error(arg, 126);
			return (1);
		}
	}
	return (0);
}


/**
  * exec_cmd -  responsible for executing a command specified in the arg.
  * @arg:  pointer to a shell_struct.
  *
  * Return: 1 on success.
  */

int exec_cmd(shell_struct *arg)
{
	pid_t pd, wpd;
	int state = 0;
	int exec;
	char *dir;

	(void) wpd;
	exec = is_executable(arg);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = _locate(arg->args[0], arg->_environ);
		if (cmd_check_error(dir, arg) == 1)
			return (1);
	}
	pd = fork();
	if (pd == 0)
	{
		if (exec == 0)
			dir = _locate(arg->args[0], arg->_environ);
		else
			dir = arg->args[0];
		execve(dir + exec, arg->args, arg->_environ);
	}
	else if (pd < 0)
	{
		perror(arg->av[0]);
		return (1);
	}
	else
	{
		do {
			wpd = waitpid(pd, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	arg->status = state / 256;
	return (1);
}
