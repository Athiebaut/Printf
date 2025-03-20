/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_signed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:28 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:48:21 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Converts an unsigned integer into its string representation
 *        and stores it in the provided string buffer.
 *
 * This function takes an unsigned integer `nb` and converts it into
 * its decimal string representation, storing the result in the `str`
 * buffer starting at the specified `size` index. The conversion is
 * performed in reverse order, starting from the least significant digit.
 *
 * @param str A pointer to the character buffer where the result will be stored.
 *            The buffer must be large enough to hold the resulting string.
 * @param nb The unsigned integer to be converted into a string.
 * @param size The index in the buffer where the conversion should start.
 *             This is typically the position of the last digit in the string.
 * @return A pointer to the updated string buffer containing the converted number.
 */
static char	*ft_char(char *str, unsigned int nb, long int size)
{
	while (nb > 0)
	{
		str[size] = 48 + (nb % 10);
		nb = nb / 10;
		size--;
	}
	return (str);
}

/**
 * @brief Calculates the number of characters required to represent
 *        a signed integer as a string, including the sign if negative.
 *
 * @param nb The signed integer whose string size is to be calculated.
 * @return The number of characters required to represent the integer as a string.
 *         This includes space for the negative sign (if applicable) and the null terminator.
 */
static int	str_size(int nb)
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
 * @brief Converts an integer to a null-terminated string representation.
 *
 * This function takes an integer as input and converts it to a string
 * representation. It handles both positive and negative integers, as well
 * as zero. Memory for the resulting string is dynamically allocated and
 * must be freed by the caller.
 *
 * @param n The integer to be converted to a string.
 * @return A pointer to the dynamically allocated string containing the
 *         string representation of the integer. Returns NULL if memory
 *         allocation fails.
 *
 * @note The function uses helper functions `str_size` to determine the
 *       size of the string and `ft_char` to populate the string with
 *       characters. Ensure these helper functions are implemented and
 *       available in the codebase.
 */
static char	*ft_itoa(int n)
{
	char			*str;
	long int		size;
	unsigned int	nb;

	size = str_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size = size - 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		nb = n * -1;
		str[0] = '-';
	}
	else
		nb = n;
	str = ft_char(str, nb, size);
	return (str);
}

/**
 * @brief Prints a signed integer to the standard output.
 * 
 * This function converts the given signed integer to its string representation
 * using `ft_itoa`, prints the string using `ft_put_str`, and then frees the 
 * allocated memory for the string. It returns the number of characters printed.
 * 
 * @param nb The signed integer to be printed.
 * @return The number of characters printed.
 * 
 * @note The function assumes that `ft_itoa` dynamically allocates memory for 
 *       the string representation of the integer, and that `ft_put_str` 
 *       handles the actual printing of the string.
 */
int	ft_print_int_signed(int nb)
{
	char	*num;
	int		size;

	num = ft_itoa(nb);
	size = ft_put_str(num);
	free(num);
	return (size);
}
