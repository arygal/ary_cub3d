/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:30:03 by megen             #+#    #+#             */
/*   Updated: 2021/04/19 17:38:34 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool make_map_line(t_map_node **node , char *line)
{
	if (!(*node = malloc(sizeof(t_map_node))))
		return(false);
	(*node)->line = line;
	(*node)->next = NULL;
	return(true);
}

static void free_map_line(t_map_list *map)
{
	t_map_node *temp;

	temp = map->head;
	map->head = map->head->next;
	--map->len;
	free(temp->line);
	free(temp);
}

int free_map_list(t_map_list *map)
{
	while (map->head != NULL)
		free_map_line(map);
	return(0);
}

static bool map_chek_add(char **map)
{
	int x;
	int y;

	y = 0;
	x = 0;
	while (map[y][x] != '\0')
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			return(false);
		++x;
	}
	while(map[y] != NULL)
		++y;
	--y;
	x = 0;
		while (map[y][x] != '\0')
	{
		if (map[y][x] != '1' && map[y][x] != ' ')
			return(false);
		++x;
	}
	return(true);
}

bool map_chek(t_set *set , int x, int y)
{
	int len1;
	int len2;

	while(set->m[++y + 1] != NULL)
	{
		len1 = ft_strlen(set->m[y - 1]);
		len2 = ft_strlen(set->m[y + 1]);
		while(set->m[y][++x + 1] != '\0')
		{
			if (set->m[y][x] == '2' || set->m[y][x] == '0' || set->m[y][x] == set->s)
				{
					if ((x >= len1 || set->m[y + 1][x] == ' ') 
					|| (x >= len2 || set->m[y - 1][x] == ' ') 
					|| (set->m[y][x + 1] == ' ') || (set->m[y][x - 1] == ' '))
						return(false);
					if(set->m[y][x] == set->s)
					{
							set->spawn_x = x;
							set->spawn_y = y;
					}
				}
		}
		x = 0;
	}
	return(map_chek_add(set->m));
}

bool		map_line_check(t_set *set,char *ln)
{
	if (*ln != '1' && *ln != ' ')
		return(false);
	while (*ln)
	{
		if (*ln == '2')
			++set->sprites;
		if (*ln == 'N' || *ln == 'W' || *ln == 'S' || *ln == 'E')
			{
				if (set->s == 0)
				{
					set->s = *ln;
					++ln;
					continue;
				}
					return(false);
			}
		if (*ln != '0' && *ln != '1' && *ln != '2' && *ln != ' ')
			return(false);
		++ln;
	}
	--ln;
	if (*ln != '1' && *ln != ' ')
		return(false);
	return(true);
}
