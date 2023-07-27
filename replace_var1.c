#include "shell.h"

/**
  * replace_ip - variable replacement process.
  * @head: a linked list of variables.
  * @input: input string.
  * @new_input: a new string for the replaced input.
  * @new_len: length of the input after replacement .
  *
  * Return: pointer to new_input.
  */

char *replace_ip(var_name **head, char *input, char *new_input, int new_len)
{
	var_name *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < new_len; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->var_len) && !(index->value_len))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->var_len && !(index->value_len))
			{
				for (k = 0; k < index->var_len; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->var_len; k++)
				{
					new_input[i] = index->value[k];
					i++;
				}
				j += (index->var_len);
				i--;
			}
			index = index->nxt;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}
	return (new_input);
}

/**
  * check_envn - check if a typed variable in the input string (in)
  * corresponds to an environment variable.
  * @h: header of linked list.
  * @in: input string.
  * @arg: pointer to shell_struct.
  */

void check_envn(var_name **h, char *in, shell_struct *arg)
{
	int row, chr, j, lval;
	char **envr;

	envr = arg->_environ;
	for (row = 0; envr[row]; row++)
	{
		for (j = 1, chr = 0; envr[row][chr]; chr++)
		{
			if (envr[row][chr] == '=')
			{
				lval = _strlen(envr[row] + chr + 1);
				add_var_node(h, j, envr[row] + chr + 1, lval);
				return;
			}
			if (in[j] == envr[row][chr])
				j++;
			else
				break;
		}
	}
	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}
	add_var_node(h, j, NULL, 0);
}


/**
  * var_check - check input string (in) for special variables ($$ and $?)
  * @h: pointer to head of linked list
  * @in: input string.
  * @st: last status of the shell.
  * @arg: pointer to structure.
  *
  * Return:  total number of characters checked.
  */

int var_check(var_name **h, char *in, char *st, shell_struct *arg)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(arg->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_node(h, 2, arg->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else
				check_envn(h, in + i, arg);
		}
	}
	return (i);
}


/**
  * replace_var - entry point for the variable replacement process
  * in the custom shell program.
  * @input: original input string.
  * @arg:  pointer to sreucture.
  *
  * Return: new input string
  */

char *replace_var(char *input, shell_struct *arg)
{
	var_name *head, *index;
	char *status, *new_input;
	int old_len, new_len;

	status = _itoa(arg->status);
	head = NULL;
	old_len = var_check(&head, input, status, arg);
	if (head == NULL)
	{
		free(status);
		return (input);
	}
	index = head;
	new_len = 0;
	while (index != NULL)
	{
		new_len += (index->value_len - index->var_len);
		index = index->nxt;
	}
	new_len += old_len;
	new_input = (char *) malloc(sizeof(char) * (new_len + 1));
	if (!new_input)
		return (NULL);

	new_input[new_len] = '\0';
	new_input = replace_ip(&head, input, new_input, new_len);
	free(input);
	free(status);
	free_var_list(&head);
	return (new_input);
}
