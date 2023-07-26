#include "main.h"

/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long dig_pntr;
	char map_to[] = "0123456789abcdef";
	void *p = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (p == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	dig_pntr = (unsigned long)p;

	while (dig_pntr > 0)
	{
		buffer[ind--] = map_to[dig_pntr % 16];
		dig_pntr /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	ind++;
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *s = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		return (write(1, "(null)", 6));

	while (s[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = s[i];
		else
			offset += append_hexa_code(s[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}
/**
 * print_reverse - Prints reverse string.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *s;
	int j, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	s = va_arg(types, char *);

	if (s == NULL)
	{
		UNUSED(precision);

		s = ")Null(";
	}
	for (j = 0; s[j]; j++)

	for (j = j - 1; j >= 0; j--)
	{
		char a = s[j];

		write(1, &a, 1);
		count++;
	}
	return (count);
}
/**
 * print_rot13string - Print a string in rot13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char b;
	char *s;
	unsigned int l, k;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	s = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (s == NULL)
		s = "(AHYY)";
	for (l = 0; s[l]; l++)
	{
		for (k = 0; in[k]; k++)
		{
			if (in[k] == s[l])
			{
				b = out[k];
				write(1, &b, 1);
				count++;
				break;
			}
		}
		if (!in[k])
		{
			b = s[l];
			write(1, &b, 1);
			count++;
		}
	}
	return (count);
}
