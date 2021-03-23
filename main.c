/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:42:48 by megen             #+#    #+#             */
/*   Updated: 2021/03/23 17:53:44 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool map_proc(t_set *set, char *path)
{
	int fd;
	int len;

	len = ft_strlen(path);
	if (path[len - 1] != 'b' && path[len - 2] != 'u' && path[len - 3] != 'c' && path[len - 4] != '.')
		return(false);
	if ((fd = open(path, O_RDONLY)) < 3)
		return(false);
	if (!(get_settings(set, fd)))
	{
		close(fd);
		return(false);
	}
	if (!(get_map(set, fd)))
	{
		free_set(set);
		close(fd);
		return(false);
	}
	close(fd);
	return(true);
}

int main(int argc, char *argv[])
{

	t_set	set;

	if (argc != 2)
		return(printf("Error\n %s\n", "Use map path as argument"));
	if (!(map_proc(&set, argv[1])))
		return(printf("Error\n %s\n", "Map file error"));
	printf("good");
	return(0);
}
