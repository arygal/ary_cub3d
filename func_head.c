/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_head.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 21:19:10 by megen             #+#    #+#             */
/*   Updated: 2021/03/18 19:59:09 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		revstrchr(char *line, char* specifier)
{
	int ct;
	int	i;

	ct = 0;
	while(line[ct] != '\0')
		{
			i = -1;
			while (specifier[++i] != '\0')
				if (specifier[i] == line[ct])
					break;
			if (specifier[i] == '\0')
				return(0);
			++ct;
		}
	return(1);
}

/* 0 if wrong char in line   ||  1 if line is only from specifier */