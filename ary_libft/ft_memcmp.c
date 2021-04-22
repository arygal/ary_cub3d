#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*st1;
	unsigned char	*st2;
	size_t			ct;

	st1 = (unsigned char *)s1;
	st2 = (unsigned char *)s2;
	ct = 0;
	while (ct < n)
	{
		if (*st1 != *st2)
			return (*(unsigned char *)st1 - *(unsigned char *)st2);
		st1++;
		st2++;
		ct++;
	}
	return (0);
}
