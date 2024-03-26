/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:48:34 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/26 23:50:36 by athiebau         ###   ########.fr       */
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

static void	if_n_equal_zero(t_print list, int *count)
{
	if (!list.precision)
		list.precision = 5;
	if (!list.minus && list.width > list.precision)
		*count += ft_putnchar(' ', list.width - list.precision);
	*count += ft_putnstr("(nil)", 5);
}

static void	ft_print_ptr_bis(t_print l, int *count, int len, uintptr_t n)
{
	if (!l.minus && l.width > l.precision && !l.dot && l.zero)
		*count += ft_putnchar('0', (l.width - l.precision));
	else if (!l.minus && l.width > l.precision)
		*count += ft_putnchar(' ', (l.width - l.precision));
	*count += write(1, "0x", 2 * !l.zero);
	*count += ft_putnchar('0', (l.precision - len) * (n != 0));
	*count += ft_putnchar('0', l.precision * (l.dot && !n));
	if (len)
		*count += ft_recursive_hex(l, n, n);
	if (l.minus && l.width > *count && l.width > l.precision)
		*count += ft_putnchar(' ', l.width - l.precision);
}

int	ft_print_ptr(t_print l, va_list args)
{
	int			count;
	uintptr_t	n;
	int			len;

	count = 0;
	n = va_arg(args, size_t);
	if (n == 0)
		if_n_equal_zero(l, &count);
	else
	{	
		len = ft_nbrlen(n, 16);
		len *= !(!n && !l.precision && l.dot);
		if (l.precision < len || !l.dot)
			l.precision = len;
		count += write(1, "0x", 2 * l.zero);
		l.width -= 2;
		ft_print_ptr_bis(l, &count, len, n);
	}
	return (count);
}
