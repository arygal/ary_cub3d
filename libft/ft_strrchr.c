#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		ct;
	char	*cts;

	cts = (char *)s;
	ct = 0;
	if (c == '\0')
		return (cts + ft_strlen(s));
	while (*s)
	{
		if (*s == c)
			ct++;
		s++;
	}
	if (ct == 0)
		return ((void *)0);
	while (*cts)
	{
		if (*cts == c)
			ct--;
		if (ct == 0)
			return (cts);
		cts++;
	}
	return ((void *)0);
}
