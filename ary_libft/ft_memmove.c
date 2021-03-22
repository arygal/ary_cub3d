/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 18:54:24 by megen             #+#    #+#             */
/*   Updated: 2020/10/31 18:54:26 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		ct;
	const char	*cstsrc = src;
	char		*cstdst;

	if (dst == src)
		return (dst);
	cstdst = dst;
	ct = 0;
	if (src < dst)
	{
		while (len > 0)
		{
			len--;
			cstdst[len] = cstsrc[len];
		}
	}
	else
	{
		while (ct < len)
		{
			cstdst[ct] = cstsrc[ct];
			ct++;
		}
	}
	return (dst);
}
