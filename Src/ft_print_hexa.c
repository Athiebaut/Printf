/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:58:56 by alix              #+#    #+#             */
/*   Updated: 2025/04/18 01:52:15 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Returns the appropriate prefix for hexadecimal numbers based on the specifier.
 * 
 * This function checks the specifier in the t_print structure and returns
 * the corresponding prefix for hexadecimal numbers. If the specifier is 'X',
 * it returns "0X" (uppercase). Otherwise, it returns "0x" (lowercase).
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
 * @brief Implements a function to format and print hexadecimal numbers with
 *        various formatting options.
 *
 * @param l A structure of type `t_print` containing formatting options such as:
 *          - `precision`: Minimum number of digits to be printed.
 *          - `width`: Minimum field width for the output.
 *          - `sharp`: Flag to prepend "0x" or "0X" for non-zero values.
 *          - `zero`: Flag to pad with zeros instead of spaces.
 *          - `minus`: Flag to left-align the output within the field width.
 *          - `dot`: Flag indicating whether precision is specified.
 *          - `sign`: Flag for sign handling.
 * @param args A `va_list` containing the arguments to be formatted and printed.
 *
 * @return The total number of characters printed.
 *
 * @details
 * This function formats and prints an unsigned integer as a hexadecimal number
 * according to the specified formatting options. It supports:
 * - Precision handling: Ensures the number has at least the specified number
 *   of digits.
 * - Width handling: Ensures the output occupies at least the specified field
 *   width, padding with spaces or zeros as needed.
 * - Flags:
 *   - `sharp`: Adds a "0x" or "0X" prefix for non-zero values.
 *   - `zero`: Pads with zeros instead of spaces when the width is greater than
 *     the number of digits.
 *   - `minus`: Left-aligns the output within the field width.
 * - Handles edge cases such as zero values with precision set to zero.
 *
 * The function internally uses helper functions like `ft_putnstr`, `ft_putnchar`,
 * and `ft_recursive_hex` to handle string output, padding, and recursive
 * hexadecimal conversion, respectively.
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
