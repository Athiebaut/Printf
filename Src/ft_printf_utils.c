/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 17:35:37 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 01:32:50 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Calculates the number of digits required to represent a number
 *        in a given base.
 *
 * @param n The number whose length is to be calculated. It can be any
 *          long integer.
 * @param base The base in which the number is represented. Must be greater
 *             than 1.
 * @return The number of digits required to represent the number in the
 *         specified base. Returns 1 if the number is 0.
 */
int	ft_nbrlen(long n, int base)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		len++;
		n /= base;
	}
	return (len);
}

/**
 * @file ft_uitoa.c
 * @brief Converts an unsigned integer to a null-terminated string.
 *
 * This function takes an unsigned integer as input and converts it into
 * a string representation in base 10. The resulting string is dynamically
 * allocated and must be freed by the caller to avoid memory leaks.
 *
 * @param n The unsigned integer to convert.
 * @return A pointer to the newly allocated string containing the number
 *         representation, or NULL if memory allocation fails or if the
 *         length of the number exceeds 10 digits.
 *
 * @note The function uses `ft_nbrlen` to calculate the length of the number
 *       in base 10. Ensure that `ft_nbrlen` is implemented correctly and
 *       available in the project.
 */
char	*ft_uitoa(unsigned int n)
{
	char			*str;
	int				len;

	len = ft_nbrlen(n, 10);
	if (len > 10)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len-- > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (!str)
		return (NULL);
	return (str);
}
