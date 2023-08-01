/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:47:08 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

void	ft_initialize(t_print *list)
{
	char  specifier = 0;
	int   width = 0;
	int   precision = 0;
	int   minus = 0;
	int   zero = 0;
	int   dot = 0;
	int   sharp = 0;
	int   space = 0;
	int   plus = 0;
	int   sign = 0;
}

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		i = i + write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
	return (i);
}

static int	ft_convert(va_list list, const char arg)
{
	int	printed;

	printed = 0;
	if (arg == 'c')
		printed = printed + ft_put_char(va_arg(list, int));
	else if (arg == 's')
		printed = printed + ft_put_str(va_arg(list, char *));
	else if ((arg == 'd') || (arg == 'i'))
		printed = printed + ft_print_int_signed(va_arg(list, int));
	else if (arg == 'u')
		printed = printed + ft_print_int_unsigned(va_arg(list, unsigned int));
	else if (arg == '%')
		printed = printed + ft_putchar('%');
	else if (arg == 'p')
		printed = printed + ft_print_ptr(va_arg(list, uintptr_t));
	else if ((arg == 'x') || (arg == 'X'))
		printed = printed + ft_print_hexadecimal(va_arg(list,
					unsigned int), arg);
	return (printed);
}

int	ft_printf(const char *arg, ...)
{
	int		printed;
	va_list		args;

	printed = 0;
	if (!arg)
		return (-1);
	va_start (args, arg);
	while(*arg)
	{
		if (*arg == '%')
		{
			if (*(++arg))
			{
				printed = ft_parse((char *)arg, args);
			}
		}
		else
		{}
	}
	va_end(args);
	return (printed);
}
