#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*cstsrc;
	unsigned char	chr;
	size_t			ct;

	ct = 0;
	cstsrc = (unsigned char *)s;
	chr = c;
	while (n > 0)
	{
		n--;
		if (cstsrc[ct] == chr)
			return ((void *)&cstsrc[ct]);
		ct++;
	}
	return ((void *)0);
}
