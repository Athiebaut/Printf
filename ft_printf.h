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

int	ft_print_int_signed(int nb);
int	ft_print_int_unsigned(unsigned int nb);
int	ft_putstr(char *str);
int	ft_putchar(int c);
int	ft_printf(const char *arg, ...);
int	ft_print_ptr(uintptr_t ptr);
int	ft_print_hexadecimal(unsigned int nb, const char arg);

#endif
