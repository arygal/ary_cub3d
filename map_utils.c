/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:30:03 by megen             #+#    #+#             */
/*   Updated: 2021/03/23 17:49:23 by megen            ###   ########.fr       */
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

bool map_chek(char **map, int spawn)
{
	int x;
	int y;
	int len1;
	int len2;

	y = 1;
	while(map[y + 1] != NULL)
	{
		x = 1;
		while(map[y][x + 1] != '\0')
		{
			if (map[y][x] == '2' || map[y][x] == '0' || map[y][x] == spawn)
				{
					len1 = ft_strlen(map[y - 1]);
					len2 = ft_strlen(map[y + 1]);
					if ((x >= len1 || map[y + 1][x] == ' ') 
					|| (x >= len2 || map[y - 1][x] == ' ') 
					|| (map[y][x + 1] == ' ') || (map[y][x - 1] == ' '))
						return(false);
				}
			++x;
		}
		++y;
	}
	return(map_chek_add(map));
}

bool		map_line_check(t_set *set,char *line)
{
	if(*line == '\0')
		return(true);
	if (*line != '1' && *line != ' ')
		return(false);
	while (*line)
	{
		if (*line == 'N' || *line == 'W' || *line == 'S' || *line == 'E')
			{
				if (set->spawn == 0)
				{
					set->spawn = *line;
					++line;
					continue;
				}
					return(false);
			}
		if (*line != '0' && *line != '1' && *line != '2' && *line != ' ')
			return(false);
		++line;
	}
	--line;
	if (*line != '1' && *line != ' ')
		return(false);
	return(true);
}
