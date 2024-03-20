/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:50:51 by alix              #+#    #+#             */
/*   Updated: 2024/03/20 23:23:11 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

int	ft_putnstr(char *str, int size)
{
	if (str)
		return ((int)write(1, str, size));
	return (0);
}

int	ft_print_str(t_print list, va_list args)
{
	char	*string;
	int		count;
	int		has_malloc;

	count = 0;
	has_malloc = 0;
	string = va_arg(args, char *);
	if (!string)
	{
		string = malloc(sizeof(char) * 7);
		has_malloc = 1;
		ft_strlcpy(string, "(null)", 7);
	}
	if (!list.dot || list.precision > (int)ft_strlen(string) || list.precision < 0)
		list.precision = ft_strlen(string);
	if (!list.minus && list.width > list.precision && list.zero && (!list.dot || list.sign))
		count += ft_putnchar('0', list.width - list.precision);
	else if (!list.minus && list.width - list.precision > 0)
		count += ft_putnchar(' ', list.width - list.precision);
	count += ft_putnstr(string, list.precision);
	if (list.minus && list.width - list.precision > 0)
		count += ft_putnchar(' ', list.width - list.precision);
	if (has_malloc)
		free(string);
	return (count);
}