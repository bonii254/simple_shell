#include "shell.h"

/**
  * copies_info - create new string.
  * @name: name of an environment variable..
  * @value: value of an environment variable.
  *
  * Return: pointer to the newly created string
  */

char *copies_info(const char *name, const char *value)
{
	char *new;
	int len, len_name, len_value;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;

	new = (char *) malloc(sizeof(char) * len);
	if (!new)
		return (NULL);
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
  * set_env - set an environment variable .
  * @name: name of an environment variable..
  * @value: value of an environment variable.
  * @arg: pointer to structure variable.
  */

void set_env(char *name, char *value, shell_struct *arg)
{
	int i;
	char *name_env, *var_name;

	for (i = 0; arg->_environ[i]; i++)
	{
		name_env = _strtok(var_name, "=");
		var_name = _strdup(arg->_environ[i]);
		if (_strcmp(name_env, name) == 0)
		{
			free(arg->_environ[i]);
			arg->_environ[i] = copies_info(name_env, value);
			free(var_name);
			return;
		}
		arg->_environ = _reallocdptr(arg->_environ, i, sizeof(char *) * (i + 2));
		arg->_environ[i] = copies_info(name_env, value);
		arg->_environ[i + 1] = NULL;
	}
}

/**
  * _setenv - wrapper function that sets an environment variable
  * using the set_env function.
  * @arg: pointer to structure.
  *
  * Return: 1 on success.
  */

int _setenv(shell_struct *arg)
{
	if (arg->args[1] == NULL || arg->args[2] == NULL)
	{
		get_error(arg, -1);
		return (1);
	}
	set_env(arg->args[1], arg->args[2], arg);
	return (1);
}

/**
  * _unsetenv - remove an environment variable from the _environ array.
  * @arg: pointer to shell_struct
  *
  * Return: 1 on success.
  */

int _unsetenv(shell_struct *arg)
{
	char **new_environ;
	char *env_name, *env_var;
	int l, m, n;

	if (arg->args[1] == NULL)
	{
		get_error(arg, -1);
		return (1);
	}
	n = -1;
	for (l = 0; arg->_environ[l]; l++)
	{
		env_var = _strdup(arg->_environ[l]);
		env_name = _strtok(env_var, "=");
		if (_strcmp(env_name, arg->args[1]) == 0)
			n = l;
		free(env_var);
	}
	if (n == -1)
	{
		get_error(arg, -1);
		return (1);
	}
	new_environ = (char **) malloc(sizeof(char *) * (l));
	if (!new_environ)
		return (0);
	for (l = m = 0; arg->_environ[l]; l++)
	{
		if (l != m)
		{
			new_environ[m] = arg->_environ[l];
			m++;
		}
	}
	new_environ[m] = NULL;
	free(arg->_environ[n]);
	free(arg->_environ);
	arg->_environ = new_environ;
	return (1);
}
