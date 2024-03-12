/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/12 03:19:52 by alix             ###   ########.fr       */
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
	// else if ((list.specifier == 'd') || (list.specifier == 'i'))
	// 	printed = printed + ft_print_int_signed(va_arg(args, int));
	// else if (list.specifier == 'u')
	// 	printed = printed + ft_print_int_unsigned(va_arg(args, unsigned int));
	// else if (list.specifier == 'p')
	// 	printed = printed + ft_print_ptr(va_arg(args, uintptr_t));
	// else if ((list.specifier == 'x') || (list.specifier == 'X'))
	// 	printed = printed + ft_print_hexadecimal(va_arg(args,
	// 				unsigned int), list.specifier);
	return (printed);
}

int	ft_printf_bonus(const char *arg, ...)
{
	int		printed;
	va_list		args;
	char	*start;

	printed = 0;
	if (!arg)
		return (-1);
	va_start (args, arg);
	while(*arg)
	{
		if (*arg == '%')
		{
			start = (char *)arg; 
			if (*(++arg))
				printed = ft_parse((char *)arg, args);
			while (*arg && !ft_strchr(SPECIFIERS, *arg))
				arg++;
			if (!(*arg))
				arg = start;
		}
		else
			printed += ft_putnchar(*arg, 1);
		if (*arg)
			arg++;
	}
	va_end(args);
	return (printed);
}

int main()
{
	ft_printf_bonus("%.3s\n", "aasdas");
	printf("%.3s\n", "aasdas");
}
