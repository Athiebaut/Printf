/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:48:34 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:49:37 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Calculates the number of hexadecimal digits required to represent a given pointer value.
 *
 * This function determines the size (in terms of hexadecimal digits) of the given
 * pointer value by repeatedly dividing it by 16 until the value becomes zero.
 *
 * @param nb The pointer value (as an unsigned integer of type uintptr_t) to calculate the size for.
 * @return The number of hexadecimal digits required to represent the pointer value.
 */
static int	ptr_size(uintptr_t nb)
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
 * @brief Recursively prints a pointer value in hexadecimal format.
 *
 * This function takes an unsigned integer of type `uintptr_t` and prints
 * its value in hexadecimal format. It uses recursion to break down the
 * number into its hexadecimal digits, starting from the most significant
 * digit. The digits are printed in lowercase (e.g., 'a' for 10, 'b' for 11, etc.).
 *
 * @param nb The pointer value to be printed, represented as an unsigned
 *           integer of type `uintptr_t`.
 *
 * @note This function relies on an external function `ft_put_char` to
 *       output individual characters. Ensure that `ft_put_char` is
 *       implemented and available in the same project.
 */
static void	ft_put_ptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		ft_put_ptr(nb / 16);
		ft_put_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_put_char(nb + '0');
		else
			ft_put_char(nb - 10 + 'a');
	}
}

/**
 * ft_print_ptr - Prints a pointer address in hexadecimal format.
 * 
 * @ptr: The pointer address to be printed, passed as an unsigned integer
 *       of type uintptr_t.
 * 
 * This function prints the memory address of a pointer in a human-readable
 * hexadecimal format prefixed with "0x". If the pointer is NULL (0), it
 * prints "(nil)" instead. The function calculates and returns the total
 * number of characters printed.
 * 
 * Return: The total number of characters printed.
 */
int	ft_print_ptr(uintptr_t ptr)
{
	int	printed;

	printed = 0;
	if (ptr == 0)
		printed = printed + ft_put_str("(nil)");
	else
	{
		printed = printed + write(1, "0x", 2);
		ft_put_ptr(ptr);
		printed = printed + ptr_size(ptr);
	}
	return (printed);
}
