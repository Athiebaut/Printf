/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:20 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:48:05 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Calculates the number of digits required to represent a given 
 *        unsigned integer in hexadecimal (base 16).
 * 
 * @param nb The unsigned integer whose size in hexadecimal is to be calculated.
 * 
 * @return The number of digits required to represent the number in base 16.
 *         Returns 0 if the input number is 0.
 */
static int	number_size(unsigned int nb)
{
	int	size;

	size = 0;
	while (nb != 0)
	{
		size++;
		nb = nb / 16;
	}
	return (size);
}

/**
 * @brief Recursively prints an unsigned integer in hexadecimal format.
 * 
 * This function converts an unsigned integer to its hexadecimal representation
 * and prints it character by character. The format of the hexadecimal output
 * depends on the value of the `arg` parameter:
 * - If `arg` is 'x', the output will be in lowercase (e.g., "1a3f").
 * - If `arg` is 'X', the output will be in uppercase (e.g., "1A3F").
 * 
 * @param nb The unsigned integer to be converted and printed in hexadecimal.
 * @param arg A character indicating the format of the hexadecimal output:
 *            'x' for lowercase, 'X' for uppercase.
 * 
 * @note This function relies on an external function `ft_put_char` to print
 *       individual characters. Ensure that `ft_put_char` is implemented and
 *       available in the same project.
 */
static void	ft_put_hex(unsigned int nb, const char arg)
{
	if (nb >= 16)
	{
		ft_put_hex(nb / 16, arg);
		ft_put_hex(nb % 16, arg);
	}
	else if (arg == 'x')
	{
		if (nb <= 9)
			ft_put_char(nb + '0');
		else
			ft_put_char(nb - 10 + 'a');
	}
	else if (arg == 'X')
	{
		if (nb <= 9)
			ft_put_char(nb + '0');
		else
			ft_put_char(nb - 10 + 'A');
	}
}

/**
 * @brief Prints an unsigned integer in hexadecimal format.
 * 
 * This function prints the given unsigned integer `nb` in hexadecimal format.
 * The format (uppercase or lowercase) is determined by the `arg` parameter.
 * If `nb` is 0, it writes "0" to the standard output.
 * 
 * @param nb The unsigned integer to be printed in hexadecimal format.
 * @param arg Specifies the format of the hexadecimal output:
 *            - 'x' for lowercase hexadecimal (e.g., "1a3f").
 *            - 'X' for uppercase hexadecimal (e.g., "1A3F").
 * 
 * @return The number of characters printed.
 *         - If `nb` is 0, it returns 1 (for the single character "0").
 *         - Otherwise, it returns the number of digits in the hexadecimal representation of `nb`.
 */
int	ft_print_hexadecimal(unsigned int nb, const char arg)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(nb, arg);
	return (number_size(nb));
}
