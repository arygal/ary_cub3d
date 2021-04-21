/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:27:53 by megen             #+#    #+#             */
/*   Updated: 2021/04/20 18:07:18 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	make_textures_node(void *mlx ,t_texture **node
, char *path , char *name)
{
	*node = malloc(sizeof(t_texture));
	if (*node == NULL)
		return(false);
	(*node)->img = mlx_xpm_file_to_image(mlx, path, &(*node)->w, &(*node)->h);
	if ((*node)->img == NULL)
		return(i_free(*node));
	(*node)->adr = mlx_get_data_addr((*node)->img,
	&(*node)->bpp, &(*node)->len, &(*node)->end);
	if ((*node)->adr == NULL)
	{
		mlx_destroy_image(mlx,(*node)->img);
		return(i_free(*node));
	}
	free(path);
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
	mlx_destroy_image(set->textures.mlx, temp->img);
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
	if (!(make_textures_node(set->textures.mlx ,&temp, path, name)))
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
	int len;
	
	if (split[2] != NULL)
		return(split_free(split));
	len = ft_strlen(split[1]);
	if (len < 5 || (!(i_strcmp(split[1] + len - 4, ".xpm")) 
			&& !(i_strcmp(split[1] + len - 4, ".png"))))
		return (split_free(split));
	fd = open (split[1] , O_RDONLY);
	if (fd < 3)
		return(split_free(split));
	close(fd);
	free(split);
	if (!(add_to_textures_list(set, split[0], split[1])))
		return(false);
	return(true);
}
