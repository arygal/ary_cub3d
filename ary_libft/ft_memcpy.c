#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned long int		ct;
	const unsigned char		*cstsrc = src;
	unsigned char			*cstdst;

	if (dst == src)
		return (dst);
	cstdst = dst;
	ct = 0;
	while (ct < n)
	{
		cstdst[ct] = cstsrc[ct];
		ct++;
	}
	return (dst);
}
