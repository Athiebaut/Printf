/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 17:22:38 by alix              #+#    #+#             */
/*   Updated: 2023/08/01 18:58:58 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf_bonus.h"

t_print	get_width(char *arg, va_list args, t_print *list)
{
	int	specifier;

	specifier = 0;
	while (*arg != '.' && !ft_strchr(SPECIFIERS, *arg))
	{
		if (*arg == '-')
			list->minus = 1;
		if(*arg == '0' && !ft_isdigit())
	}
}

int	ft_parse(char *arg, va_list args)
{
	t_print	list;

	ft_initialize(&list);
	list = get_width(arg, args, &list);
}

