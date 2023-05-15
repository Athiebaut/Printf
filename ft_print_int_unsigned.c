/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_unsigned.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:47 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/15 11:51:49 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	str_size(unsigned int nb)
{
	int	size;

	size = 0;
	if (nb <= 0)
		size = 1;
	while (nb != 0)
	{
		size++;
		nb = nb / 10;
	}
	return (size);
}

static char	*ft_itoa(unsigned int n)
{
	char			*str;
	long int		size;

	size = str_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size = size - 1;
	if (n == 0)
		str[0] = '0';
	else
	{
		while (n > 0)
		{
			str[size] = 48 + (n % 10);
			n = n / 10;
			size--;
		}
	}
	return (str);
}

int	ft_print_int_unsigned(unsigned int nb)
{
	char	*num;
	int		size;

	num = ft_itoa(nb);
	size = ft_putstr(num);
	free(num);
	return (size);
}
