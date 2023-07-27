#include "shell.h"

/**
  * check_first_char - check first character of a string.
  * @input: input string.
  * @ind: store the index of the first non-whitespace character
  * found in the input.
  *
  * Return: -1 for error condition or 0 if no error.
  */

int check_first_char(char *input, int *ind)
{
	for (*ind = 0; input[*ind]; *ind += 1)
	{
		if (input[*ind] == ' ' || input[*ind] == '\t')
			continue;
		if (input[*ind] == ';' || input[*ind] == '|' || input[*ind] == '&')
			return (-1);
		break;
	}
	return (0);
}

/**
  * check_dup_char - count consecutive duplicated characters
  * @input: pointer to character array.
  * @ind: current index in the stream.
  *
  * Return: number of consecutive duplicated characters.
  */

int check_dup_char(char *input, int ind)
{
	if (*(input - 1) == *input)
		return (check_dup_char(input - 1, ind + 1));
	return (ind);
}

/**
  * check_syntax_err - check syntax errors in the input string.
  * @input: pointer to input stream.
  * @ind: current index.
  * @last: last character before current character.
  *
  * Return: index of first syntax erro, 0 if non.
  */

int check_syntax_err(char *input, int ind, char last)
{
	int count = 0;

	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (check_syntax_err(input + 1, ind + 1, last));
	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (ind);
	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (ind);
		if (last == '|')
		{
			count = check_dup_char(input, 0);
			if (count == 0 || count > 1)
				return (ind);
		}
	}
	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (ind);
		if (last == '&')
		{
			count = check_dup_char(input, 0);
			if (count == 0 || count > 1)
				return (ind);
		}

	}
	return (check_syntax_err(input + 1, ind + 1, *input));
}

/**
  * _perror - print error message to standard error file no.
  * @arg: pointer to structure.
  * @input: pointer to input stream.
  * @ind: index value.
  * @bool: boolen to control message error.
  */

void _perror(shell_struct *arg, char *input, int ind, int bool)
{
	char *txt, *txt2, *txt3, *err, *counter;
	int len;

	if (input[ind] == ';')
	{
		if (bool == 0)
			txt = (input[ind + 1] == ';' ? ";;" : ";");
		else
			txt = (input[ind - 1] == ';' ? ";;" : ";");
	}
	if (input[ind] == '|')
		txt = (input[ind + 1] == '|' ? "||" : "|");
	if (input[ind] == '&')
		txt = (input[ind + 1] == '&' ? "&&" : "&");
	txt2 = " Syntax errror \"";
	txt3 = "\" unexpected input\n";
	counter = _itoa(arg->counter);
	len = _strlen(arg->av[0]) + _strlen(counter);
	len += _strlen(txt) + _strlen(txt2) + _strlen(txt3) + 2;

	err = (char *) malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(counter);
		return;
	}
	_strcpy(err, arg->av[0]);
	_strcat(err, ": ");
	_strcat(err, counter);
	_strcat(err, txt2);
	_strcat(err, txt);
	_strcat(err, txt3);
	_strcat(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(counter);
}

/**
  * has_syntax_error - entry point to detection an handling of errors.
  * @arg: pointer to shell_struct structure.
  * @input: pointer to input stream.
  *
  * Return: 0 if no error. 1 else.
  */

int has_syntax_error(shell_struct *arg, char *input)
{
	int start = 0, char1 = 0, ind = 0;

	char1 = check_first_char(input, &start);
	if (char1 == -1)
	{
		_perror(arg, input, start, 0);
		return (1);
	}
	ind = check_syntax_err(input + start, 0, *(input + start));
	if (ind != 0)
	{
		_perror(arg, input, start + ind, 1);
		return (1);
	}
	return (0);
}
