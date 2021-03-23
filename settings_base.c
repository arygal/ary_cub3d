/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 17:21:12 by megen             #+#    #+#             */
/*   Updated: 2021/03/23 17:28:47 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool basic_texrues

static bool		basic_textures_check(t_set *set)
{
	if (texture_list_name_check(set, "SO"))
		return(free_set(set));
	if (texture_list_name_check(set, "NO"))
		return(free_set(set));
	if (texture_list_name_check(set, "EA"))
		return(free_set(set));
	if (texture_list_name_check(set, "WE"))
		return(free_set(set));
	if (texture_list_name_check(set, "S"))
		return(free_set(set));
	return(true);
}


static bool get_settings_chek(t_set *set)
{
	if(set->ceiling.b == -1 || set->floor.b == -1 || set->height == -1)
		return(false);
	if(set->textures.len != 5)
		return(false);
	return(true);
}

static bool get_settings_hub (t_set *set, int fd)
{
	char *line;
	char **split;

	if (get_next_line(fd, &line) <= 0)
		return(false);
	while(*line == '\0')
		{
			free(line);
			if (get_next_line(fd, &line) <= 0)
				return(false);
		}
	split = ft_split(line , ' ');
	if (*split == NULL)
		return(i_free(line));
	free(line);
	if (split[0][0] == 'R' && split[0][1] == '\0' && set->height == -1 && split[2] != NULL)
		return (get_res(set, split));
	if (split[0][0] == 'C' && split[0][1] == '\0' && set->ceiling.b == -1 && split[2] == NULL)
		return (get_color(set, split, 'C'));
	if (split[0][0] == 'F' && split[0][1] == '\0' && set->floor.b == -1 && split[2] == NULL)
		return (get_color(set, split, 'F'));
	if(!(get_textures(set, split)))
		return(split_free(split));
	return(!(split_free(split)));
}

bool get_settings(t_set *set, int fd)
{

	set->ceiling.b = -1;
	set->floor.b = -1;
	set->height = -1;
	set->textures.head = NULL;
	set->textures.tail = NULL;
	set->map = NULL;
	set->textures.len = 0;
	while (true)
	{
		if (!(get_settings_hub(set, fd)))
			return (free_set(set));
		if (get_settings_chek(set))
			return (basic_textures_check(set));
	}
}
