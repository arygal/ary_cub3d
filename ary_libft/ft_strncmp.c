/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 14:27:58 by megen             #+#    #+#             */
/*   Updated: 2020/11/13 14:28:00 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t ct;

	ct = 0;
	if (n == 0)
		return (0);
	while (*s1 && (*s1 == *s2) && ct < n - 1)
	{
		s1++;
		s2++;
		ct++;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}
