#include "shell.h"

/**
  * get_error - generate and handle eror messages based on error value
  * @arg: struct variable.
  * @error_value: holds the error number.
  *
  * Return: error value.
  */

int get_error(shell_struct *arg, int error_value)
{
	char *error;

	switch (error_value)
	{
		case -1:
			error = env_var_error(arg);
			break;
		case 126:
			error = path_126_error(arg);
			break;
		case 127:
			error = not_found_error(arg);
			break;
		case 2:
			if (_strcmp("exit", arg->args[0]) == 0)
				error = exit_shell_error(arg);
			else if (_strcmp("cd", arg->args[0]) == 0)
				error = get_cd_error(arg);
			break;
	}
	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}
	arg->status = error_value;
	return (error_value);
}
/**
  * path_126_error - handle error message based on path.
  * @arg: struct_shell variable.
  *
  * Return: error.
  */

char *path_126_error(shell_struct *arg)
{
	int len;
	char *string, *error;

	string =  _itoa(arg->counter);
	len =  _strlen(arg->av[0] + _strlen(string));
	len += _strlen(arg->args[0]) + 24;

	error = (char *) malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(string);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, string);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, ":Access denied\n");
	_strcat(error, "\0");
	free(string);
	return (error);
}

/**
  * env_var_error - generate an error message when there is an issue adding or
  * removing from the environment variables.
  * @arg: pointer to a shell structure.
  *
  * Return: a pointer to a character string.
  */

char *env_var_error(shell_struct *arg)
{
	int len;
	char *error, *msg, *str;

	str = _itoa(arg->counter);
	msg = "Can't  add/remove from env\n";
	len = _strlen(arg->av[0]) + _strlen(str);
	len = _strlen(arg->args[0]) + _strlen(msg) + 4;
	error = (char *) malloc(sizeof(char) * (len + 1));
	if (error == 0)
	{
		free(error);
		free(str);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, str);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(str);
	return (error);
}
