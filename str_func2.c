#include "shell.h"

/**
* *strchr - locate the first occurrence of a character in a string.
* @s: a pointer to the null-terminated string in which
* the search is performed.
* @c: character to be located.
*
* Return: If the character is found,
* a pointer to the first occurrence of the character is returned. else
* NULL is returned.
*/

char *strchr(const char *s, int c)
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
	size_t initial_len = 0, len1, len2, i, j, k;

	len1 = _strlen(s);
	len2 = _strlen(accept);

	for (i = 0; i < len1; i++)
	{
		k = 0;
		for (j = 0; j < len2; j++)
		{
			if (accept[j] == s[i])
			{
				k = 1;
				break;
			}
		}
		if (k == 0)
			break;
		initial_len++;
	}
	return (initial_len);
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
	char rev = s[0];
	int counter = 0;
	int i;

	while (s[counter] != '\0')
		counter++;
	for (i = 0; i < counter; i++)
	{
		counter--;
		rev = s[i];
		s[i] = s[counter];
		s[counter] = rev;
	}
}
