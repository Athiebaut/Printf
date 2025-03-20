/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:28 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/26 23:50:35 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * @brief Determines the sign character to be used based on the `plus` flag in the t_print structure.
 *
 * @param list A t_print structure containing the `plus` flag.
 *             If `list.plus` is true, the function returns the '+' character.
 *             Otherwise, it returns the '-' character.
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
 * This function handles the formatting and printing of a number string
 * according to the specifications provided in the `t_print` structure.
 * It manages padding, alignment, signs, and other formatting options.
 *
 * @param list A `t_print` structure containing formatting options such as
 *             width, precision, flags (space, plus, minus, zero), and others.
 * @param nbr  A string representation of the number to be printed.
 * @param len  The length of the number string `nbr`.
 * @param neg  An integer indicating if the number is negative (non-zero if true).
 *
 * @return The total number of characters printed.
 *
 * @note The function assumes that the `ft_putnchar` and `plus` helper functions
 *       are defined elsewhere and are used for printing characters and determining
 *       the sign character, respectively.
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
 * ft_print_d_i_u - Prints a number based on the given format specifier.
 *
 * @list: A structure of type t_print containing formatting options.
 * @ap: A va_list containing the arguments to be formatted and printed.
 *
 * This function handles the printing of signed ('d', 'i') and unsigned ('u')
 * integers. It retrieves the number from the variable argument list, processes
 * it based on the formatting options in the t_print structure, and prints it
 * accordingly. The function also handles special cases such as negative numbers,
 * precision, and zero values.
 *
 * Return: The total number of characters printed.
 *
 * Notes:
 * - If the number is negative and the specifier is not 'u', the negative sign
 *   is handled separately, and the number is converted to its absolute value.
 * - If the specifier is 'u', the number is treated as unsigned.
 * - The function uses ft_itoa or ft_uitoa to convert the number to a string.
 * - If the precision is specified and the number is zero, the length may be
 *   adjusted to handle edge cases.
 * - Memory allocated for the number string is freed before returning.
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
