/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athiebau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:38 by athiebau          #+#    #+#             */
/*   Updated: 2023/05/15 11:51:40 by athiebau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>

typedef struct s_print                       
{                        
      va_list  args;    // arg to print out                    
      int   wdt;        // width                
      int   prc;        // precision              
      int   zero;       // zero padding               
      int   point;        // .     
      int   dash;       // -               
      int   tl;         // total_length (return value)              
      int   sign;       // pos or neg number               
      int   is_zero;    // is number zero                 
      int   perc;       // %               
      int   sp;         // space flag ' '            
}    t_print;

int	ft_print_int_signed(int nb);
int	ft_print_int_unsigned(unsigned int nb);
int	ft_putstr(char *str);
int	ft_putchar(int c);
int	ft_printf(const char *arg, ...);
int	ft_print_ptr(uintptr_t ptr);
int	ft_print_hexadecimal(unsigned int nb, const char arg);

void	ft_initialize(t_print *list);
#endif
