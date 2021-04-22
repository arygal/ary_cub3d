#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		ct;
	const char	*cstsrc = src;
	char		*cstdst;

	if (dst == src)
		return (dst);
	cstdst = dst;
	ct = 0;
	if (src < dst)
	{
		while (len > 0)
		{
			len--;
			cstdst[len] = cstsrc[len];
		}
	}
	else
	{
		while (ct < len)
		{
			cstdst[ct] = cstsrc[ct];
			ct++;
		}
	}
	return (dst);
}
