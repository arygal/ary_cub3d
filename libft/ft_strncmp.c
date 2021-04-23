#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	ct;

	ct = 0;
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && ct < n - 1)
	{
		s1++;
		s2++;
		ct++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
