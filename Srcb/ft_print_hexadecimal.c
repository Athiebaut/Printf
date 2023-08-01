/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexadecimal.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:20 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/15 11:51:22 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	number_size(unsigned int nb)
{
	int	size;

	size = 0;
	while (nb != 0)
	{
		size++;
		nb = nb / 16;
	}
	return (size);
}

static void	ft_put_hex(unsigned int nb, const char arg)
{
	if (nb >= 16)
	{
		ft_put_hex(nb / 16, arg);
		ft_put_hex(nb % 16, arg);
	}
	else if (arg == 'x')
	{
		if (nb <= 9)
			ft_putchar(nb + '0');
		else
			ft_putchar(nb - 10 + 'a');
	}
	else if (arg == 'X')
	{
		if (nb <= 9)
			ft_putchar(nb + '0');
		else
			ft_putchar(nb - 10 + 'A');
	}
}

int	ft_print_hexadecimal(unsigned int nb, const char arg)
{
	if (nb == 0)
		return (write(1, "0", 1));
	else
		ft_put_hex(nb, arg);
	return (number_size(nb));
}
