/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 01:57:04 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Converts and prints a formatted argument based on the specifier.
 *
 * This function takes a variable argument list and a formatting structure,
 * and prints the argument according to the specified format. It supports
 * various specifiers such as characters, strings, integers, unsigned integers,
 * pointers, and hexadecimal values.
 *
 * @param args The variable argument list containing the value to be printed.
 * @param list A structure of type t_print containing formatting information,
 *             including the specifier that determines the type of argument.
 *
 * @return The total number of characters printed.
 *
 * Supported specifiers:
 * - 'c': Prints a single character.
 * - '%': Prints a literal '%' character.
 * - 's': Prints a null-terminated string.
 * - 'd' or 'i': Prints a signed decimal integer.
 * - 'u': Prints an unsigned decimal integer.
 * - 'p': Prints a pointer address in hexadecimal format.
 * - 'x' or 'X': Prints an unsigned integer in hexadecimal format (lowercase or uppercase).
 */
int	ft_convert(va_list args, t_print list)
{
	int	printed;

	printed = 0;
	if (list.specifier == 'c' || list.specifier == '%')
		printed += ft_print_char(list, args);
	else if (list.specifier == 's')
		printed += ft_print_str(list, args);
	else if ((list.specifier == 'd') || (list.specifier == 'i'))
		printed = printed + ft_print_d_i_u(list, args);
	else if (list.specifier == 'u')
		printed = printed + ft_print_d_i_u(list, args);
	else if (list.specifier == 'p')
		printed = printed + ft_print_ptr(list, args);
	else if ((list.specifier == 'x') || (list.specifier == 'X'))
		printed = printed + ft_print_hexa(list, args);
	return (printed);
}

/**
 * ft_printf - A custom implementation of the printf function.
 *
 * @arg: The format string containing text and format specifiers.
 *       Format specifiers are preceded by '%' and are replaced
 *       with corresponding arguments provided after the format string.
 * @...: Variadic arguments corresponding to the format specifiers in @arg.
 *
 * This function processes the format string and handles text and format
 * specifiers. For each format specifier, it delegates the processing to
 * the `ft_parse` function. Characters that are not part of a format
 * specifier are printed as-is using `ft_putnchar`.
 *
 * Return: The total number of characters printed, or -1 if the format
 *         string is NULL.
 *
 * Note:
 * - The function uses `va_list` to handle variadic arguments.
 * - Format specifiers are defined in the `SPECIFIERS` macro or constant.
 * - The `ft_strchr` function is used to check for valid specifiers.
 * - The `ft_parse` function is expected to handle the actual formatting
 *   and printing of arguments based on the specifier.
 */
int	ft_printf(const char *arg, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	if (!arg)
		return (-1);
	va_start (args, arg);
	while (*arg)
	{
		if (*arg == '%')
		{
			if (*(++arg))
				printed += ft_parse((char *)arg, args);
			while (*arg && !ft_strchr(SPECIFIERS, *arg))
				arg++;
		}
		else
			printed += ft_putnchar(*arg, 1);
		if (*arg)
			arg++;
	}
	va_end(args);
	return (printed);
}
