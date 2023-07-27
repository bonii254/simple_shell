#include "shell.h"

/**
  * exit_shell - initiate exiting of the shell.
  * @arg: pointer to shell_struct structure.
  *
  * Return: 0 on success.
  */

int exit_shell(shell_struct *arg)
{
	unsigned int exit_code;
	int is_numeric;
	int str_len;
	int is_exit_num;

	if (arg->args[1] != NULL)
	{
		exit_code = _atoi(arg->args[1]);
		is_numeric = _isNumeric(arg->args[1]);
		str_len = _strlen(arg->args[1]);
		is_exit_num = exit_code > (unsigned int)INT_MAX;
		if (!is_numeric || str_len > 10 || is_exit_num)
		{
			get_error(arg, 2);
			arg->status = 2;
			return (1);
		}
		arg->status = (exit_code % 256);
	}
	return (0);
}
