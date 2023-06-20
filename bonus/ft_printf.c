/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/15 11:51:13 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		printed = printed + ft_putchar(va_arg(list, int));
	else if (arg == 's')
		printed = printed + ft_putstr(va_arg(list, char *));
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
	int		i;
	t_print	*list;

	printed = 0;
	i = 0;
	if (!arg)
		return (-1);
	list = (t_print *)malloc(sizeof(t_print));
	if (!list)
		return (-1);
	ft_initialize(list);
	va_start (list->args, arg);
	while(arg[i])
	{
		if(arg[i] == '%')
			
	}
	va_end(list->args);
	free(list);
	return (printed);
}

int main()
{
	int i = 42;
	ft_printf("%i\n%c\n%x\n%p", i, 'a', i);
}