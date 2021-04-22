#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	b;

	b = 0;
	if (n < 0)
	{
		write(fd, "-", 1);
		n = (n + 1) * -1;
		b = n;
		b++;
	}
	else if (n >= 0)
		b = n;
	if ((b / 10) > 0)
		ft_putnbr_fd(b / 10, fd);
	n = (b % 10 + '0');
	write(fd, &n, 1);
}
