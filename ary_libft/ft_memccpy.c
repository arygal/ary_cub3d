/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 17:40:50 by megen             #+#    #+#             */
/*   Updated: 2020/10/31 17:40:52 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				ct;
	unsigned	char	*cstsrc;
	unsigned	char	*cstdst;

	cstsrc = (unsigned char*)src;
	cstdst = (unsigned char*)dst;
	ct = 0;
	while (ct < n)
	{
		cstdst[ct] = cstsrc[ct];
		if (cstsrc[ct] == (unsigned char)c)
			return (&dst[ct + 1]);
		ct++;
	}
	return ((void *)0);
}
