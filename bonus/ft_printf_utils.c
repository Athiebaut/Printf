#include "ft_printf.h"

void	ft_initialize(t_print *list)
{
	list->wdt = 0;
	list->prc = 0;
	list->zero = 0;
	list->point = 0;
	list->dash = 0;
	list->tl = 0;
	list->sign = 0;
	list->is_zero = 0;
	list->perc = 0;
	list->sp = 0;
}