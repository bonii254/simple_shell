#include "shell.h"

/**
  * cd_dot - change current directory to parent directory.
  * @arg: pointer to shell_struct.
  */

void cd_dot(shell_struct *arg)
{
	char curr_dir[PATH_MAX];
	char *dir_arg, *curr_path_copy, *parent_dir;

	getcwd(curr_dir, sizeof(curr_dir));
	curr_path_copy = _strdup(curr_dir);
	set_env("OLDPWD", curr_path_copy, arg);
	dir_arg = arg->args[1];

	if (_strcmp(".", dir_arg) == 0)
	{
		set_env("PWD", curr_path_copy, arg);
		free(curr_path_copy);
		return;
	}
	if (_strcmp("/", curr_path_copy) == 0)
	{
		free(curr_path_copy);
		return;
	}
	rev_string(curr_path_copy);
	parent_dir = _strtok(curr_path_copy, "/");
	if (parent_dir != NULL)
	{
		rev_string(parent_dir);
		chdir(parent_dir);
		set_env("PWD", parent_dir, arg);
	}
	else
	{
		chdir("/");
		set_env("PWD", "/", arg);
	}
	arg->status = 0;
	free(curr_path_copy);
}

/**
  * cd_home - change from current directory to home directory.
  * @arg: pointer to shell_struct.
  */

void cd_home(shell_struct *arg)
{
	char *p_pwd, *p_home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = _strdup(pwd);
	p_home = _getenv("HOME", arg->_environ);
	if (p_home == NULL)
	{
		set_env("OLDPWD", p_pwd, arg);
		free(p_pwd);
		return;
	}
	if (chdir(p_home) == -1)
	{
		get_error(arg, 2);
		free(p_pwd);
		return;
	}
	set_env("OLDPWD", p_pwd, arg);
	set_env("PWD", p_home, arg);
	free(p_pwd);
	arg->status = 0;
}


/**
  * cd_to - change from one directory to another.
  * @arg: pointer to shell_struct.
  */

void cd_to(shell_struct *arg)
{
	char pwd[PATH_MAX];
	char *dir, *current_pwd, *current_dir;

	getcwd(pwd, sizeof(pwd));
	dir = arg->args[1];
	if (chdir(dir) == -1)
	{
		get_error(arg, 2);
		return;
	}
	current_pwd = _strdup(pwd);
	set_env("PREV_PWD", current_pwd, arg);
	current_dir = _strdup(dir);
	set_env("PWD", current_dir, arg);
	free(current_pwd);
	free(current_dir);

	arg->status = 0;
	chdir(dir);
}

/**
  * cd_previous - change directory to previous directory.
  * @arg: pointer to shell_struct.
  */

void cd_previous(shell_struct *arg)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *current_pwd, *current_oldpwd;

	getcwd(pwd, sizeof(pwd));
	current_pwd = _strdup(pwd);
	p_oldpwd = _getenv("OLDPWD", arg->_environ);
	if (p_oldpwd == NULL)
		current_oldpwd = current_pwd;
	else
		current_oldpwd  = _strdup(p_oldpwd);
	set_env("OLDPWD", current_pwd, arg);
	if (chdir(current_oldpwd) == -1)
		set_env("PWD", current_pwd, arg);
	else
		set_env("PWD", current_oldpwd, arg);
	p_pwd = _getenv("PWD", arg->_environ);
	write(STDOUT_FILENO, p_pwd, _strlen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(current_pwd);
	if (p_oldpwd)
		free(current_oldpwd);

	arg->status = 0;
	chdir(p_pwd);
}

/**
  * cd_shell - handle change directory in shell.
  * @arg: pointer to shell_struct structure.
  *
  * Return: 1 on success else 0.
  */

int cd_shell(shell_struct *arg)
{
	char *dir;
	int home = 0;
	int home2 = 0;
	int doubledash = 0;

	dir = arg->args[1];
	if (dir != NULL)
	{
		home = _strcmp("$HOME", dir);
		home2 = _strcmp("~", dir);
		doubledash = _strcmp("--", dir);
	}
	else if (dir == NULL || !home || !home2 || !doubledash)
	{
		cd_home(arg);
		return (1);
	}
	else if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		cd_dot(arg);
		return (1);
	}
	else if (_strcmp("-", dir) == 0)
	{
		cd_previous(arg);
		return (1);
	}
	else
	{
		cd_to(arg);
		return (1);
	}
	return (0);
}
