/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:48:34 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/26 23:50:36 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * @brief Recursively converts a number to its hexadecimal representation
 *        and prints it character by character.
 *
 * @param list A structure of type t_print containing formatting options,
 *             including the specifier ('X' for uppercase, others for lowercase)
 *             and flags like 'dot' for precision handling.
 * @param n The number to be converted to hexadecimal.
 * @param iteration A flag to indicate whether the recursion has started
 *                  (0 for initial call, 1 for subsequent recursive calls).
 *
 * @return The total number of characters printed.
 *
 * @note This function handles both uppercase and lowercase hexadecimal
 *       representations based on the specifier in the t_print structure.
 *       It also considers special cases for the 'p' specifier and precision
 *       handling when the 'dot' flag is set.
 */
int	ft_recursive_hex(t_print list, size_t n, size_t iteration)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	if (n > 0 || (!iteration && (list.specifier != 'p' || !list.dot)))
	{
		i = n % 16;
		if (list.specifier != 'X')
			c = HEXA_LOW[i];
		else
			c = HEXA_UP[i];
		n /= 16;
		iteration = 1;
		count += ft_recursive_hex(list, n, iteration);
		count += ft_putnchar(c, 1);
	}
	return (count);
}

/**
 * if_n_equal_zero - Handles the case where a specific condition is met
 *                   (likely when a pointer value is zero).
 *
 * @list: A structure of type t_print containing formatting options such as
 *        precision, width, and alignment (minus flag).
 * @count: A pointer to an integer that tracks the total number of characters
 *         printed. This value is updated within the function.
 *
 * Description:
 * This function checks if the precision in the `list` structure is zero and
 * assigns it a default value of 5 if true. It then handles padding with spaces
 * if the `minus` flag is not set and the width is greater than the precision.
 * Finally, it appends the string "(nil)" to the output and updates the `count`
 * accordingly.
 */
static void	if_n_equal_zero(t_print list, int *count)
{
	if (!list.precision)
		list.precision = 5;
	if (!list.minus && list.width > list.precision)
		*count += ft_putnchar(' ', list.width - list.precision);
	*count += ft_putnstr("(nil)", 5);
}

/**
 * @brief Prints a pointer address in hexadecimal format with formatting options.
 *
 * This function handles the formatting and printing of a pointer address
 * based on the specified formatting options provided in the `t_print` structure.
 * It supports options such as zero-padding, left alignment, width, and precision.
 *
 * @param l      A `t_print` structure containing formatting options:
 *               - `minus`: Left-align the output if true.
 *               - `width`: Minimum field width for the output.
 *               - `precision`: Minimum number of digits to print.
 *               - `dot`: Indicates if precision is specified.
 *               - `zero`: Pads with zeros instead of spaces if true.
 * @param count  A pointer to an integer that keeps track of the total number
 *               of characters printed. This value is updated within the function.
 * @param len    The length of the hexadecimal representation of the pointer value.
 * @param n      The pointer value to be printed, cast to `uintptr_t`.
 *
 * @note The function assumes that the caller has already calculated the length
 *       of the hexadecimal representation (`len`) and passed it as an argument.
 *       It also assumes that the `count` pointer is valid and initialized.
 */
static void	ft_print_ptr_bis(t_print l, int *count, int len, uintptr_t n)
{
	if (!l.minus && l.width > l.precision && !l.dot && l.zero)
		*count += ft_putnchar('0', (l.width - l.precision));
	else if (!l.minus && l.width > l.precision)
		*count += ft_putnchar(' ', (l.width - l.precision));
	*count += write(1, "0x", 2 * !l.zero);
	*count += ft_putnchar('0', (l.precision - len) * (n != 0));
	*count += ft_putnchar('0', l.precision * (l.dot && !n));
	if (len)
		*count += ft_recursive_hex(l, n, n);
	if (l.minus && l.width > *count && l.width > l.precision)
		*count += ft_putnchar(' ', l.width - l.precision);
}

/**
 * ft_print_ptr - Prints a pointer address in hexadecimal format.
 * 
 * @l: A structure of type `t_print` containing formatting options such as
 *     width, precision, zero-padding, and dot flag.
 * @args: A `va_list` containing the variable arguments, from which the pointer
 *        value is extracted.
 * 
 * This function handles the formatting and printing of a pointer address.
 * It first checks if the pointer value is `0` and handles it accordingly.
 * If the pointer is not `0`, it calculates the length of the hexadecimal
 * representation, adjusts the precision based on the formatting options,
 * and prints the pointer with the "0x" prefix if required.
 * 
 * Return: The total number of characters printed.
 */
int	ft_print_ptr(t_print l, va_list args)
{
	int			count;
	uintptr_t	n;
	int			len;

	count = 0;
	n = va_arg(args, size_t);
	if (n == 0)
		if_n_equal_zero(l, &count);
	else
	{	
		len = ft_nbrlen(n, 16);
		len *= !(!n && !l.precision && l.dot);
		if (l.precision < len || !l.dot)
			l.precision = len;
		count += write(1, "0x", 2 * l.zero);
		l.width -= 2;
		ft_print_ptr_bis(l, &count, len, n);
	}
	return (count);
}
