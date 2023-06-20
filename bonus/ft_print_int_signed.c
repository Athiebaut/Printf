/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int_signed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:28 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/15 11:51:31 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_char(char *str, unsigned int nb, long int size)
{
	while (nb > 0)
	{
		str[size] = 48 + (nb % 10);
		nb = nb / 10;
		size--;
	}
	return (str);
}

static int	str_size(int nb)
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

static char	*ft_itoa(int n)
{
	char			*str;
	long int		size;
	unsigned int	nb;

	size = str_size(n);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	size = size - 1;
	if (n == 0)
		str[0] = '0';
	if (n < 0)
	{
		nb = n * -1;
		str[0] = '-';
	}
	else
		nb = n;
	str = ft_char(str, nb, size);
	return (str);
}

int	ft_print_int_signed(int nb)
{
	char	*num;
	int		size;

	num = ft_itoa(nb);
	size = ft_putstr(num);
	free(num);
	return (size);
}
