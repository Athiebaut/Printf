/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_decimal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:52:59 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/12 13:53:02 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

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

static long int	str_size(int nb)
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

char	*ft_itoa(int n)
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

void	ft_print_decimal(int nb)
{
	char	*num;
	int	size;

	num = itoa(nb);
}
