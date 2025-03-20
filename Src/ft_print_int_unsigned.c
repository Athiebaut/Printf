/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:47 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:48:29 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Calculates the number of digits required to represent an unsigned integer.
 *
 * This function determines the size (number of digits) of an unsigned integer
 * when represented in base 10. If the input number is 0, the size is considered
 * to be 1, as a single digit is required to represent 0.
 *
 * @param nb The unsigned integer whose size is to be calculated.
 * @return The number of digits required to represent the input number in base 10.
 */
static int	str_size(unsigned int nb)
{
	int	size;

	size = 0;
	if (nb <= 0)
		size = 1;
	while (nb != 0)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

/**
 * @brief Converts an unsigned integer to a null-terminated string.
 *
 * This function takes an unsigned integer as input and converts it into
 * a dynamically allocated string representation of the number. The caller
 * is responsible for freeing the allocated memory.
 *
 * @param n The unsigned integer to be converted.
 * @return A pointer to the dynamically allocated string representing the
 *         number, or NULL if memory allocation fails.
 *
 * @note The returned string is null-terminated.
 * @note If the input number is 0, the function returns a string containing "0".
 */
static char	*ft_itoa(unsigned int n)
{
	char			*str;
	long int		size;

	size = str_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size = size - 1;
	if (n == 0)
		str[0] = '0';
	else
	{
		while (n > 0)
		{
			str[size] = 48 + (n % 10);
			n = n / 10;
			size--;
		}
	}
	return (str);
}

/**
 * ft_print_int_unsigned - Prints an unsigned integer to the standard output.
 * 
 * @nb: The unsigned integer to be printed.
 * 
 * This function converts the given unsigned integer to a string using `ft_itoa`,
 * prints the string using `ft_put_str`, and then frees the allocated memory for
 * the string. It returns the number of characters printed.
 * 
 * Return: The number of characters printed.
 */
int	ft_print_int_unsigned(unsigned int nb)
{
	char	*num;
	int		size;

	num = ft_itoa(nb);
	size = ft_put_str(num);
	free(num);
	return (size);
}
