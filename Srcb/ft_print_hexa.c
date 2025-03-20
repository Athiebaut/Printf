/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:58:56 by alix              #+#    #+#             */
/*   Updated: 2024/03/26 23:50:34 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * @brief Returns the appropriate prefix for hexadecimal numbers based on the specifier.
 * 
 * This function checks the specifier in the provided t_print structure and 
 * returns the corresponding prefix for hexadecimal numbers. If the specifier 
 * is 'X', it returns "0X" (uppercase prefix). Otherwise, it returns "0x" 
 * (lowercase prefix).
 * 
 * @param list A t_print structure containing the specifier to determine the prefix.
 * @return A string representing the hexadecimal prefix ("0X" or "0x").
 */
static char	*ft_sharp(t_print list)
{
	if (list.specifier == 'X')
		return ("0X");
	return ("0x");
}

/**
 * @file ft_print_hexa.c
 * @brief Contains the implementation of the ft_print_hexa function for printing
 *        hexadecimal numbers with various formatting options.
 *
 * @function ft_print_hexa
 * @param l A struct of type t_print containing formatting options such as width,
 *          precision, flags (sharp, zero, minus), and dot.
 * @param args A va_list containing the arguments to be formatted and printed.
 * @return The total number of characters printed.
 *
 * @details
 * The ft_print_hexa function formats and prints an unsigned integer as a
 * hexadecimal number according to the specified formatting options in the
 * t_print struct. The function supports the following features:
 * - Precision and width formatting.
 * - Handling of the '#' flag for prefixing with "0x" or "0X".
 * - Handling of the '0' flag for zero-padding.
 * - Handling of the '-' flag for left alignment.
 * - Conditional handling of the '.' flag for precision control.
 *
 * The function calculates the length of the number in hexadecimal format,
 * adjusts the width and precision based on the flags, and prints the number
 * with the appropriate padding and formatting. It also handles edge cases
 * such as when the number is zero and precision is explicitly set to zero.
 *
 * Helper functions such as ft_nbrlen, ft_putnstr, ft_putnchar, and
 * ft_recursive_hex are used to perform specific tasks like calculating the
 * length of the number, printing strings, padding with characters, and
 * recursively printing the hexadecimal digits.
 */
int	ft_print_hexa(t_print l, va_list args)
{
	int				count;
	unsigned int	n;
	int				len;

	count = 0;
	n = va_arg(args, unsigned int);
	len = ft_nbrlen(n, 16);
	if (!n && !l.precision && l.dot)
		len = 0;
	if (l.precision < 0 || l.precision < len || !l.dot)
		l.precision = len;
	if (l.sharp && n)
		l.width -= 2;
	count += ft_putnstr(ft_sharp(l), 2 * (l.sharp && l.zero && n));
	if (!l.minus && l.width > l.precision && (!l.dot || l.sign) && l.zero)
		count += ft_putnchar('0', (l.width - l.precision));
	else if (!l.minus && l.width > l.precision)
		count += ft_putnchar(' ', (l.width - l.precision));
	count += ft_putnstr(ft_sharp(l), 2 * (l.sharp && !l.zero && n));
	count += ft_putnchar('0', (l.precision - len));
	if (len)
		count += ft_recursive_hex(l, n, n);
	if (l.minus && l.width > l.precision)
		count += ft_putnchar(' ', l.width - l.precision);
	return (count);
}
