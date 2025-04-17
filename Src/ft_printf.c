/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <athiebau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:10 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/24 17:27:37 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/ft_printf.h"

int	ft_convert(va_list args, t_print list)
{
	int	printed;

	printed = 0;
	if (list.specifier == 'c' || list.specifier == '%')
		printed += ft_print_char(list, args);
	else if (list.specifier == 's')
		printed += ft_print_str(list, args);
	else if ((list.specifier == 'd') || (list.specifier == 'i'))
		printed = printed + ft_print_d_i_u(list, args);
	else if (list.specifier == 'u')
		printed = printed + ft_print_d_i_u(list, args);
	else if (list.specifier == 'p')
		printed = printed + ft_print_ptr(list, args);
	else if ((list.specifier == 'x') || (list.specifier == 'X'))
		printed = printed + ft_print_hexa(list, args);
	return (printed);
}

int	ft_printf(const char *arg, ...)
{
	int		printed;
	va_list	args;

	printed = 0;
	if (!arg)
		return (-1);
	va_start (args, arg);
	while (*arg)
	{
		if (*arg == '%')
		{
			if (*(++arg))
				printed += ft_parse((char *)arg, args);
			while (*arg && !ft_strchr(SPECIFIERS, *arg))
				arg++;
		}
		else
			printed += ft_putnchar(*arg, 1);
		if (*arg)
			arg++;
	}
	va_end(args);
	return (printed);
}

// int main()
// {
// 	char ch = 'A';
// 	printf("char c :\n");
// 	printf("-----------------------\n");
// 	ft_printf("|%-6c|\n", ch);
// 	printf("|%-6c|\n", ch);
// 	ft_printf("|%4c|\n", ch);
// 	printf("|%4c|\n", ch); 
// 	printf("-----------------------\n");
// 	char str[] = "Hello World";
// 	printf("string s :\n");
// 	printf("-----------------------\n");
// 	ft_printf("|%s|\n", str);
// 	printf("|%s|\n", str);
// 	ft_printf("|%15s|\n", str);
// 	printf("|%15s|\n", str);
// 	ft_printf("|%-15s|\n", str);
// 	printf("|%-15s|\n", str);
// 	ft_printf("|%-15.3s|\n", str);
// 	printf("|%-15.3s|\n", str);
// 	ft_printf("|%15.3s|\n", str);
// 	printf("|%15.3s|\n", str);
// 	printf("-----------------------\n");

// 	int *ptr = NULL;
// 	char *str2 = "oui";
// 	printf("pointeur p :\n");
// 	printf("-----------------------\n");
// 	ft_printf("|%p|\n", ptr);      
// 	printf("|%p|\n", ptr); 
// 	ft_printf("|%p|\n", str2);      
// 	printf("|%p|\n", str2); 
// 	ft_printf("|%20p|\n", str2);      
// 	printf("|%20p|\n", str2); 
// 	ft_printf("|%-20p|\n", str2);      
// 	printf("|%-20p|\n", str2); 
// 	printf("-----------------------\n");

// 	int num = -424242;
// 	printf("integer d/i :\n");
// 	printf("-----------------------\n");
// 	ft_printf("|%+d|\n", num);
// 	printf("|%+d|\n", num);
// 	ft_printf("|%+d|\n", -num);
// 	printf("|%+d|\n", -num);
// 	ft_printf("|%0+10d|\n", num);
// 	printf("|%0+10d|\n", num);
// 	ft_printf("|%-10i|\n", num);
// 	printf("|%-10i|\n", num);
// 	ft_printf("|%10i|\n", num);
// 	printf("|%10i|\n", num);
// 	printf("-----------------------\n");
// 	unsigned int num2 = 123;
// 	printf("unsigned integer u :\n");
// 	printf("-----------------------\n");
// 	ft_printf("|%u|\n", num2); 
// 	printf("|%u|\n", num2);     
// 	ft_printf("|%05u|\n", num2); 
// 	printf("|%05u|\n", num2); 
// 	ft_printf("|%08.10u|\n", num2); 
// 	printf("|%08.10u|\n", num2);   
// 	ft_printf("|%-10.2u|\n", num2); 
// 	printf("|%-10.2u|\n", num2);
// 	printf("-----------------------\n");

// 	unsigned int hex = 255;
// 	printf("unsigned hex x/X :\n");
// 	printf("-----------------------\n");
// 	ft_printf("|%x|\n", hex);
// 	printf("|%x|\n", hex);
// 	ft_printf("|%X|\n", hex);
// 	printf("|%X|\n", hex);
// 	ft_printf("|%#x|\n", hex);
// 	printf("|%#x|\n", hex);
// 	ft_printf("|%-#6X|\n", hex);
// 	printf("|%-#6X|\n", hex);
// 	ft_printf("|%#6X|\n", hex);
// 	printf("|%#6X|\n", hex);
// 	ft_printf("|%#010x|\n", hex);
// 	printf("|%#010x|\n", hex);
// }