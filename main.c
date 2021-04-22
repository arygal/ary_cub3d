#include "cub3d.h"

bool	map_proc(t_set *set, char *path)
{
	int	fd;
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] != 'b' && path[len - 2] != 'u' && path[len - 3]
		!= 'c' && path[len - 4] != '.')
		return (false);
	fd = open(path, O_RDONLY);
	if (fd < 3)
		return (false);
	if (!(get_settings(set, fd)))
	{
		close(fd);
		return (false);
	}
	if (!(get_map(set, fd)))
	{
		free_set(set);
		close(fd);
		return (false);
	}
	close(fd);
	return (true);
}

int	main(int argc, char **argv)
{
	t_all	all;

	all.set.bmp = false;
	if (argc == 1)
		return (printf("Error\n %s\n", "Use map path as argument"));
	if (argc > 3)
		return (printf("Error\n %s\n", "Too many arguments"));
	if (argc == 3)
	{
		if (!(i_strcmp(argv[2], "--save")))
			return (printf("Error\n %s\n", "Use \"––save\" for screenshot"));
		all.set.bmp = true;
	}
	if (!(map_proc(&all.set, argv[1])))
		return (printf("Error\n %s\n", "Map file error"));
	screen_res(&all);
	if (!(game(&all)))
		return (exit_game(&all));
	return (0);
}
