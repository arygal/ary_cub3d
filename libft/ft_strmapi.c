#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	len;
	unsigned int	ct;

	if (!s || !f)
		return ((void *)0);
	len = ft_strlen(s);
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return ((void *)0);
	ct = 0;
	while (ct < len)
	{
		ret[ct] = f(ct, s[ct]);
		ct++;
	}
	return (ret);
}
