/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_proc_body.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:17:29 by megen             #+#    #+#             */
/*   Updated: 2021/03/18 21:04:54 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int get_colors_add(char *line, int specifier, t_set *set)
{
	char **rgb;
	t_rgb temp;

	if(!(rgb = ft_split(line, ',')))
		return(i_free(line));
	free(line);

	if ((ft_strlen(rgb[0]) > 3) || (ft_strlen(rgb[1]) > 3) || (ft_strlen(rgb[2]) > 3))
	{
		ft_split_free(rgb);
		return(1);
	}
	if ((temp.r = ft_atoi(rgb[0]) > 255) || (temp.g = ft_atoi(rgb[1]) > 255) 
	|| (temp.b = ft_atoi(rgb[2]) > 255))
		{
		ft_split_free(rgb);
		return(1);
		}
	if (specifier == 'F')
		set->floor = temp;
	else
		set->ceiling = temp;
	ft_split_free(rgb);
	return(0);
}

int get_colors(int fd ,t_set *set, int specifier)
{
	char *line;
	char *trim;

	if (get_next_line(fd, &line) <= 0)
		return(1);
	while(*line == '\0')
		{
			free(line);
			if (get_next_line(fd, &line) <= 0)
				return(1);
		}
	if (line[0] != specifier || line[1] != ' ')
		return(i_free(line));
	if (!(revstrchr(line + 1 , " 0123456789,")))
		return(i_free(line));
	if (!(trim = ft_strtrim(line + 1, " ")))
		return(i_free(line));
	free(line);
	if (!(color_pattern(line + 1)))
		return(i_free(trim));
	if (get_colors_add(trim, specifier, set))
		return(i_free(trim));
	return(0);
}

int		make_textures_node(t_texture **node , char *path , char *name)
{
	if (!(*node = malloc(sizeof(t_texture))))
		return(0);
	(*node)->path = path;
	(*node)->name = name;
	(*node)->next = NULL;
	return(1);
}

/*  0 if fails || 1  if  makes new node */

int			free_textures_list(t_set *set)
{
	while (set->textures.head != NULL)
		free_textures_node(set);
	return(1);
}

/* kills list */

void			free_textures_node(t_set *set)
{
	t_texture *temp;

	temp = set->textures.head;
	set->textures.head = set->textures.head->next;
	free(temp->path);
	free(temp->name);
	free(temp);
}

/* kills one from the head */