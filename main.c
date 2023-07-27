#include "shell.h"

/**
* main - entry point.
* @ac: number of arguements passed.
* @av: pointer to array of arguement.
*
* Return: 0 on success.
*/

int main(int ac __attribute__((unused)), char **av)
{
	shell_struct arg;

	signal(SIGINT, sigint_handler);
	set_shell_struct(&arg, av);
	shell_prompt(&arg);
	free_shell_struct(&arg);

	if (arg.status < 0)
		return (255);
	return (arg.status);
}

/**
  * sigint_handler - implement the Ctrl+C exit signal handling
  * @sig: represents the signal number that is passed to the signal handler.
  */

void sigint_handler(int sig  __attribute__((unused)))
{
	write(STDOUT_FILENO, "\nCtrl+C received. Exiting the shell.\n", 37);
}

/**
* free_shell_struct - free shell struct.
* @arg: vvariable of shell_struct struct.
*/

void free_shell_struct(shell_struct *arg)
{
	unsigned int i = 1;

	while (arg->_environ[i])
	{
		free(arg->_environ[i]);
		i++;
	}
	free(arg->_environ);
	free(arg->pid);
}

/**
* set_shell_struct - initiate member of shell_struct.
* @arg: shell_struct variable.
* @av: input variable.
*/

void set_shell_struct(shell_struct *arg, char **av)
{
	unsigned int j;

	arg->av = av;
	arg->input = NULL;
	arg->args = NULL;
	arg->status = 0;
	arg->counter = 1;

	for (j = 0; environ[j]; j++)
		;
	arg->_environ = malloc(sizeof(char *) * (j + 1));
	for (j = 0; environ[j]; j++)
		arg->_environ[j] = _strdup(environ[j]);
	arg->_environ[j] = NULL;
	arg->pid = _itoa(getpid());
	}
