/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:49:26 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * ft_put_char - Writes a single character to the standard output.
 *
 * @c: The character to be written, passed as an integer.
 *
 * Return: Always returns 1, indicating that one character was written.
 *
 * Description:
 * This function uses the `write` system call to output a single character
 * to the standard output (file descriptor 1). It is a simple utility
 * function that can be used in custom implementations of formatted output
 * functions like printf.
 */
int	ft_put_char(int c)
{
	write(1, &c, 1);
	return (1);
}

/**
 * ft_put_str - Writes a string to the standard output.
 *
 * @str: The string to be written. If the string is NULL, the function
 *       writes "(null)" to the standard output.
 *
 * Return: The number of characters written to the standard output.
 *         If the string is NULL, it returns 6 (the length of "(null)").
 *
 * Note: This function uses ft_put_char to write individual characters
 *       of the string. Ensure that ft_put_char is implemented correctly.
 */
int	ft_put_str(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		i = i + write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_put_char(str[i]);
		i++;
	}
	return (i);
}

/**
 * @brief Converts and prints a value based on the specified format specifier.
 *
 * This function processes a format specifier and retrieves the corresponding
 * argument from the variable argument list. It then calls the appropriate
 * helper function to handle the printing of the value.
 *
 * @param list The variable argument list containing the values to be printed.
 * @param arg The format specifier indicating the type of value to print.
 *            Supported specifiers:
 *            - 'c': Prints a single character.
 *            - 's': Prints a null-terminated string.
 *            - 'd' or 'i': Prints a signed integer.
 *            - 'u': Prints an unsigned integer.
 *            - '%': Prints a literal '%' character.
 *            - 'p': Prints a pointer address.
 *            - 'x' or 'X': Prints an unsigned integer in hexadecimal format
 *              (lowercase for 'x', uppercase for 'X').
 *
 * @return The total number of characters printed.
 */
static int	ft_convert(va_list list, const char arg)
{
	int	printed;

	printed = 0;
	if (arg == 'c')
		printed = printed + ft_put_char(va_arg(list, int));
	else if (arg == 's')
		printed = printed + ft_put_str(va_arg(list, char *));
	else if ((arg == 'd') || (arg == 'i'))
		printed = printed + ft_print_int_signed(va_arg(list, int));
	else if (arg == 'u')
		printed = printed + ft_print_int_unsigned(va_arg(list, unsigned int));
	else if (arg == '%')
		printed = printed + ft_put_char('%');
	else if (arg == 'p')
		printed = printed + ft_print_ptr(va_arg(list, uintptr_t));
	else if ((arg == 'x') || (arg == 'X'))
		printed = printed + ft_print_hexadecimal(va_arg(list,
					unsigned int), arg);
	return (printed);
}

/**
 * ft_printf - A custom implementation of the printf function.
 *
 * @arg: The format string containing characters and format specifiers.
 *       Format specifiers are preceded by '%' and determine how the
 *       subsequent arguments are formatted and printed.
 * @...: A variable number of arguments to be formatted and printed
 *       according to the format specifiers in the format string.
 *
 * This function processes the format string character by character.
 * - If a '%' character is encountered, it processes the next character
 *   as a format specifier and calls the `ft_convert` function to handle
 *   the corresponding argument.
 * - If a regular character is encountered, it is printed directly using
 *   the `ft_put_char` function.
 *
 * Return: The total number of characters printed. If the format string
 *         is NULL, the function returns -1.
 *
 * Note: This function uses the `va_list` type and related macros to
 *       handle the variable number of arguments.
 */
int	ft_printf(const char *arg, ...)
{
	int		printed;
	int		i;
	va_list	list;

	printed = 0;
	i = 0;
	if (!arg)
		return (-1);
	va_start (list, arg);
	while (arg[i])
	{
		if (arg[i] == '%')
		{
			printed = printed + ft_convert(list, arg[i + 1]);
			i++;
		}
		else
			printed = printed + ft_put_char(arg[i]);
		i++;
	}
	va_end(list);
	return (printed);
}
