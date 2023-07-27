#include "shell.h"

/**
* _strlen - finds the length of a string.
* @s: string input.
*
* Return: len of the string on success.
*/

int _strlen(const char *s)
{
	int len = 0;

	if (!s)
		return (len);
	for (len = 0; s[len] != '\0'; len++)
		;
	return (len);
}

/**
* _strcpy - copy src to dest including null terminator.
* @dest: pointer to destination string
* @src: pointer to source string
*
* Return: pointer to destination.
*/

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

/**
  * _strcat - Concantenates two strings.
  * @dest: pointer to destination string.
  * @src: pointer to source string.
  *
  * Return: pointer to destination string.
  */

char *_strcat(char *dest, const char *src)
{
	size_t i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;
	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
* _strcmp - compares str1 with str2.
* @str1: pointer to first string.
* @str2: pointer to second string.
*
* Return: 0 if equal.
* positive value if str1 > str2
* negative value if str1 < str2
*/

int _strcmp(char *str1, char *str2)
{
	int i;

	for (i = 0; str1[i] == str2[i] && str1[i]; i++)
		;
	if (str1[i] > str2[i])
		return (1);
	if (str1[i] < str2[i])
		return (-1);
	return (0);
}

/**
* _strdup - duplicates a string.
* @s: pointer to the string to duplicate.
*
* Return: pointer to string duplicate.
*/

char *_strdup(const char *s)
{
	size_t len;
	char *dup;

	len = _strlen(s);
	dup = malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	mem_copy(dup, s, len + 1);
	return (dup);
}
