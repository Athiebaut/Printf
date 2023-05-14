
#ifndef FT_PRINTF_H
#define FT_PRINTF_H
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int	ft_print_int_signed(int nb);
int	ft_print_int_unsigned(unsigned int nb);
int	ft_putstr(char *str);
int	ft_putchar(int c);
int	ft_printf(const char *arg, ...);

#endif