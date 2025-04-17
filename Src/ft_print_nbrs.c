/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:28 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 01:53:26 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Determines the sign character to be used based on the `plus` flag in the t_print structure.
 *
 * @param list A t_print structure containing the `plus` flag.
 *             If `list.plus` is true, the function returns '+'.
 *             Otherwise, it returns '-'.
 *
 * @return A character representing the sign ('+' or '-').
 */
static char	plus(t_print list)
{
	if (list.plus)
		return ('+');
	return ('-');
}

/**
 * @brief Prints a formatted number based on the given parameters.
 *
 * This function handles the formatting and printing of a number according to
 * the specifications provided in the `t_print` structure. It manages padding,
 * alignment, signs, and other formatting options.
 *
 * @param list A `t_print` structure containing formatting options such as
 *             width, precision, flags (space, plus, minus, zero, dot), and sign.
 * @param nbr A string representation of the number to be printed.
 * @param len The length of the number string `nbr`.
 * @param neg An integer indicating whether the number is negative (1 if negative, 0 otherwise).
 *
 * @return The total number of characters printed.
 *
 * @details
 * - Handles padding with spaces or zeros based on the flags and width.
 * - Adds a sign ('+' or '-') or a space before the number if specified.
 * - Aligns the number to the left or right based on the `minus` flag.
 * - Ensures the number is printed with the specified precision.
 * - Writes the formatted number to the standard output.
 */
static int	ft_print_nbr(t_print list, char *nbr, int len, int neg)
{
	int	c;

	c = 0;
	list.width -= (list.space && !neg && !list.plus && list.width);
	if (neg || list.plus)
		c += ft_putnchar(plus(list), list.zero && (!list.dot || list.sign));
	else if (list.space)
		c += ft_putnchar(' ', list.zero && !list.dot);
	if (!list.minus && list.width > list.precision && (!list.dot || list.sign)
		&& list.zero)
		c += ft_putnchar('0', list.width - list.precision - neg - list.plus);
	else if (!list.minus && list.width > list.precision)
		c += ft_putnchar(' ', list.width - list.precision - neg - list.plus);
	if (neg || list.plus)
		c += ft_putnchar(plus(list), !list.zero || (list.dot && !list.sign));
	else if (list.space)
		c += ft_putnchar(' ', !list.zero || list.dot);
	c += ft_putnchar('0', list.precision - len);
	c += write(1, nbr, len);
	if (list.minus && list.width > list.precision)
		c += ft_putnchar(' ', list.width - list.precision - neg - list.plus);
	return (c);
}

/**
 * ft_print_d_i_u - Handles the printing of integer and unsigned integer values
 *                  based on the specified format.
 *
 * @list: A structure of type t_print containing formatting options such as
 *        precision, width, flags, and specifier.
 * @ap: A va_list containing the arguments to be formatted and printed.
 *
 * This function processes integer ('d', 'i') and unsigned integer ('u') 
 * specifiers. It retrieves the corresponding argument from the va_list, 
 * applies formatting rules (e.g., handling negative numbers, precision, 
 * and flags), and converts the number to a string representation. The 
 * formatted number is then printed using the ft_print_nbr function.
 *
 * Return: The total number of characters printed.
 *
 * Notes:
 * - If the specifier is 'u', the number is treated as unsigned.
 * - Negative numbers are handled appropriately, and the '-' sign is 
 *   considered in the output.
 * - Memory allocated for the number string is freed before returning.
 * - If the precision is zero and the number is zero, no characters are printed.
 */
int	ft_print_d_i_u(t_print list, va_list ap)
{
	char		*nbr;
	long long	n;
	int			c;
	int			len;
	int			neg;

	c = 0;
	n = va_arg(ap, int);
	neg = (n < 0 && n >= INT_MIN && list.specifier != 'u');
	if (neg)
		list.plus = 0;
	if (n < 0 && list.specifier != 'u')
		n *= -1;
	if (n < 0 && list.specifier == 'u')
		nbr = ft_uitoa(n);
	else
		nbr = ft_itoa(n);
	len = ft_strlen(nbr);
	if (*nbr == '0' && !list.precision && list.dot)
		len = 0;
	if (list.precision < len || !list.dot)
		list.precision = len;
	c += ft_print_nbr(list, nbr, len, neg);
	free(nbr);
	return (c);
}
