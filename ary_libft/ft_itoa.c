#include "libft.h"

static	char	*ft_itoa_charset(char *ret, long int nclone, int size, int spec)
{
	while (size >= 0)
	{
		ret[size--] = nclone % 10 + 48;
		nclone = nclone / 10;
	}
	if (spec == 1)
		ret[0] = 45;
	return (ret);
}

char	*ft_itoa(int n)
{
	long int	nclone;
	int			size;
	char		*ret;

	nclone = n;
	size = 0;
	while (nclone != 0)
	{
		nclone = nclone / 10;
		size++;
	}
	if (n <= 0)
		size++;
	ret = (char *)ft_calloc(size + 1, sizeof(char));
	if (!ret)
		return ((void *)0);
	nclone = n;
	if (nclone < 0)
	{
		nclone = nclone * -1;
		ret = ft_itoa_charset(ret, nclone, size - 1, 1);
	}
	else
		ret = ft_itoa_charset(ret, nclone, size - 1, 0);
	return (ret);
}
