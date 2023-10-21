#include "shell.h"

/**
 * interactive - this perhaps returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delime- this function checks if character is a delimeter
 * @c: the char to check it
 * @delime: the delimeter is a string
 * Return: 1 if true, 0 if false
 */
int is_delime(char c, char *delime)
{
	while (*delime)
		if (*delime++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character of a func
 *@c: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integerS
 *@s: the string to be converted t
 *Return: 0 if no numbers in string, converted number otherwises
 */

int _atoi(char *s)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
