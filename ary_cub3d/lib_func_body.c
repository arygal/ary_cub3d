/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func_body.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:35:41 by megen             #+#    #+#             */
/*   Updated: 2021/03/17 22:50:49 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *str;

	str = b;
	while (len)
	{
		*str = (unsigned char)c;
		len--;
		str++;
	}
	return (b);
}

void			*ft_calloc(size_t count, size_t size)
{
	unsigned long long	sum;
	void				*ptr;

	sum = count * size;
	ptr = (void *)malloc(sum);
	if (ptr)
		ft_memset(ptr, '\0', sum);
	return (ptr);
}

int		ft_atoi(const char *str)
{
	int ct;
	int val;
	int ret;

	val = 1;
	ct = 0;
	ret = 0;
	while (str[ct] == ' ' || str[ct] == '\n' || str[ct] == '\r' ||
			str[ct] == '\f' || str[ct] == '\v' || str[ct] == '\t')
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
