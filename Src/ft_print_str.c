/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:50:51 by alix              #+#    #+#             */
/*   Updated: 2025/04/18 01:56:21 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Writes up to 'size' characters from the given string to the standard output.
 * 
 * @param str The string to be written. If NULL, the function does nothing and returns 0.
 * @param size The maximum number of characters to write from the string.
 * @return The number of characters written on success, or 0 if the string is NULL.
 */
int	ft_putnstr(char *str, int size)
{
	if (str)
		return ((int)write(1, str, size));
	return (0);
}

/**
 * @brief Handles the case where a string is null and prepares a default string.
 * 
 * This function checks if the given string is null and, if necessary, allocates
 * memory for a default string "(null)". It also considers specific formatting
 * conditions based on the `t_print` structure's precision and width fields.
 * 
 * @param list A `t_print` structure containing formatting information such as
 *             precision and width.
 * @param string A pointer to a char pointer where the default string will be
 *               stored if the input string is null.
 * @param has_malloc A pointer to an integer that will be set to 1 if memory
 *                   was allocated for the default string, or left unchanged
 *                   otherwise.
 * 
 * @return Returns 1 if a default string was allocated and set, or 0 if no
 *         action was needed.
 * 
 * @note The caller is responsible for freeing the allocated memory for the
 *       default string if `has_malloc` is set to 1.
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
 * @brief Prints a formatted string based on the given parameters.
 *
 * This function retrieves a string argument from the variable argument list,
 * applies formatting options such as width, precision, padding, and alignment,
 * and prints the resulting string. It also handles special cases such as null
 * strings and dynamically allocated strings.
 *
 * @param list A `t_print` structure containing formatting options:
 *             - `dot`: Indicates if precision is specified.
 *             - `precision`: The maximum number of characters to print.
 *             - `width`: The minimum width of the output.
 *             - `minus`: Left-aligns the output if set.
 *             - `zero`: Pads with zeros instead of spaces if set.
 *             - `sign`: Indicates if a sign is required for numeric values.
 * @param args A `va_list` containing the variable arguments, from which the
 *             string to be printed is retrieved.
 *
 * @return The total number of characters printed.
 *
 * @note If the string is null, the function calls `if_string_null` to handle
 *       the null case and may allocate memory for a replacement string.
 *       If memory is allocated, it is freed before returning.
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
