/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:19:10 by megen             #+#    #+#             */
/*   Updated: 2021/03/31 18:14:42 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		i_free(void *line)
{
	free(line);
	return(0);
}

/* it is free but it returns 0  */

int		split_free(char **ret)
{
	size_t	ct;

	ct = 0;
	while (ret[ct])
		free(ret[ct++]);
	free(ret);
	return (0);
}

/* free for (char **)  */

int	i_strcmp(char *line1, char *line2)
{
	while (*line1)
	{
		if (*line1 != *line2)
			return(0);
		++line1;
		++line2;
	}
	if (*line1 != '\0' || *line2 != '\0')
		return(0);
	return(1);
}

/* compares line1 and line2  1 if they are same */


int clear_atoui(char *line)
{
	int ret;
	
	ret = 0;
	while (*line != '\0')
	{
		if (*line >= '0' && *line <= '9')
			ret = ret * 10 + (*line - '0');
		else
			return(-1);
		++line;
	}
	return(ret);
}

/* atoi onli for positive int and if it found not num char - it return -1 */

int arr_len(char **arr)
{
	int	ct;
	
	ct = 0;
	while (arr[ct] != NULL)
		++ct;
	return(ct);
}