#include "main.h"

/************************* WRITE HANDLE *************************/
/**
 * handle_write_char - Prints a string
 * @c: char types.
 * @buffer: Buffer array for handling print
 * @flags:  Calculates active flags.
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int handle_write_char(char c, char buffer[],
	int flags, int width, int precision, int size)
{ /* char is stored at left and padding at buffer's right */
	int a = 0;
	char padding = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padding = '0';

	buffer[a++] = c;
	buffer[a] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (a = 0; a < width - 1; a++)
			buffer[BUFF_SIZE - a - 2] = padding;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - a - 1], width - 1));
		else
			return (write(1, &buffer[BUFF_SIZE - a - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/************************* WRITE NUMBER *************************/
/**
 * write_number - Prints a string
 * @is_negative: Lists of arguments
 * @ind: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int ind, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padding = ' ', added_c = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';
	if (is_negative)
		added_c = '-';
	else if (flags & F_PLUS)
		added_c = '+';
	else if (flags & F_SPACE)
		added_c = ' ';

	return (write_num(ind, buffer, flags, width, precision,
		length, padding, added_c));
}

/**
 * write_num - Write a number using a buffer
 * @ind: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Padding char
 * @added_c: Added char
 *
 * Return: Number of printed chars.
 */
int write_num(int ind, char buffer[],
	int flags, int width, int prec,
	int length, char padding, char added_c)
{
	int a, padding_up = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0); /* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padding = ' '; /* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padding = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (added_c != 0)
		length++;
	if (width > length)
	{
		for (a = 1; a < width - length + 1; a++)
			buffer[a] = padding;
		buffer[a] = '\0';
		if (flags & F_MINUS && padding == ' ')/* added char to left of buffer */
		{
			if (added_c)
				buffer[--ind] = added_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], a - 1));
		}
		else if (!(flags & F_MINUS) && padding == ' ')/* added char left of buffer */
		{
			if (added_c)
				buffer[--ind] = added_c;
			return (write(1, &buffer[1], a - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')/* added char left of paddin */
		{
			if (added_c)
				buffer[--padding_up] = added_c;
			return (write(1, &buffer[padding_up], a - padding_up) +
				write(1, &buffer[ind], length - (1 - padding_up)));
		}
	}
	if (added_c)
		buffer[--ind] = added_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @ind: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int ind,
	char buffer[],
	int flags, int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position a */
	int length = BUFF_SIZE - ind - 1, a = 0;
	char padding = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0); /* printf(".0d", 0)  no char is printed */

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padding = '0';

	if (width > length)
	{
		for (a = 0; a < width - length; a++)
			buffer[a] = padding;

		buffer[a] = '\0';

		if (flags & F_MINUS) /* Asign added char to left of buffer [buffer>padding]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], a));
		}
		else /* Asign added char to left of padding [padding>buffer]*/
		{
			return (write(1, &buffer[0], a) + write(1, &buffer[ind], length));
		}
	}

	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @ind: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Width specifier
 * @flags: Flags specifier
 * @padding: Char representing the padding
 * @added_c: Char representing added char
 * @padding_up: Index at which padding should begin
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int ind, int length,
	int width, int flags, char padding, char added_c, int padding_up)
{
	int a;

	if (width > length)
	{
		for (a = 3; a < width - length + 3; a++)
			buffer[a] = padding;
		buffer[a] = '\0';
		if (flags & F_MINUS && padding == ' ')/* added char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (added_c)
				buffer[--ind] = added_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], a - 3));
		}
		else if (!(flags & F_MINUS) && padding == ' ')/* added char left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (added_c)
				buffer[--ind] = added_c;
			return (write(1, &buffer[3], a - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padding == '0')/* added char left of paddin */
		{
			if (added_c)
				buffer[--padding_up] = added_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padding_up], a - padding_up) +
				write(1, &buffer[ind], length - (1 - padding_up) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (added_c)
		buffer[--ind] = added_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
