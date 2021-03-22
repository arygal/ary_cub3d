/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 19:00:39 by megen             #+#    #+#             */
/*   Updated: 2020/11/01 19:00:43 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static		size_t	ft_strlen_ct(const char *s, size_t ct)
{
	size_t a;

	a = 0;
	while (a < ct)
	{
		if (!*s)
			break ;
		s++;
		a++;
	}
	return (a);
}

size_t				ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t ds;
	size_t sr;

	sr = ft_strlen(src);
	ds = ft_strlen_ct(dst, dstsize);
	if (ds == dstsize)
		return (dstsize + sr);
	if (sr < dstsize - ds)
		ft_memcpy(dst + ds, src, sr + 1);
	else
	{
		ft_memcpy(dst + ds, src, dstsize - ds - 1);
		dst[dstsize - 1] = '\0';
	}
	return (ds + sr);
}
