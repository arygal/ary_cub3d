#include "libft.h"

int	ft_atoi(const char *str)
{
	int	ct;
	int	val;
	int	ret;

	val = 1;
	ct = 0;
	ret = 0;
	while (str[ct] == ' ' || str[ct] == '\n' || str[ct] == '\r'
		|| str[ct] == '\f' || str[ct] == '\v' || str[ct] == '\t')
		ct++;
	if (str[ct] == '-')
	{
		ct++;
		val = -1;
	}
	else if (str[ct] == '+')
		ct++;
	while (str[ct] > 47 && str[ct] < 58)
	{
		ret = ret * 10 + str[ct] - '0';
		ct++;
	}
	return (ret * val);
}
