/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:49:44 by alix              #+#    #+#             */
/*   Updated: 2024/03/26 23:50:32 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * @brief Writes a character to the standard output a specified number of times.
 *
 * This function writes the character `c` to the standard output `size` times
 * using the `write` system call. It returns the total number of characters
 * written.
 *
 * @param c The character to be written.
 * @param size The number of times the character should be written.
 * @return The total number of characters successfully written.
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
 * @brief Implements the function to handle the 'c' and '%' specifiers for a custom printf.
 *
 * @param list A structure of type t_print containing formatting options such as width, precision, 
 *             minus flag, zero flag, and the specifier.
 * @param args A va_list containing the variable arguments passed to the custom printf function.
 * 
 * @return The total number of characters printed.
 *
 * The function processes the 'c' specifier to print a single character or the '%' specifier to print
 * a literal '%' character. It handles formatting options such as width, precision, left alignment 
 * (minus flag), and zero padding (zero flag). The function calculates the number of padding characters 
 * (spaces or zeros) required based on the width and precision, prints them, and then prints the 
 * character itself. If the minus flag is set, padding is added after the character; otherwise, it is 
 * added before.
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
