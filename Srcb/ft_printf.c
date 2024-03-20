/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/21 00:05:31 by alix             ###   ########.fr       */
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
	va_list		args;
	//char	*start;

	printed = 0;
	if (!arg)
		return (-1);
	va_start (args, arg);
	while(*arg)
	{
		if (*arg == '%')
		{
			// start = (char *)arg;
			if (*(++arg))
				printed += ft_parse((char *)arg, args);
			while (*arg && !ft_strchr(SPECIFIERS, *arg))
				arg++;
			// if (!(*arg))
			// 	arg = start;
		}
		else
			printed += ft_putnchar(*arg, 1);
		if (*arg)
			arg++;
	}
	va_end(args);
	return (printed);
}

// int main()
// {
// 	printf("CHAR c and widths : ");
// 	printf("Me :\n\n");
// 	ft_printf("%1c\n", 'a');
// 	ft_printf("%1c\n", '\0');
// 	ft_printf("%10c\n", 'b');
// 	ft_printf("%10c\n", '\0');
// 	ft_printf("%2c\n", 'c');
// 	ft_printf("there are 15 spaces between this text and the next char%15c\n", 'd');
// 	ft_printf("%5chis paragraph is indented\n", 't');
// 	ft_printf("%5c now you see\n", '\0');
// 	ft_printf("The number %7c represents luck\n", '7');
// 	printf("---------------------------------------------------------\n");
// 	printf("%1c\n", 'a');
// 	printf("%1c\n", '\0');
// 	printf("%10c\n", 'b');
// 	printf("%10c\n", '\0');
// 	printf("%2c\n", 'c');
// 	printf("there are 15 spaces between this text and the next char%15c\n", 'd');
// 	printf("%5chis paragraph is indented\n", 't');
// 	printf("%5c now you see\n", '\0');
// 	printf("The number %7c represents luck\n", '7');
// 	printf("---------------------------------------------------------");
// 	ft_printf("%c%c%c*\n", '\0', '1', 1);
// 	printf("%c%c%c*\n", '\0', '1', 1);
// }

