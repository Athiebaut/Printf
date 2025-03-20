/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/26 23:50:37 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * @brief Handles the conversion and printing of various data types based on the format specifier.
 * 
 * This function determines the appropriate printing function to call based on the 
 * format specifier stored in the `t_print` structure. It supports the following specifiers:
 * - 'c': Prints a single character.
 * - '%': Prints a literal '%' character.
 * - 's': Prints a string.
 * - 'd' or 'i': Prints a signed decimal integer.
 * - 'u': Prints an unsigned decimal integer.
 * - 'p': Prints a pointer address in hexadecimal format.
 * - 'x' or 'X': Prints an unsigned integer in hexadecimal format (lowercase or uppercase).
 * 
 * @param args A `va_list` containing the arguments to be printed.
 * @param list A `t_print` structure containing the format specifier and other formatting options.
 * @return The total number of characters printed.
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
 *       with corresponding arguments provided in the variadic list.
 * 
 * This function processes the format string and handles format
 * specifiers by delegating their processing to the `ft_parse` function.
 * It also handles regular characters by printing them directly.
 * 
 * Return: The total number of characters printed, or -1 if the
 *         format string is NULL.
 * 
 * Notes:
 * - The function uses a variadic argument list (`va_list`) to handle
 *   additional arguments corresponding to format specifiers.
 * - The `ft_parse` function is expected to handle the parsing and
 *   printing of specific format specifiers.
 * - The `ft_putnchar` function is used to print regular characters.
 * - The `SPECIFIERS` macro or constant is assumed to define the valid
 *   format specifiers.
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
