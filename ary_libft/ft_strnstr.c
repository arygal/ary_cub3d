/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:04:21 by megen             #+#    #+#             */
/*   Updated: 2020/11/04 18:04:23 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *haystack, const char *needle,
				size_t len)
{
	size_t	szn;

	if (!*needle)
		return ((char *)haystack);
	szn = ft_strlen(needle);
	while (*haystack && len >= szn)
	{
		len--;
		if (ft_strncmp(haystack, needle, szn) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return ((void *)0);
}
