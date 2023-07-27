#include "shell.h"

/**
* _strtok - breaks a string into a sequence of zero or more nonempty tokens.
* @str:  A pointer to the string to be tokenized.
* @delim: A pointer to a constant string containing the delimiter characters.
*
* Return: pointer to the token (substring) found in str.
* NULL if no more tokens are available.
*/

char *_strtok(char str[], const char *delim)
{
	static char *splitted_str, *str_end;
	char *str_strt;
	unsigned int j, bool;

	if (str != NULL)
	{
		if (cmp_chars(str, delim))
			return (NULL);
		splitted_str = str;
		j = _strlen(str);
		str_end = &str[j];
	}
	str_strt = splitted_str;
	if (str_strt == str_end)
		return (NULL);

	for (bool = 0; *splitted_str; splitted_str++)
	{
		if (splitted_str != str_strt)
			if (*splitted_str && *(splitted_str - 1) == '\0')
				break;
		for (j = 0; delim[j]; j++)
		{
			if (*splitted_str == delim[j])
			{
				*splitted_str = '\0';
				if (splitted_str == str_strt)
					str_strt++;
				break;
			}
		}
		if (bool == 0 && *splitted_str)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (str_strt);
}

/**
  * split_line - split string based on delimeters.
  * @input: getline string.
  *
  * Return: pointer to array of tokens or NULL.
  */

char **split_line(char *input)
{
	char **tokens;
	char *token;
	size_t byte_size;
	size_t j = 1;

	byte_size = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * TOK_BUFSIZE);
	if (!tokens)
	{
		write(STDERR_FILENO, ": Memory allocation error\n", 25);
		exit(EXIT_FAILURE);
	}
	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;
	while (token != NULL)
	{
		if (j == byte_size)
		{
			byte_size += TOK_BUFSIZE;
			tokens = _reallocdptr(tokens, j, sizeof(char *) * TOK_BUFSIZE);
			if (!tokens)
			{
				write(STDERR_FILENO, ": Memory allocation error\n", 25);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[j] = token;
		j++;
	}
	return (tokens);
}


/**
  * cmp_chars -  checks if all characters in the str are present in the delim.
  * @str: an array of characters.
  * @delim: character pointer containing delimiter characters.
  *
  * Return: 1 on success else 0.
  */

int cmp_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}
