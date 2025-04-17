/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alix <alix@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 11:51:38 by athiebau          #+#    #+#             */
/*   Updated: 2025/04/18 01:32:20 by alix             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# define SPECIFIERS      "cspdiuxX%"
# define HEXA_LOW	"0123456789abcdef"
# define HEXA_UP	"0123456789ABCDEF"

/*-------------------------------------------*/
/*                     LIB                   */
/*-------------------------------------------*/

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <stdio.h>
# include <stdbool.h> 
# include "../Libft/libft.h"

/*-------------------------------------------*/
/*                 STRUCTURE                 */
/*-------------------------------------------*/

typedef struct s_print
{
	char	specifier;
	int		minus;
	int		zero;
	int		width;
	int		plus;
	int		space;
	int		sharp;
	int		dot;
	int		precision;
	bool	sign;
}	t_print;

/*-------------------------------------------*/
/*                    FILES                  */
/*-------------------------------------------*/

int	ft_printf(const char *arg, ...);
int	ft_convert(va_list args, t_print list);

int	ft_parse(char *arg, va_list args);

int	ft_putnchar(char c, int size);
int	ft_print_char(t_print list, va_list ap);

int	ft_putnstr(char *str, int size);
int	ft_print_str(t_print list, va_list ap);

int	ft_print_d_i_u(t_print list, va_list ap);

int	ft_recursive_hex(t_print list, size_t n, size_t iteration);
int	ft_print_ptr(t_print list, va_list args);

int	ft_print_hexa(t_print list, va_list args);

char	*ft_uitoa(unsigned int n);
int	ft_nbrlen(long n, int base);
#endif
