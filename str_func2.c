#include "shell.h"

/**
* *_strchr - locate the first occurrence of a character in a string.
* @s: a pointer to the null-terminated string in which
* the search is performed.
* @c: character to be located.
*
* Return: If the character is found,
* a pointer to the first occurrence of the character is returned. else
* NULL is returned.
*/

char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	return (NULL);
}

/**
* _strspn - calculates the length (in bytes) of the initial
* segment of s which consists entirely of bytes in accept.
* @s: initial segments.
* @accept: accepted bytes.
*
* Return: length of the segment.
*/

size_t _strspn(const char *s, const char *accept)
{
	int i, j, state;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		state = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				state = 0;
				break;
			}
		}
		if (state == 1)
			break;
	}
	return (i);
}

/**
* _isNumeric - check is a string is numeric.
* @s: string pointer.
*
* Return: 1 if string is a number, else 0.
*/

int _isNumeric(const char *s)
{
	unsigned int d;

	for (d = 0; s[d] != '\0'; d++)
	{
		if (s[d] < 48 || s[d] > 57)
			return (0);
	}
	return (1);
}

/**
* rev_string - reverses a string.
* @s: pointer to string to reverse.
*/

void rev_string(char *s)
{
	int count = 0, i, j;
	char *str, temp;

	while (count >= 0)
	{
		if (s[count] == '\0')
			break;
		count++;
	}
	str = s;

	for (i = 0; i < (count - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(str + j);
			*(str + j) = *(str + (j - 1));
			*(str + (j - 1)) = temp;
		}
	}
}
