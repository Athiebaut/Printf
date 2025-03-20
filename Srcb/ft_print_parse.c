/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:22:38 by alix              #+#    #+#             */
/*   Updated: 2024/03/26 23:50:35 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

/**
 * @brief Initializes the members of a t_print structure to their default values.
 * 
 * This function sets all the fields of the given t_print structure to zero or 
 * their respective default states. It is typically used to ensure that the 
 * structure is in a clean and predictable state before being used.
 * 
 * @param list Pointer to the t_print structure to be initialized.
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
 * This function iterates through the format string starting from the given 
 * argument pointer `arg` and extracts the width specifier. It handles cases 
 * where the width is specified as a number, an asterisk (*), or is affected 
 * by flags such as '-' (left alignment) or '0' (zero padding). The extracted 
 * width is stored in the `width` field of the `t_print` structure, and the 
 * flags are updated accordingly.
 * 
 * @param arg Pointer to the current position in the format string.
 * @param args Variadic argument list containing the values for '*' specifiers.
 * @param list Pointer to the t_print structure where the parsed values will 
 *             be stored.
 * 
 * @note The function stops parsing when it encounters a '.' or a character 
 *       from the SPECIFIERS set.
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
 * either a '.' or a character from the SPECIFIERS set. During the iteration,
 * it checks for specific flag characters ('+', ' ', '#') and sets the 
 * corresponding fields in the `t_print` structure to indicate their presence.
 *
 * @param arg The format string to parse for flags.
 * @param list A pointer to the t_print structure where the flags will be set.
 *
 * Flags:
 * - '+' : Sets the `plus` field in the t_print structure to 1.
 * - ' ' : Sets the `space` field in the t_print structure to 1.
 * - '#' : Sets the `sharp` field in the t_print structure to 1.
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
 * @brief Extracts and sets the precision value for formatted output.
 *
 * This function parses the precision value from the given format string `arg`.
 * The precision can either be specified as a literal number, or as a `*` 
 * character, in which case the value is retrieved from the variadic arguments.
 * The precision value is then stored in the `precision` field of the `t_print` 
 * structure.
 *
 * @param arg A pointer to the format string being parsed.
 * @param args A variadic arguments list from which the precision value may be 
 *             retrieved if specified as `*`.
 * @param list A pointer to the `t_print` structure where the parsed precision 
 *             value will be stored.
 *
 * @note The function stops parsing when it encounters a character that is part 
 *       of the `SPECIFIERS` set.
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
 * ft_parse - Parses the format string and initializes the print structure.
 * 
 * @arg: The format string to be parsed.
 * @args: The variadic arguments list.
 * 
 * This function initializes a t_print structure and extracts formatting
 * information from the format string. It processes width, flags, precision,
 * and specifier details. The function ensures proper handling of negative
 * width values by setting the minus flag and converting the width to positive.
 * Finally, it calls ft_convert to handle the conversion based on the parsed
 * information.
 * 
 * Return: The result of the ft_convert function, which processes the formatted
 * output based on the parsed data.
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
