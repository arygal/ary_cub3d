/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:29:06 by megen             #+#    #+#             */
/*   Updated: 2021/03/21 20:29:25 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

bool	ft_strcmp(char *line1, char *line2)
{
	while (*line1)
	{
		if (*line1 != *line2)
			return(false);
		++line1;
		++line2;
	}
	if (*line1 != '\0' || *line2 != '\0')
		return(false);
	return(true);
}

/* compares line1 and line2< true if they are same */

bool		texture_list_name_check(t_set *set, char *name)
{
	t_texture	*temp;

	temp = set->textures.head;
	while (temp != NULL)
	{
		if (ft_strcmp(temp->name, name))
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
	if (set->map != NULL)
		split_free(set->map);
	return(0);
}
