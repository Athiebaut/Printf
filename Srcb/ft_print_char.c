/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:49:44 by alix              #+#    #+#             */
/*   Updated: 2024/03/21 04:48:57 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

int	ft_putnchar(char c, int size)
{
	int	count;

	count = 0;
	while (size-- > 0)
		count += (int)write(1, &c, 1);
	return (count);
}

int	ft_print_char(t_print list, va_list args)
{
	char	c;
	int		count;

	count = 0;
	if (list.specifier == 'c')
		c = va_arg(args, int);
	else
		c = '%';
	list.precision = 1;
	if (!list.minus && list.zero)
		count += ft_putnchar('0', list.width - list.precision);
	else if (!list.minus && list.width > list.precision)
		count += ft_putnchar(' ', list.width - list.precision);
	count += ft_putnchar(c, 1);
	if (list.minus && list.width - list.precision > 0)
		count += ft_putnchar(' ', list.width - list.precision);
	return (count);
}
