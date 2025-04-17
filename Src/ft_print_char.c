/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:49:44 by alix              #+#    #+#             */
/*   Updated: 2025/04/18 01:51:48 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * ft_putnchar - Writes a character to the standard output a specified number of times.
 *
 * @c: The character to be written.
 * @size: The number of times the character should be written.
 *
 * Return: The total number of characters written. If an error occurs during
 *         writing, the return value may not accurately reflect the intended count.
 *
 * Description:
 * This function writes the character `c` to the standard output `size` times
 * using the `write` system call. It keeps track of the total number of characters
 * successfully written and returns this count.
 */
int	ft_putnchar(char c, int size)
{
	int	count;

	count = 0;
	while (size-- > 0)
		count += (int)write(1, &c, 1);
	return (count);
}

/**
 * @file ft_print_char.c
 * @brief Implements the function to handle character and '%' specifiers for a custom printf.
 *
 * @param list A structure of type `t_print` containing formatting options such as width, precision, 
 *             flags (minus, zero), and the specifier.
 * @param args A `va_list` containing the variable arguments passed to the custom printf function.
 * 
 * @return The total number of characters printed.
 *
 * @details
 * - If the specifier in `list` is 'c', the function retrieves a character from `args`.
 * - If the specifier is '%', the function sets the character to '%'.
 * - The function handles padding with spaces or zeros based on the flags and width specified in `list`.
 * - If the `minus` flag is set, padding is added after the character; otherwise, it is added before.
 * - The `precision` is set to 1 since only one character is printed.
 * - The function uses `ft_putnchar` to print the character and any necessary padding.
 */
int	ft_print_char(t_print list, va_list args)
{
	char	c;
	int		count;

	count = 0;
	if (list.specifier == 'c')
		c = va_arg(args, int);
	else
		c = '%';
	list.precision = 1;
	if (!list.minus && list.zero)
		count += ft_putnchar('0', list.width - list.precision);
	else if (!list.minus && list.width > list.precision)
		count += ft_putnchar(' ', list.width - list.precision);
	count += ft_putnchar(c, 1);
	if (list.minus && list.width - list.precision > 0)
		count += ft_putnchar(' ', list.width - list.precision);
	return (count);
}
