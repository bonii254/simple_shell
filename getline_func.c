#include "shell.h"

/**
  * _getline - reads  an  entire  line  from  stream,
  * storing  the address of the buffer containing the text into *lineptr.
  * @lineptr: double pointer that will store address of the allocated buffer
  * @n: pointer to a variable that will store the size of the allocated buffer
  * @stream: file from which to read input.
  *
  * Return: number of characters read.
  */

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	ssize_t input_len = 0, chars_read = 0;
	char *buff = NULL;
	char c = 'b';

	fflush(stream);
	buff = (char *) malloc(sizeof(char) * BUFSIZE);
	if (!buff)
		return (-1);
	while (c != '\n')
	{
		i = read(STDIN_FILENO, &c, 1);
		if (i == -1 || (i == 0 && input_len == 0))
		{
			free(buff);
			return (-1);
		}
		if (i == 0 && input_len != 0)
		{
			input_len++;
			break;
		}
		if (input_len >= BUFSIZE)
		{
			buff = _realloc(buff, input_len, input_len + 1);
			if (!buff)
			{
				free(buff);
				return (-1);
			}
		}
		buff[input_len] = c;
		input_len++;
	}
	buff[input_len] = '\0';
	_checkline(lineptr, n, buff, input_len);
	chars_read = input_len;
	if (i != 0)
		input_len = 0;
	return (chars_read);
}

/**
  * _checkline - handle processing of the line read by the _getline function.
  * @lineptr: double pointer to allocated buffer.
  * @n: a pointer to a variable that stores the size of the allocated buffer.
  * @buff: pointer to buffer containing the line.
  * @i: length of the line.
  */

void _checkline(char **lineptr, size_t *n, char *buff, size_t i)
{
	if (!(*lineptr))
	{
		if (i > BUFSIZE)
			*n = i;
		else
			*n = BUFSIZE;
		*lineptr = buff;
	}
	else if (*n < i)
	{
		if (i > BUFSIZE)
			*n = i;
		else
			*n = BUFSIZE;
		*lineptr = buff;
	}
	else
	{
		_strcpy(*lineptr, buff);
		free(buff);
	}
}

/**
  * _readline - read user input checking checking end of file
  * @endfile: indicate end of file.
  *
  * Return: user input.
  */

char *_readline(int *endfile)
{
	char *input = NULL;
	size_t buf_size = 0;

	*endfile = _getline(&input, &buf_size, stdin);
	return (input);
}
