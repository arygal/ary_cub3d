/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:29:06 by megen             #+#    #+#             */
/*   Updated: 2021/04/20 18:05:59 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		texture_list_name_check(t_set *set, char *name)
{
	t_texture	*temp;

	temp = set->textures.head;
	while (temp != NULL)
	{
		if (i_strcmp(temp->name, name))
			return(false);
		temp = temp->next;
	}
	return(true);
}

/* true  if name is unique in list*/

int free_set(t_set *set)
{
	if (set->textures.head != NULL)
		free_textures_list(set);
	if (set->m != NULL)
		split_free(set->m);
	free(set->textures.index);
	// free(set->textures.mlx);
	return(0);
}

t_texture		*texture_find(t_set *set, char *name)
{
	t_texture	*temp;

	temp = set->textures.head;
	while (temp != NULL)
	{
		if (i_strcmp(temp->name, name))
			return(temp);
		temp = temp->next;
	}
	return(NULL);
}

int			trgb(int t , int r, int g, int b)
{
	return(t << 24| r << 16 | g << 8 | b);
}
