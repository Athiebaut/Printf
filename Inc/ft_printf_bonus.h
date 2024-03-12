/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:38 by athiebau          #+#    #+#             */
/*   Updated: 2024/03/12 03:09:29 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define SPECIFIERS      "cspdiuxX%"

/*-------------------------------------------*/
/*                     LIB                   */
/*-------------------------------------------*/

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <stdbool.h> 
# include "../Libft/libft.h"

/*-------------------------------------------*/
/*                 STRUCTURE                 */
/*-------------------------------------------*/

typedef struct s_print                       
{                        
      char  specifier;
      int   minus;
      int   zero;
      int   width;
      int   plus;
      int   space;
      int   sharp;
      int   dot;
      int   precision;
      bool  sign;                        
}    t_print;

/*-------------------------------------------*/
/*                    FILES                  */
/*-------------------------------------------*/

int	ft_parse(char *arg, va_list args);

int	ft_convert(va_list args, t_print list);

int	ft_putnchar(char c, int size);
int	ft_print_str(t_print list, va_list ap);
int	ft_print_char(t_print list, va_list ap);

#endif
