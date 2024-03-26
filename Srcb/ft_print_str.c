/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:50:51 by alix              #+#    #+#             */
/*   Updated: 2024/03/26 23:50:36 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

int	ft_putnstr(char *str, int size)
{
	if (str)
		return ((int)write(1, str, size));
	return (0);
}

static	int	if_string_null(t_print list, char **string, int *has_malloc)
{
	if (((list.precision < 6 && list.precision > 0) && !list.width))
		return (0);
	*string = malloc(sizeof(char) * 7);
	*has_malloc = 1;
	ft_strlcpy(*string, "(null)", 7);
	return (1);
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
		if (!if_string_null(list, &string, &has_malloc))
			return (0);
	if (!list.dot || list.precision > (int)ft_strlen(string)
		|| list.precision < 0)
		list.precision = ft_strlen(string);
	if (!list.minus && list.width > list.precision && list.zero && (!list.dot
			|| list.sign))
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
