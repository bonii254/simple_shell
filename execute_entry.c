#include "shell.h"

/**
  * exec_line - execute single line of input provided to the shell.
  * @arg: pointer to shell_struct.
  *
  * Return: 1 if no error.
  */

int exec_line(shell_struct *arg)
{
	int (*builtin)(shell_struct *arg);

	if (arg->args[0] == NULL)
		return (1);
	builtin = _builtin(arg->args[0]);
	if (builtin != NULL)
		return (builtin(arg));
	return (exec_cmd(arg));
}
