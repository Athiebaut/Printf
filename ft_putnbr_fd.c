
#include "printf.h"

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nbr;

	nbr = nb;
	if (nbr < 0)
	{
		ft_putchar_fd('-', fd);
		nbr = -nb;
	}
	if (nbr > 9)
		ft_putnbr_fd(nbr / 10, fd);
	ft_putchar(nbr % 10 - 48, fd);
}