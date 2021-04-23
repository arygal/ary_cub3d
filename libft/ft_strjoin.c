#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	a;
	size_t	b;
	size_t	ct;
	char	*ret;

	if (!s1 && !s2)
		return ((void *)0);
	if (!s2)
		return (ret = ft_strdup(s1));
	if (!s1)
		return (ret = ft_strdup(s2));
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	ret = (char *)ft_calloc(a + b + 1, sizeof(char));
	if (!ret)
		return ((void *)0);
	ct = -1;
	while (++ct < a)
		ret[ct] = s1[ct];
	ct = -1;
	while (++ct < b)
		ret[a + ct] = s2[ct];
	return (ret);
}
