#include "shell.h"

/**
  * add_var_node - add new new node to a linked list.
  * @head: pointer to head node.
  * @lvar: length off variable.
  * @val: value of vaiable.
  * @lval: length of value.
  *
  * Return:  pointer to the head of the linked list.
  */

var_name *add_var_node(var_name **head, int lvar, char *val, int lval)
{
	var_name *new, *temp;

	new = malloc(sizeof(var_name));
	if (new == NULL)
		return (NULL);
	new->var_len = lvar;
	new->value = val;
	new->value_len = lval;

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
  * free_var_list - free  memory associated with the linked list of variables.
  * @head: pointer to address of head node.
  */

void free_var_list(var_name **head)
{
	var_name *tmp;
	var_name *current;

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
