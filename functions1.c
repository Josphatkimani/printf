#include "main.h"
/**
 * print_unsigned - Prints an unsigned n0
 * @types: List all arguments
 * @buffer: Buffer array that handles printing
 * @flags:  Calculates the active flags
 * @width: gets the width
 * @precision: Specifies precision
 * @size: Specifies Size
 * Return: Number of characters printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/**
 * print_octal - Prints an unsigned no in octal notation
 * @types: Lists all arguments
 * @buffer: Buffer array that handles printing
 * @flags:  Calc the active flags
 * @width: gets the width
 * @precision: Specifies precision
 * @size: Specifies Size
 * Return: Number of characters that are printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
/**
 * print_hexadecimal - Prints an unsigned no in hexadecimal notation
 * @types: Lists all the arguments
 * @buffer: Buffer array handling printing
 * @flags:  Calculates the active flags
 * @width: gets the width
 * @precision: Specifies precision
 * @size: Specifies precision
 * Return: Number of characters that are printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lists all the arguments
 * @buffer: Buffer array that handles printing
 * @flags:  Calculates the active flags
 * @width: gets the width
 * @precision: Specifies precision
 * @size: Specifies Size
 * Return: Number of characters that printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lists all the arguments
 * @map_to: Array of values to map the no
 * @buffer: Buffer array that handles print
 * @flags:  Calculates the active flags
 * @flag_ch: Calculates the active flags
 * @width: gets the width
 * @precision: Specifies precision
 * @size: Specifies Size
 * Return: Number of characters printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
