#include "main.h"
/**
 * print_char - Prints a char
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char p = va_arg(types, int);

	return (handle_write_char(p, buffer, flags, width, precision, size));
}
/**
 * print_string - Prints a string
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int Len = 0, j;
	char *s = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (s == NULL)
	{
		s = "(null)";
		if (precision >= 6)
			s = "      ";
	}

	while (s[Len] != '\0')
		Len++;

	if (precision >= 0 && precision < Len)
		Len = precision;

	if (width > Len)
	{
		if (flags & F_MINUS)
		{
			write(1, &s[0], Len);
			for (j = width - Len; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - Len; j > 0; j--)
				write(1, " ", 1);
			write(1, &s[0], Len);
			return (width);
		}
	}

	return (write(1, s, Len));
}
/**
 * print_percent - Prints a percent sign
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int r = va_arg(types, long int);
	unsigned long int dig;

	r = convert_size_number(r, size);

	if (r == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	dig = (unsigned long int)r;

	if (r < 0)
	{
		dig = (unsigned long int)((-1) * r);
		is_negative = 1;
	}

	while (dig > 0)
	{
		buffer[i--] = (dig % 10) + '0';
		dig /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
/**
 * print_binary - Prints an unsigned number
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int a, s, j, sum;
	unsigned int v[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	a = va_arg(types, unsigned int);
	s = 2147483648;
	v[0] = a / s;
	for (j = 1; j < 32; j++)
	{
		s /= 2;
		v[j] = (a / s) % 2;
	}
	for (j = 0, sum = 0, count = 0; j < 32; j++)
	{
		sum += v[j];
		if (sum || j == 31)
		{
			char b = '0' + v[j];

			write(1, &b, 1);
			count++;
		}
	}
	return (count);
}
