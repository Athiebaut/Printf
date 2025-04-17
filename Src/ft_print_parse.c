/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:22:38 by alix              #+#    #+#             */
/*   Updated: 2025/04/18 01:54:49 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

/**
 * @brief Initializes the members of a t_print structure to their default values.
 *
 * This function sets all the fields of the given t_print structure to zero or
 * their respective default values. It is typically used to reset or prepare
 * the structure for use in formatting operations.
 *
 * @param list A pointer to the t_print structure to be initialized.
 */
static void	ft_initialize(t_print *list)
{
	list->specifier = 0;
	list->width = 0;
	list->precision = 0;
	list->minus = 0;
	list->zero = 0;
	list->dot = 0;
	list->sharp = 0;
	list->space = 0;
	list->plus = 0;
	list->sign = 0;
}

/**
 * @brief Parses the width specifier from a format string and updates the
 *        corresponding fields in the t_print structure.
 *
 * This function iterates through the format string `arg` until it encounters
 * either a '.' or a character from the SPECIFIERS set. During the iteration,
 * it checks for specific flags and width specifiers:
 * - If a '-' character is found, the `minus` flag in the `t_print` structure
 *   is set to 1.
 * - If a '0' character is found and it is not preceded by a digit, the `zero`
 *   flag in the `t_print` structure is set to 1.
 * - If a numeric value or '*' is encountered and the width has not been set
 *   yet, the width is determined:
 *   - If '*' is found, the width is retrieved from the `args` variadic
 *     argument list.
 *   - Otherwise, the width is parsed as an integer using `ft_atoi`.
 *
 * @param arg  The format string to parse.
 * @param args The variadic argument list containing additional arguments.
 * @param list A pointer to the t_print structure to update with parsed values.
 */
static void	get_width(char *arg, va_list args, t_print *list)
{
	int	size;

	size = 0;
	while (*arg != '.' && !ft_strchr(SPECIFIERS, *arg))
	{
		if (*arg == '-')
			list->minus = 1;
		if (*arg == '0' && !ft_isdigit(*(arg - 1)))
			list->zero = 1;
		else if (((*arg >= '0' && *arg <= '9') || *arg == '*') && !size)
		{
			if (*arg == '*')
				list->width = va_arg(args, int);
			else
				list->width = ft_atoi(arg);
			size = 1;
		}
		arg++;
	}
}

/**
 * @brief Parses the format string to extract and set specific flags in the 
 *        t_print structure.
 *
 * This function iterates through the format string `arg` until it encounters
 * either a '.' character or a specifier from the SPECIFIERS string. During 
 * this iteration, it checks for specific flag characters ('+', ' ', '#') and 
 * sets the corresponding fields in the `t_print` structure to indicate the 
 * presence of these flags.
 *
 * @param arg A pointer to the format string to be parsed.
 * @param list A pointer to the t_print structure where the flags will be set.
 *
 * Flags:
 * - '+' : Sets the `plus` field in `list` to 1.
 * - ' ' : Sets the `space` field in `list` to 1.
 * - '#' : Sets the `sharp` field in `list` to 1.
 */
static void	get_flags(char *arg, t_print *list)
{
	while (*arg != '.' && !ft_strchr(SPECIFIERS, *arg))
	{
		if (*arg == '+')
			list->plus = 1;
		if (*arg == ' ')
			list->space = 1;
		if (*arg == '#')
			list->sharp = 1;
		arg++;
	}
}

/**
 * @brief Parses the precision value from the format string and updates the
 *        t_print structure with the extracted precision.
 *
 * This function iterates through the format string `arg` until it encounters
 * a character that belongs to the SPECIFIERS set. During this iteration, it
 * checks for the presence of a precision specifier, which can either be a
 * numeric value or an asterisk ('*'). If an asterisk is found, the precision
 * value is retrieved from the variadic arguments list `args`. If a numeric
 * value is found, it is converted to an integer and assigned to the precision
 * field of the `t_print` structure. The function ensures that the precision
 * is only set once by using the `size` flag.
 *
 * @param arg A pointer to the format string being parsed.
 * @param args A variadic arguments list containing additional arguments.
 * @param list A pointer to the t_print structure where the precision value
 *             will be stored.
 */
static void	get_precision(char *arg, va_list args, t_print *list)
{
	int	size;

	size = 0;
	while (!ft_strchr(SPECIFIERS, *arg))
	{
		if ((*arg == '*' || ft_isdigit(*arg)) && !size)
		{
			if (*arg == '*')
				list->precision = va_arg(args, int);
			else
				list->precision = ft_atoi(arg);
			size = 1;
		}
		arg++;
	}
}

/**
 * ft_parse - Parses the format string and extracts formatting information.
 * 
 * @arg: The format string to parse.
 * @args: The variadic arguments list.
 * 
 * This function initializes a t_print structure, extracts width, flags, 
 * precision, and specifier information from the format string, and 
 * processes them accordingly. It handles negative width by setting the 
 * minus flag and converting the width to positive. The function also 
 * determines if the precision is specified and sets the appropriate 
 * fields in the t_print structure. Finally, it calls ft_convert to 
 * handle the conversion based on the parsed information.
 * 
 * Return: The result of the conversion function (ft_convert).
 */
int	ft_parse(char *arg, va_list args)
{
	t_print	list;

	ft_initialize(&list);
	get_width(arg, args, &list);
	get_flags(arg, &list);
	while (*arg != '.' && !ft_strchr(SPECIFIERS, *arg))
		arg++;
	if (!list.specifier && *arg == '.')
	{
		list.dot = 1;
		get_precision(arg++, args, &list);
		while (!ft_strchr(SPECIFIERS, *arg))
			arg++;
	}
	if (list.width < 0)
	{
		list.minus = 1;
		list.width *= -1;
	}
	list.specifier = *arg;
	list.sign = list.precision < 0;
	return (ft_convert(args, list));
}
