#include "shell.h"

/**
  * build_cd_error - construct the error message related to the cd command.
  * @arg: pointer to shell_struct
  * @msg: error message.
  * @str_count: a string representation of the command counter
  * @err: pointer to a string that provide more info about a error.
  *
  * Return: constructed error message in the error string.
  */

char *build_cd_error(shell_struct *arg, char *msg, char *str_count, char *err)
{
	char *wrng_val;

	_strcpy(err,  arg->args[0]);
	_strcat(err, ": ");
	_strcat(err, str_count);
	_strcat(err, ": ");
	_strcat(err, arg->args[0]);
	_strcat(err, msg);

	if (arg->args[1][0] == '-')
	{
		wrng_val = malloc(3);
		wrng_val[0] = '-';
		wrng_val[1] = arg->args[1][1];
		wrng_val[2] = '\0';
		_strcat(err, wrng_val);
		free(wrng_val);
	}
	else
	{
		_strcat(err, arg->args[1]);
	}
	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
  * get_cd_error - create cd error meassage.
  * @arg: pointer to struct,
  *
  * Return: pointer to constructed error message.
  */

char *get_cd_error(shell_struct *arg)
{
	int total_len, id_len;
	char *err_msg, *str, *err, *msg;

	str = _itoa(arg->counter);
	if (arg->args[1][0] == '-')
	{
		msg = ":wrong option ";
		id_len = 2;
	}
	else
	{
		msg = ": no directory ";
		id_len = _strlen(arg->args[1]);
	}
	total_len = _strlen(arg->av[0]) + _strlen(arg->args[0]);
	total_len += _strlen(str) + _strlen(msg) + id_len + 5;

	err_msg = (char *) malloc(sizeof(char) * (total_len + 1));
	if (err_msg == 0)
	{
		free(str);
		return (NULL);
	}
	err = build_cd_error(arg, msg, err_msg, str);
	free(str);
	return (err);
}

/**
  * not_found_error - generate error message for command not found error.
  * @arg: pointer to shell_struct structure.
  *
  * Return: error message or NULL ON FAIL.
  */

char *not_found_error(shell_struct *arg)
{
	int len;
	char *str, *err;

	str = _itoa(arg->counter);
	len = _strlen(arg->av[0]) + _strlen(str);
	len += _strlen(arg->args[0]) + 16;

	err = (char *) malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(err);
		free(str);
		return (NULL);
	}
	_strcpy(err, arg->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, arg->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(str);
	return (err);
}

/**
  * exit_shell_error - generate exit shell related error message.
  * @arg: pointer to structure.
  *
  * Return: error message or NULL on fail.
  */

char *exit_shell_error(shell_struct *arg)
{
	int len;
	char *str, *err;

	str = _itoa(arg->counter);
	len = _strlen(arg->av[0]) + _strlen(str);
	len += _strlen(arg->args[0]) + _strlen(arg->args[1]) + 23;

	err = (char *) malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(str);
		return (NULL);
	}
	_strcpy(err, arg->av[0]);
	_strcat(err, ": ");
	_strcat(err, str);
	_strcat(err, ": ");
	_strcat(err, arg->args[0]);
	_strcat(err, ":wrong number: ");
	_strcat(err, arg->args[1]);
	_strcat(err, "\n\0");
	free(str);
	return (err);
}


/**
  * cmd_nt_found - construct error message when command is not found.
  * @arg: pointer to shell_struct structure.
  *
  * Return: pointer to error message.
  */

char *cmd_nt_found(shell_struct *arg)
{
	int i;
	char *error;
	char *ver_str;

	ver_str = _itoa(arg->counter);
	i = _strlen(arg->av[0]) + _strlen(ver_str);
	i += _strlen(arg->args[0]) + 16;
	error = malloc(sizeof(char) * (i + 1));
	if (error == 0)
	{
		free(error);
		free(ver_str);
		return (NULL);
	}
	_strcpy(error, arg->av[0]);
	_strcat(error, ": ");
	_strcat(error, ver_str);
	_strcat(error, ": ");
	_strcat(error, arg->args[0]);
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(ver_str);
	return (error);
}
