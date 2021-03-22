/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 18:17:21 by megen             #+#    #+#             */
/*   Updated: 2020/11/01 18:17:26 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t ct;

	ct = 0;
	if (dst == (void *)0)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	while (src[ct] != '\0' && ct < dstsize - 1)
	{
		dst[ct] = src[ct];
		ct++;
	}
	if (ct < dstsize)
		dst[ct] = '\0';
	while (src[ct] != '\0')
		ct++;
	return (ct);
}
