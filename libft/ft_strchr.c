#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != c)
	{
		if (!*s)
			return ((void *)0);
		s++;
	}
	return ((char *)s);
}
