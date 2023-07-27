#include "shell.h"

/**
  * cmp_env_name -  compares an environment variable name (envn) with a given
  * name (name) up to the first occurrence of the = character.
  * @envn: pointer to environment variable.
  * @name: name of the vaiable.
  *
  * Return: length of the matched part plus one if there is a match.
  * 0 if there is no match
  */

int cmp_env_name(const char *envn, const char *name)
{
	int i = 0;

	while (envn[i] != '\0' && envn[i] == name[i])
		i++;
	if (envn[i] == '=' && name[i] == '\0')
		return (i + 1);
	return (0);
}

/**
  * _getenv - search for an environment variable by its name.
  * @name: name of environment variable.
  * @_environ: array of strings representing the environment variables.
  *
  * Return: pointer to environment variable else NULL.
  */

char *_getenv(const char *name, char **_environ)
{
	char *ptr_env = NULL;
	int i, change = 0;

	for (i = 0; _environ[i]; i++)
	{
		change = cmp_env_name(_environ[i], name);
		if (change)
		{
			ptr_env = _environ[i];
			break;
		}
	}
	return (ptr_env + change);
}


/**
  * prints_env - print the entire environment stored in the _environ array.
  * @arg: pointer to shell_struct structure.
  *
  * Return: 1 on success.
  */

int prints_env(shell_struct *arg)
{
	int i, j;

	for (i = 0; arg->_environ[i]; i++)
	{
		for (j = 0; arg->_environ[i][j]; j++)
			;
		write(STDOUT_FILENO, arg->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	arg->status = 0;
	return (1);
}
