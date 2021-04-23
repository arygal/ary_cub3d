#include "cub3d.h"

int	exit_game(t_all *all)
{
	char	*line;

	mlx_destroy_image(all->lib.mlx, all->img.img);
	mlx_destroy_window(all->lib.mlx, all->lib.win);
	free(all->spr.line_y);
	free_set(&all->set);
	get_next_line(-1, &line);
	exit(0);
}

static void	ray_cast(t_all *all, t_ray *ray)
{
	t_spr	spr;

	spr.ln = ray->line;
	inits(all, ray);
	step_prep(ray);
	while (all->set.m[ray->map_y][ray->map_x] != '1')
	{
		dda(ray);
		if (all->set.m[ray->map_y][ray->map_x] == '2')
			sprites(all, &spr, ray->map_x, ray->map_y);
	}
	walls(all, ray);
	line(all, ray);
	ft_bzero(all->spr.line_y, all->set.height);
}

static int	ray_start(t_all *all)
{
	t_ray	ray;
	double	y;
	double	x;

	y = (double)arr_len(all->set.m);
	if (all->plr.pos_y > 1.0 && all->plr.pos_y < y)
		x = ft_strlen(all->set.m[(int)all->plr.pos_y]);
	else
		x = 0.0;
	ray.line = -1;
	if (all->plr.pos_y > 1.0 && all->plr.pos_y < y - 1
		&& all->plr.pos_x > 1.0 && all->plr.pos_x < x - 1)
		if ((all->set.m[(int)all->plr.pos_y][(int)all->plr.pos_x] != ' ')
		&& (all->set.m[(int)all->plr.pos_y][(int)all->plr.pos_x] != '1'))
			while (++ray.line < all->set.width)
				ray_cast(all, &ray);
	if (ray.line == -1)
		draw_canwas(all);
	if (all->set.bmp == true)
		screenshot(&all->img, all->set.width - 1,
			all->set.height - 1, all);
	mlx_put_image_to_window(all->lib.mlx, all->lib.win, all->img.img, 0, 0);
	controls(&all->plr, &all->key);
	return (1);
}

bool	game(t_all *all)
{
	base_inits(all);
	all->spr.line_y = ft_calloc(all->set.height, sizeof(char));
	if (all->spr.line_y == NULL)
		return (false);
	all->lib.win = mlx_new_window(all->lib.mlx, all->set.width,
			all->set.height, "cub3d");
	if (all->lib.win == NULL)
		return (false);
	all->img.img = mlx_new_image(all->lib.mlx, all->set.width, all->set.height);
	if (all->img.img == NULL)
		return (false);
	all->img.adr = mlx_get_data_addr(all->img.img,
			&all->img.bpp, &all->img.len, &all->img.end);
	if (all->img.img == NULL)
		return (false);
	player_init(&all->plr, all->set.s, all->set.spawn_x, all->set.spawn_y);
	mlx_hook(all->lib.win, 2, 1L << 0, controls_press, all);
	mlx_hook(all->lib.win, 3, 1L << 1, controls_release, all);
	mlx_hook(all->lib.win, 17, 0L, exit_game, all);
	mlx_loop_hook(all->lib.mlx, ray_start, all);
	mlx_loop(all->lib.mlx);
	return (true);
}
