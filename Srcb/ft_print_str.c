/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:50:51 by alix              #+#    #+#             */
/*   Updated: 2024/03/26 23:50:36 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * ft_putnstr - Writes a specified number of characters from a string to the standard output.
 * 
 * @str: The string to be written. If NULL, the function does nothing and returns 0.
 * @size: The number of characters to write from the string.
 * 
 * Return: The number of bytes written on success, or 0 if the string is NULL.
 *         If an error occurs during the write operation, the return value is unspecified.
 */
int	ft_putnstr(char *str, int size)
{
	if (str)
		return ((int)write(1, str, size));
	return (0);
}

/**
 * if_string_null - Handles the case where a string is NULL.
 *
 * @list: A structure of type t_print containing formatting options.
 * @string: A pointer to a char pointer where the allocated string will be stored.
 * @has_malloc: A pointer to an integer that will be set to 1 if memory is allocated.
 *
 * This function checks if the string is NULL and allocates memory for the string
 * "(null)" if necessary. It also ensures that the allocated memory is properly
 * copied with the placeholder string. The function returns 0 if the precision
 * is less than 6 and greater than 0, and the width is 0. Otherwise, it returns 1.
 *
 * Return: 0 if the conditions for precision and width are met, otherwise 1.
 */
static	int	if_string_null(t_print list, char **string, int *has_malloc)
{
	if (((list.precision < 6 && list.precision > 0) && !list.width))
		return (0);
	*string = malloc(sizeof(char) * 7);
	*has_malloc = 1;
	ft_strlcpy(*string, "(null)", 7);
	return (1);
}

/**
 * ft_print_str - Prints a formatted string based on the given parameters.
 * 
 * @list: A structure of type t_print containing formatting options such as
 *        width, precision, flags (minus, zero, dot, etc.), and sign.
 * @args: A va_list containing the arguments to be formatted and printed.
 * 
 * This function retrieves a string from the variable argument list and formats
 * it according to the specifications in the t_print structure. It handles
 * cases where the string is NULL, applies precision and width formatting, and
 * manages padding with spaces or zeros as needed. If the string is dynamically
 * allocated during processing, it ensures proper memory deallocation.
 * 
 * Return: The total number of characters printed.
 */
int	ft_print_str(t_print list, va_list args)
{
	char	*string;
	int		count;
	int		has_malloc;

	count = 0;
	has_malloc = 0;
	string = va_arg(args, char *);
	if (!string)
		if (!if_string_null(list, &string, &has_malloc))
			return (0);
	if (!list.dot || list.precision > (int)ft_strlen(string)
		|| list.precision < 0)
		list.precision = ft_strlen(string);
	if (!list.minus && list.width > list.precision && list.zero && (!list.dot
			|| list.sign))
		count += ft_putnchar('0', list.width - list.precision);
	else if (!list.minus && list.width - list.precision > 0)
		count += ft_putnchar(' ', list.width - list.precision);
	count += ft_putnstr(string, list.precision);
	if (list.minus && list.width - list.precision > 0)
		count += ft_putnchar(' ', list.width - list.precision);
	if (has_malloc)
		free(string);
	return (count);
}
