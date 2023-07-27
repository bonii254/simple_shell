#include "shell.h"

/**
  * get_len - get the length of an integer.
  * @num: input.
  *
  * Return: length of an integer.
  */

int get_len(int num)
{
	int length = 0;

	if (num == 0)
	{
		return (1);
	}
	else if (num < 0)
	{
		length++;
		num = -num;
	}

	while (num > 0)
	{
		length++;
		num /= 10;
	}

	return (length);
}

/**
  * _itoa - convert integer to string.
  * @num: input integer.
  *
  * Return: pointer to string.
  */

char *_itoa(int num)
{
	int isNegative = 0;
	char *buff;
	int len = get_len(num);

	buff = malloc(sizeof(char) * (len + 1));
	if (!buff)
		return (NULL);
	if (num < 0)
		isNegative = 1;
	buff[len] = '\0';
	len--;
	do {
		buff[len] = (num % 10) + '0';
		num /= 10;
		len--;
	}
	while (num > 0)
		;
	if (isNegative == 1)
		buff[len] = '-';
	return (buff);
}

/**
  * _atoi - convert string to int.
  * @str: input string.
  *
  * Return: integer.
  */

int _atoi(char *str)
{
	size_t index = 0, count = 0, result = 0, sign = 1, mult = 1, i;

	while (str[index] != '\0')
	{
		if (count > 0 && (str[index] < '0' || str[index] > '9'))
		break;
		if (str[index] == '-')
		sign = -sign;
		if ((str[index] >= '0') && (str[index] <= '9'))
		{
			if (count > 0)
			mult *= 10;
			count++;
		}
		index++;
	}
	for (i = index - count; i < index; i++)
	{
		result = result + ((*(str + i) - 48) * mult);
		mult /= 10;
	}
	return (result * sign);
}
