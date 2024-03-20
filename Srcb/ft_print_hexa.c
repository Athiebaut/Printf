/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:58:56 by alix              #+#    #+#             */
/*   Updated: 2024/03/21 00:04:08 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

static char	*ft_sharp(t_print list)
{
	if (list.specifier == 'X')
		return ("0X");
	return ("0x");
}

int	ft_print_hexa(t_print list, va_list args)
{
	int				count;
	unsigned int	n;
	int				len;

	count = 0;
	n = va_arg(args, unsigned int);
	len = ft_nbrlen(n, 16);
	if (!n && !list.precision && list.dot)
		len = 0;
	if (list.precision < 0 || list.precision < len || !list.dot)
		list.precision = len;
	if (list.sharp && n)
		list.width -= 2;
	count += ft_putnstr(ft_sharp(list), 2 * (list.sharp && list.zero && n));
	if (!list.minus && list.width > list.precision && (!list.dot || list.sign) && list.zero)
		count += ft_putnchar('0', (list.width - list.precision));
	else if (!list.minus && list.width > list.precision)
		count += ft_putnchar(' ', (list.width - list.precision));
	count += ft_putnstr(ft_sharp(list), 2 * (list.sharp && !list.zero && n));
	count += ft_putnchar('0', (list.precision - len));
	if (len)
		count += ft_recursive_hex(list, n, n);
	if (list.minus && list.width > list.precision)
		count += ft_putnchar(' ', list.width - list.precision);
	return (count);
}