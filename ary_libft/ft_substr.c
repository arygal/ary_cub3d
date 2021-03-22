/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 18:56:16 by megen             #+#    #+#             */
/*   Updated: 2020/11/15 18:56:18 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	ct;
	size_t	slen;

	if (!s)
		return ((void *)0);
	slen = ft_strlen(s);
	if (slen < start)
		return (ret = (char *)ft_calloc(1, 1));
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	if (!ret)
		return ((void *)0);
	ct = 0;
	while (ct < len)
		ret[ct++] = s[start++];
	return (ret);
}
