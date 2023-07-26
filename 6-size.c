#include "main.h"
/**
 * get_size - Calculates the Size to cast the argument.
 *
 * @format: Formatted String in which to print the arguments.
 * @i: Listed arguments to be printed.
 *
 * Return: Precision.
 */
int get_size(const char *format, int *i)
{
int nextIndex = *i + 1;
int size = 0;
if (format[nextIndex] == 'l')
size = S_LONG;
else if (format[nextIndex] == 'h')
size = S_SHORT;
if (size == 0)
*i = nextIndex - 1;
else
*i = nextIndex;
return (size);
}
