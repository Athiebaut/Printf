/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:48:34 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:49:37 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

static int	ptr_size(uintptr_t nb)
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

static void	ft_put_ptr(uintptr_t nb)
{
	if (nb >= 16)
	{
		ft_put_ptr(nb / 16);
		ft_put_ptr(nb % 16);
	}
	else
	{
		if (nb <= 9)
			ft_put_char(nb + '0');
		else
			ft_put_char(nb - 10 + 'a');
	}
}

int	ft_print_ptr(uintptr_t ptr)
{
	int	printed;

	printed = 0;
	if (ptr == 0)
		printed = printed + ft_put_str("(nil)");
	else
	{
		printed = printed + write(1, "0x", 2);
		ft_put_ptr(ptr);
		printed = printed + ptr_size(ptr);
	}
	return (printed);
}
