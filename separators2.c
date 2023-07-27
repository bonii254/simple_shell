#include "shell.h"

/**
  * add_cmdln_end - add node to a linked list.
  * @head: head of a linked list.
  * @cmd_line: pointer to commands.
  *
  * Return: pointer to head node.
  */

cmd_line_sep *add_cmdln_end(cmd_line_sep **head, char *cmd_line)
{
	cmd_line_sep *new, *tmp;

	new = malloc(sizeof(cmd_line_sep));
	if (new == NULL)
		return (NULL);
	new->cmd_line = cmd_line;
	new->nxt = NULL;
	tmp = *head;

	if (tmp == NULL)
	{
		*head = new;
	}
	else
	{
		while (tmp->nxt != NULL)
			tmp = tmp->nxt;
		tmp->nxt = new;
	}
	return (*head);
}

/**
  * free_cmdln_list - free memory allocated for the entire command line
  * linked list.
  * @head: head node.
  */

void free_cmdln_list(cmd_line_sep **head)
{
	cmd_line_sep *tmp;
	cmd_line_sep *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}

/**
  * add_separators_end - adda new separator to the end of the linked list
  * @head: headof the linked list.
  * @separator: store separator found.
  *
  * Return: head pointer.
  */

arg_seperators *add_separators_end(arg_seperators **head, char separator)
{
	arg_seperators *new, *temp;

	new = malloc(sizeof(arg_seperators));
	if (new == NULL)
		return (NULL);
	new->sep = separator;
	new->nxt = NULL;
	temp = *head;
	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->nxt != NULL)
			temp = temp->nxt;
		temp->nxt = new;
	}
	return (*head);
}

/**
  * free_separators_l - free memory allocated for the entire separators
  * linked list.
  * @head: pointer to head node.
  */

void free_separators_l(arg_seperators **head)
{
	arg_seperators *tmp;
	arg_seperators *current;

	if (head != NULL)
	{
		current = *head;
		while ((tmp = current) != NULL)
		{
			current = current->nxt;
			free(tmp);
		}
		*head = NULL;
	}
}
