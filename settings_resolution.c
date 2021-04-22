#include "cub3d.h"

bool	get_res(t_set *set, char **split)
{
	if (ft_strlen(split[1]) > 9 || ft_strlen(split[2]) > 4)
		return (split_free(split));
	set->width = clear_atoui(split[1]);
	if (set->width < 1)
		return (split_free(split));
	set->height = clear_atoui(split[2]);
	if (set->height < 1)
		return (split_free(split));
	split_free(split);
	return (true);
}

void	screen_res(t_all *all)
{
	int	x;
	int	y;

	mlx_get_screen_size(&x, &y);
	if (x < all->set.width)
		all->set.width = x;
	if (y < all->set.height)
		all->set.height = y;
}
