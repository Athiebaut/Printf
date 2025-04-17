/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:48:34 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 01:55:40 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Recursively converts a number to its hexadecimal representation
 *        and prints it character by character.
 *
 * @param list A structure of type t_print containing formatting options,
 *             such as the specifier ('X' for uppercase, others for lowercase)
 *             and flags like 'dot' for precision handling.
 * @param n The number to be converted to hexadecimal.
 * @param iteration Tracks whether the function is in its initial call (0) 
 *                  or a recursive call (1). Used to handle edge cases.
 *
 * @return The total number of characters printed.
 *
 * @details
 * - The function uses recursion to process the number `n` by dividing it
 *   by 16 and determining the remainder to map to a hexadecimal digit.
 * - The `HEXA_LOW` and `HEXA_UP` arrays are used to select the appropriate
 *   character for lowercase or uppercase hexadecimal representation.
 * - The `ft_putnchar` function is used to print each character and its
 *   return value is added to the count of printed characters.
 * - Special cases are handled for the 'p' specifier and precision flags.
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
 * @brief Handles the case where a pointer value is zero and prints "(nil)".
 * 
 * This function adjusts the precision and width of the output based on the 
 * provided `t_print` structure. If the `precision` is not set, it defaults 
 * to 5. If the `minus` flag is not set and the `width` is greater than the 
 * `precision`, it pads the output with spaces to align it properly. Finally, 
 * it prints the string "(nil)" with a length of 5.
 * 
 * @param list A `t_print` structure containing formatting options such as 
 *             precision, width, and flags.
 * @param count A pointer to an integer that keeps track of the total number 
 *              of characters printed. This value is updated within the 
 *              function.
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
 * @brief Handles the formatted printing of a pointer value with specific flags and width/precision.
 *
 * This function is a helper for printing pointer values in a formatted manner. It takes into account
 * various formatting flags such as `minus`, `zero`, `dot`, and adjusts the output accordingly. It also
 * handles padding with spaces or zeros, and ensures the "0x" prefix is added for pointer representation.
 *
 * @param l       A structure of type `t_print` containing formatting options such as width, precision,
 *                and flags (`minus`, `zero`, `dot`).
 * @param count   A pointer to an integer that keeps track of the total number of characters written.
 *                This value is updated as the function writes characters to the output.
 * @param len     The length of the hexadecimal representation of the pointer value.
 * @param n       The pointer value to be printed, cast to `uintptr_t` for safe manipulation.
 *
 * @note The function assumes that the caller has already calculated the length of the hexadecimal
 *       representation (`len`) and passed it as an argument.
 * @note The function uses helper functions such as `ft_putnchar` for padding and `ft_recursive_hex`
 *       for recursive hexadecimal conversion.
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
 * @file ft_print_ptr.c
 * @brief Contains the implementation of the function to print a pointer address.
 *
 * @function ft_print_ptr
 * @param l A structure of type `t_print` containing formatting options such as width, precision, and flags.
 * @param args A `va_list` containing the variable arguments passed to the function.
 * @return The total number of characters written to the output.
 *
 * This function is responsible for formatting and printing a pointer address. It handles
 * special cases such as when the pointer value is `NULL` and applies formatting options
 * like precision, width, and flags (e.g., zero-padding). The function also ensures that
 * the "0x" prefix is added for pointer representation in hexadecimal format.
 *
 * The function uses helper functions:
 * - `if_n_equal_zero`: Handles the case when the pointer value is `NULL`.
 * - `ft_nbrlen`: Calculates the length of the number in the specified base (16 for hexadecimal).
 * - `ft_print_ptr_bis`: Handles the actual printing of the pointer value with formatting.
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
