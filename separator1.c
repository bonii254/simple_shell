#include "shell.h"

/**
  * char_swap - perform character swap.
  * @input: pointer to input string.
  * @bool: determine direction of character swap.
  *
  * Return: pointer to input stream.
  */

char *char_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}
			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
  * add_node - split the input string into command lines and separators and add
  * them to their respective linked lists.
  * @sep_head: linked list.
  * @cmdline_head: linked list.
  * @input: pointer to input string.
  */

void add_node(arg_seperators **sep_head, cmd_line_sep **cmdline_head,
		char *input)
{
	int i;
	char *line;

	input = char_swap(input, 0);
	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_separators_end(sep_head, input[i]);
		if (input[i] == '|' || input[i] == '&')
		{
			add_separators_end(sep_head, input[i]);
			i++;
		}
	}
	line = _strtok(input, ";|&");
	do {
		line = char_swap(line, 1);
		add_cmdln_end(cmdline_head, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);
}

/**
  * go_next - list_s and list_cmdln pointers to the next relevant node.
  * @separator_list: double pointer to separators list.
  * @command_line_list: double pointer to cmd list.
  * @arg: pointer to struct.
  */

void go_next(arg_seperators **separator_list, cmd_line_sep **command_line_list,
		shell_struct *arg)
{
	int loop_continue;
	arg_seperators *separator_node;
	cmd_line_sep *command_line_node;

	loop_continue = 1;
	separator_node = *separator_list;
	command_line_node = *command_line_list;

	while (separator_node != NULL && loop_continue)
	{
		if (arg->status == 0)
		{
			if (separator_node->sep == '&' || separator_node->sep == ';')
				loop_continue = 0;
			if (separator_node->sep == '|')
			{
				command_line_node = command_line_node->nxt;
				separator_node = separator_node->nxt;
			}
		}
		else
		{
			if (separator_node->sep == '|' || separator_node->sep == ';')
			{
				loop_continue = 0;
			}
			if (separator_node->sep == '&')
			{
				command_line_node = command_line_node->nxt;
				separator_node = separator_node->nxt;
			}
		}
		if (separator_node != NULL && !loop_continue)
			separator_node = separator_node->nxt;
	}
	*separator_list = separator_node;
	*command_line_list = command_line_node;
}

/**
  * split_commands - execute shell commands.
  * @arg: pointer to structure.
  * @input: input string.
  *
  * Return: 0 to exit shell else 1.
  */

int split_commands(shell_struct *arg, char *input)
{
	arg_seperators *head_s, *list_s;
	cmd_line_sep *head_cmdln, *list_cmdln;
	int loop;

	head_s = NULL;
	head_cmdln = NULL;

	add_node(&head_s, &head_cmdln, input);
	list_s = head_s;
	list_cmdln = head_cmdln;

	while (list_cmdln != NULL)
	{
		arg->input = list_cmdln->cmd_line;
		arg->args = split_line(arg->input);
		loop = exec_line(arg);
		free(arg->args);

		if (loop == 0)
			break;
		go_next(&list_s, &list_cmdln, arg);
		if (list_cmdln != NULL)
			list_cmdln = list_cmdln->nxt;
	}
	free_separators_l(&head_s);
	free_cmdln_list(&head_cmdln);

	if (loop == 0)
		return (0);
	return (1);
}
