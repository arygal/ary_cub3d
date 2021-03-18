/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func_tail.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:11:55 by megen             #+#    #+#             */
/*   Updated: 2021/03/17 20:24:58 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			*ft_strdup(const char *s1)
{
	int		lenchar;
	char	*malchar;

	lenchar = ft_strlen(s1);
	malchar = (char *)malloc(sizeof(char) * lenchar + 1);
	if (malchar == (void *)0)
		return (malchar);
	while (lenchar >= 0)
	{
		malchar[lenchar] = s1[lenchar];
		--lenchar;
	}
	return (malchar);
}


static	size_t	ft_strtrim_chk(char s, char const *set)
{
	while (*set)
	{
		if (*set == s)
			return (1);
		set++;
	}
	return (0);
}

static	size_t	ft_strtrim_fr(char const *s1, char const *set)
{
	size_t	ret;

	ret = 0;
	while (*s1)
	{
		if (ft_strtrim_chk(*s1, set) == 1)
			ret++;
		else
			return (ret);
		s1++;
	}
	return (ret);
}

static	size_t	ft_strtrim_bk(char const *s1, char const *set)
{
	size_t ret;
	size_t ct1;

	ct1 = ft_strlen(s1) - 1;
	ret = 0;
	while (ct1 > 0)
	{
		if (ft_strtrim_chk(s1[ct1], set) == 1)
			ret++;
		else
			return (ret);
		ct1--;
	}
	return (ret);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	fr;
	size_t	bk;
	char	*ret;
	size_t	len;
	size_t	ct;

	if (!set)
		return (ret = ft_strdup(s1));
	if (!s1)
		return ((void *)0);
	len = ft_strlen(s1);
	fr = ft_strtrim_fr(s1, set);
	if (fr == len)
		return (ret = (char *)ft_calloc(1, sizeof(char)));
	bk = ft_strtrim_bk(s1, set);
	ret = (char *)ft_calloc(len - fr - bk + 1, sizeof(char));
	if (!ret)
		return ((void *)0);
	len = len - bk;
	ct = 0;
	while (fr < len)
		ret[ct++] = s1[fr++];
	return (ret);
}