/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/21 04:48:57 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

int	ft_convert(va_list args, t_print list)
{
	int	printed;

	printed = 0;
	if (list.specifier == 'c' || list.specifier == '%')
		printed += ft_print_char(list, args);
	else if (list.specifier == 's')
		printed += ft_print_str(list, args);
	else if ((list.specifier == 'd') || (list.specifier == 'i'))
		printed = printed + ft_print_d_i_u(list, args);
	else if (list.specifier == 'u')
		printed = printed + ft_print_d_i_u(list, args);
	else if (list.specifier == 'p')
		printed = printed + ft_print_ptr(list, args);
	else if ((list.specifier == 'x') || (list.specifier == 'X'))
		printed = printed + ft_print_hexa(list, args);
	return (printed);
}

int	ft_printf(const char *arg, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	if (!arg)
		return (-1);
	va_start (args, arg);
	while (*arg)
	{
		if (*arg == '%')
		{
			if (*(++arg))
				printed += ft_parse((char *)arg, args);
			while (*arg && !ft_strchr(SPECIFIERS, *arg))
				arg++;
		}
		else
			printed += ft_putnchar(*arg, 1);
		if (*arg)
			arg++;
	}
	va_end(args);
	return (printed);
}
