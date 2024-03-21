/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 23:58:56 by alix              #+#    #+#             */
/*   Updated: 2024/03/21 04:48:57 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

static char	*ft_sharp(t_print list)
{
	if (list.specifier == 'X')
		return ("0X");
	return ("0x");
}

int	ft_print_hexa(t_print l, va_list args)
{
	int				count;
	unsigned int	n;
	int				len;

	count = 0;
	n = va_arg(args, unsigned int);
	len = ft_nbrlen(n, 16);
	if (!n && !l.precision && l.dot)
		len = 0;
	if (l.precision < 0 || l.precision < len || !l.dot)
		l.precision = len;
	if (l.sharp && n)
		l.width -= 2;
	count += ft_putnstr(ft_sharp(l), 2 * (l.sharp && l.zero && n));
	if (!l.minus && l.width > l.precision && (!l.dot || l.sign) && l.zero)
		count += ft_putnchar('0', (l.width - l.precision));
	else if (!l.minus && l.width > l.precision)
		count += ft_putnchar(' ', (l.width - l.precision));
	count += ft_putnstr(ft_sharp(l), 2 * (l.sharp && !l.zero && n));
	count += ft_putnchar('0', (l.precision - len));
	if (len)
		count += ft_recursive_hex(l, n, n);
	if (l.minus && l.width > l.precision)
		count += ft_putnchar(' ', l.width - l.precision);
	return (count);
}
