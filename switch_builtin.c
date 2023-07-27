#include "shell.h"

/**
* _builtin - built in commands.
* @cmd: command input.
*
* Return: pointer to builtin
*/

int (*_builtin(char *cmd))(shell_struct *)
{
	int j = 0;

	builtin_t builtin[] = {
		{"env", prints_env },
		{ "cd", cd_shell },
		{ "unsetenv", _unsetenv },
		{ "setenv", _setenv },
		{ "exit", exit_shell },
		{ NULL, NULL }
	};
	while (builtin[j].name)
	{
		if (_strcmp(builtin[j].name, cmd) == 0)
			break;
		j++;
	}
	return (builtin[j].func_ptr);
}

/**
* execute_arg - execute input line of a shell.
* @arg: pointer to shell_struct containing shell info.
*
* Return: builtin or execute_cmd.
*/

int execute_arg(shell_struct *arg)
{
	int (*builtin)(shell_struct *arg);

	if (arg->args[0] == NULL)
		return (1);
	builtin = _builtin(arg->args[0]);
	if (builtin != NULL)
		return (builtin(arg));
	return (exec_cmd(arg));
}
