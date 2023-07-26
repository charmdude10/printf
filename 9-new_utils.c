#include "main.h"

/**
 * is_printable - Determines whether a char is printable
 * @c: Char for evaluation.
 *
 * Return: 1 for printable c, 0 for non-printable
 */
int is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - Add ASCII in hex code to buffer
 * @buffer: Array of chars.
 * @i: Index where appending begins.
 * @ascii_code: ASCII CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char convert_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = convert_to[ascii_code / 16];
	buffer[i] = convert_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Checks whether a char is numeric
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a numeric, 0 non-numeric
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Converts a number to the desired size
 * @num: Number to be converted.
 * @size: Numeric value representing the conversion target.
 *
 * Return: Converted result of num
 */
long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Converts a number to the desired size
 * @num: Number to be converted
 * @size: Numeric value representing the conversion target.
 *
 * Return: Converted result of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}
