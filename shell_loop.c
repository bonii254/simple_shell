#include "shell.h"

/**
  * shell_prompt - shell loop.
  * @arg: pointer to shell_struct struct.
  */

void shell_prompt(shell_struct *arg)
{
	int prompt = 1;
	int in_eof;
	char *cmd_input;

	while (prompt)
	{
		write(STDOUT_FILENO, "$ ", 2);
		cmd_input = _readline(&in_eof);

		if (in_eof != -1)
		{
			cmd_input = remove_comment(cmd_input);
			if (!cmd_input || *cmd_input == '\0')
			{
				free(cmd_input);
				continue;
			}
			if (has_syntax_error(arg, cmd_input) == 1)
			{
				arg->status = 2;
				free(cmd_input);
				continue;
			}
			cmd_input = replace_var(cmd_input, arg);
			prompt = split_commands(arg, cmd_input);
			arg->counter += 1;
			free(cmd_input);
		}
		else
		{
			prompt = 0;
			free(cmd_input);
		}
	}
}

/**
  * remove_comment - remove comment from an input string.
  * @input: input string.
  *
  * Return: pointer to modified input string.
  */

char *remove_comment(char *input)
{
	int i = 0, limit = 0;

	while (input[i])
	{
		if (input[i] == '#')
		{
			if (i == 0)
			{
				free(input);
				return (NULL);
			}
			if (input[i - 1] == ' ' || input[i - 1] == '\t' || input[i - 1] == ';')
				limit = i;
		}
		i++;
	}
	if (limit != 0)
	{
		input =  _realloc(input, i, limit + 1);
		input[limit] = '\0';
	}
	return (input);
}
