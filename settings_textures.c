/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:27:53 by megen             #+#    #+#             */
/*   Updated: 2021/03/22 20:15:47 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	make_textures_node(t_texture **node , char *path , char *name)
{
	if (!(*node = malloc(sizeof(t_texture))))
		return(false);
	(*node)->path = path;
	(*node)->name = name;
	(*node)->next = NULL;
	return(true);
}

/* true if makes new node */

static void			free_textures_node(t_set *set)
{
	t_texture *temp;

	temp = set->textures.head;
	set->textures.head = set->textures.head->next;
	--set->textures.len;
	free(temp->path);
	free(temp->name);
	free(temp);
}

/* kills one from the head */

int			free_textures_list(t_set *set)
{
	while (set->textures.head != NULL)
		free_textures_node(set);
	return(0);
}

/* kills list */


static	bool		add_to_textures_list( t_set *set, char *name, char *path)
{
	t_texture	*temp;

	if (set->textures.head != NULL)
		if (!(texture_list_name_check(set , name)))
		{
			free(path);
			return(i_free(name));
		}
	if (!(make_textures_node(&temp, path, name)))
		{
			free(path);
			return(i_free(name));
		}
	++set->textures.len;
	if (set->textures.head == NULL)
		{
			set->textures.head = temp;
			set->textures.tail = temp;
			return(true);
		}
	set->textures.tail->next = temp;
	set->textures.tail = temp;
	return(true);
}

bool			get_textures(t_set *set,char **split)
{
	int fd;
	char *name;
	char *path;
	
	if (split[2] != NULL)
		return(false);
	fd = open (split[1] , O_RDONLY);
	if (fd < 3)
		return(false);
	close(fd);
	if (!(name = ft_strdup(split[0])))
		return(false);
	if (!(path = ft_strdup(split[1])))
		return(i_free(path));
	if (!(add_to_textures_list(set, name, path)))
		return(false);
	return(true);
}
