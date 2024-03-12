/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:22:38 by alix              #+#    #+#             */
/*   Updated: 2024/03/12 02:56:54 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

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

static void	get_width(char *arg, va_list args, t_print *list)
{
	int	size;

	size = 0;
	while (*arg != '.' && !ft_strchr(SPECIFIERS, *arg))
	{
		if (*arg == '-')
			list->minus = 1;
		if(*arg == '0' && !ft_isdigit(*(arg - 1)))
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

static void	get_precision(char *arg, va_list args, t_print *list)
{
	int	size;

	size = 0;
	while (!ft_strchr(SPECIFIERS, *arg))
	{
		if((*arg == '*' || ft_isdigit(*arg)) && !size)
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

int	ft_parse(char *arg, va_list args)
{
	t_print	list;

	ft_initialize(&list);
	get_width(arg, args, &list);
	get_flags(arg, &list);
	while(*arg != '.' && !ft_strchr(SPECIFIERS, *arg))
		arg++;
	if (!list.specifier && *arg == '.')
	{
		list.dot = 1;
		get_precision(arg, args, &list);
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

