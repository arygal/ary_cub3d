/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:10:39 by megen             #+#    #+#             */
/*   Updated: 2020/11/26 15:10:40 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	char	*ft_itoa_charset(char *ret, long int nclone, int size)
{
	while (size >= 0)
	{
		ret[size--] = nclone % 10 + 48;
		nclone = nclone / 10;
	}
	return (ret);
}

char			*ft_itoa(int n)
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
	if (!(ret = (char *)ft_calloc(size + 1, sizeof(char))))
		return ((void *)0);
	nclone = n;
	if (nclone < 0)
	{
		nclone = nclone * -1;
		ret = ft_itoa_charset(ret, nclone, size - 1);
		ret[0] = 45;
	}
	else
		ret = ft_itoa_charset(ret, nclone, size - 1);
	return (ret);
}
