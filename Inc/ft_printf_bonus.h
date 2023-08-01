/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:38 by athiebau          #+#    #+#             */
/*   Updated: 2023/08/01 18:54:30 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include "../Libft/libft.h"

typedef struct s_print                       
{                        
      char  specifier;              
      int   width;            
      int   precision;
      int   minus;           
      int   zero;         
      int   dot;
      int   sharp; 
      int   space;            
      int   plus;            
      int   sign;                        
}    t_print;

# define SPECIFIERS      "cspdiuxX%"

int	ft_print_int_signed(int nb);
int	ft_print_int_unsigned(unsigned int nb);
int	ft_putstr(char *str);
int	ft_putchar(int c);
int	ft_printf(const char *arg, ...);
int	ft_print_ptr(uintptr_t ptr);
int	ft_print_hexadecimal(unsigned int nb, const char arg);

void	ft_initialize(t_print *list);
#endif
