/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_func_head.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:04:09 by megen             #+#    #+#             */
/*   Updated: 2021/03/16 22:42:30 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(const char *s)
{
	size_t a;

	a = 0;
	while (s[a] != '\0')
		a++;
	return (a);
}

static	size_t	ft_split_wctandpos(char const *s, char c, size_t nc)
{
	size_t	wct;
	size_t	pos;

	pos = 0;
	wct = 1;
	if (*s == '\0')
		return (0);
	while (*s != '\0')
	{
		if (*s != '\0' && pos > 0)
			wct++;
		while (*s != c && *s != '\0')
		{
			s++;
			pos++;
		}
		while (*s == c && *s != '\0')
		{
			s++;
			pos++;
		}
		if (nc > 0 && nc == wct)
			return (pos);
	}
	return (wct);
}

char	**ft_split_free(char **ret)
{
	size_t	ct;

	ct = 0;
	while (ret[ct])
		free(ret[ct++]);
	free(ret);
	return ((void *)0);
}

static	char	*ft_split_filler(char const *s, char c, size_t nc)
{
	size_t	pos;
	size_t	size;
	char	*ret;

	if (nc == 0)
		pos = 0;
	else
		pos = ft_split_wctandpos(s, c, nc);
	s = s + pos;
	size = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		size++;
	}
	if (!(ret = (char *)ft_calloc(size + 1, sizeof(char))))
		return ((void *)0);
	pos = 0;
	s = s - size;
	while (size > pos)
	{
		ret[pos++] = *s;
		s++;
	}
	return (ret);
}

char			**ft_split(char const *s, char c)
{
	size_t	wct;
	size_t	nc;
	char	**ret;

	if (!s)
		return ((void *)0);
	while (*s == c && c != '\0')
		s++;
	nc = 0;
	wct = ft_split_wctandpos(s, c, nc);
	ret = (char **)malloc((wct + 1) * sizeof(char **));
	if (!ret)
		return ((void *)0);
	while (nc < wct)
	{
		ret[nc] = ft_split_filler(s, c, nc);
		if (!ret[nc])
			return (ft_split_free(ret));
		nc++;
	}
	ret[nc] = (void *)0;
	return (ret);
}