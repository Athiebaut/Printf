/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbrs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:28 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/21 03:04:26 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

// static int	ft_strlen2(char *str)
// {
// 	int	i;

// 	i = 0;
// 	if (str[i] == '+' || str[i] == '-')
// 		str++;
// 	while(str[i])
// 		i++;
// 	return (i);
// }

static char	plus(t_print list)
{
	if (list.plus)
		return ('+');
	return ('-');
}

static int	ft_print_nbr(t_print list, char *nbr, int len, int neg)
{
	int	c;

	c = 0;
	list.width -= (list.space && !neg && !list.plus && list.width);
	if (neg || list.plus)
		c += ft_putnchar(plus(list), list.zero && (!list.dot || list.sign));
	else if (list.space)
		c += ft_putnchar(' ', list.zero && !list.dot);
	if (!list.minus && list.width > list.precision && (!list.dot || list.sign)
		&& list.zero)
		c += ft_putnchar('0', list.width - list.precision - neg - list.plus);
	else if (!list.minus && list.width > list.precision)
		c += ft_putnchar(' ', list.width - list.precision - neg - list.plus);
	if (neg || list.plus)
		c += ft_putnchar(plus(list), !list.zero || (list.dot && !list.sign));
	else if (list.space)
		c += ft_putnchar(' ', !list.zero || list.dot);
	c += ft_putnchar('0', list.precision - len);
	c += write(1, nbr, len);
	if (list.minus && list.width > list.precision)
		c += ft_putnchar(' ', list.width - list.precision - neg - list.plus);
	return (c);
}

int	ft_print_d_i_u(t_print list, va_list ap)
{
	char		*nbr;
	long long	n;
	int			c;
	int			len;
	int			neg;

	c = 0;
	n = va_arg(ap, int);
	neg = (n < 0 && n >= INT_MIN && list.specifier != 'u');
	if (neg)
		list.plus = 0;
	if (n < 0 && list.specifier != 'u')
		n *= -1;
	if (n < 0 && list.specifier == 'u')
		nbr = ft_uitoa(n);
	else
		nbr = ft_itoa(n);
	len = ft_strlen(nbr);
	if (*nbr == '0' && !list.precision && list.dot)
		len = 0;
	if (list.precision < len || !list.dot)
		list.precision = len;
	c += ft_print_nbr(list, nbr, len, neg);
	free(nbr);
	return (c);
}
