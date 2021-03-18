/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 18:42:48 by megen             #+#    #+#             */
/*   Updated: 2021/03/18 21:35:12 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static char			**map_proc(char *path , t_set *set)
// {
// 	char **map;
// 	int fd;
// 	int len;

// 	len = ft_strlen(path);
// 	if (path[len] != 'b' && path[len - 1] != 'u' && path[len - 2] != 'c' && path[len - 3] != '.')
// 		return(NULL);
// 	if ((fd = open(path, O_RDONLY)) < 0)
// 		return(NULL);
// 	if (get_settings(fd, set))
// 		return(NULL);
// //	map = get_map(fd);
// 	close(fd);
// 	return(map);
// }

// int main(int argc, char *argv[])
int main()
{
	// char **canvas;
	t_set	set;
	int		fd;

	fd = open("./map.cub", O_RDONLY);
	printf("%d\n", fd);
	if (get_settings(fd, &set))
		printf("wrong\n");
	else
		printf("good\n");
	return(0);
	// if (argc == 1)
	// 	return(printf("%s\n%s\n","Error", "Please use path to map file as argument!"));
	// if (argc > 2)
	// 	return(printf("%s\n%s\n","Error", "Too many maps, pleas use only one!"));
	// if (!(canvas = map_proc(argv[1],  &settings)))
	// 	return(printf("%s\n%s\n","Error", "Map or malloc error!"));
	// return(0);
}
