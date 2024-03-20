/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:48:34 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/20 23:55:28 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

int	ft_recursive_hex(t_print list, size_t n, size_t iteration)
{
	int		count;
	int		i;
	char	c;

	count = 0;
	if (n > 0 || (!iteration && (list.specifier != 'p' || !list.dot)))
	{
		i = n % 16;
		if (list.specifier != 'X')
			c = HEXA_LOW[i];
		else
			c = HEXA_UP[i];
		n /= 16;
		iteration = 1;
		count += ft_recursive_hex(list, n, iteration);
		count += ft_putnchar(c, 1);
	}
	return (count);
}

int	ft_print_ptr(t_print list, va_list args)
{
	int		count;
	size_t	n;
	int		len;

	count = 0;
	n = va_arg(args, size_t);
	len = ft_nbrlen(n, 16);
	len *= !(!n && !list.precision && list.dot);
	if (list.precision < len || !list.dot)
		list.precision = len;
	count += write(1, "0x", 2 * list.zero);
	list.width -= 2;
	if (!list.minus && list.width > list.precision && !list.dot && list.zero)
		count += ft_putnchar('0', (list.width - list.precision));
	else if (!list.minus && list.width > list.precision)
		count += ft_putnchar(' ', (list.width - list.precision));
	count += write(1, "0x", 2 * !list.zero);
	count += ft_putnchar('0', (list.precision - len) * (n != 0));
	count += ft_putnchar('0', list.precision * (list.dot && !n));
	if (len)
		count += ft_recursive_hex(list, n, n);
	if (list.minus && list.width > list.precision)
		count += ft_putnchar(' ', list.width - list.precision);
	return (count);
}
