/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:14:00 by megen             #+#    #+#             */
/*   Updated: 2021/03/31 21:03:55 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ray_cast(t_all *all, t_ray *ray);
int	ray_start(t_all *all);
void inits(t_all *all, t_ray *ray);
void step_prep(t_ray *ray);
void ray_cast(t_all *all, t_ray *ray);
void draw_line(t_all *all, t_ray *ray);
void textures_draw(t_all *all, t_ray *ray, t_texture *img);
void walls(t_all *all, t_ray *ray);
void dda(t_ray *ray);
void step_prep(t_ray *ray);

void mlx_draw_pixel(t_img *img, int width,int height, int argb)
{
	char *dest;

	dest = img->adr + (height * img->len + width * (img->bpp / 8));
	*(unsigned int*)dest = argb;
}

int mlx_get_pixel_color(t_texture *img, int width,int height)
{
	int		argb;
	char	*dest;

	dest = img->adr + (height * img->len + width * (img->bpp / 8));
	argb = *(unsigned int*)dest;
	return(argb);
}

void draw_canwas(t_all *all)
{
	int half;
	int y;
	int x;
	int color;

	half = all->set.height / 2;
	y = -1;
	color = all->set.ceiling;
	while (++y < all->set.height)
	{
		x = -1;
		if (y == half)
			color = all->set.floor;
		while (++x < all->set.width)
			mlx_draw_pixel(&all->img, x , y, color);
	}
}

int exit_game_alt(t_set *set)
{
	free_set(set);
	exit(1);
}

void move_forward(t_p	*plr, char **map)
{
	(void)map;
	// if (map[(int)(plr->pos_x + plr->dir_x * move)][(int)(plr->pos_y)] == '1')
		plr->pos_x = plr->pos_x + plr->dir_x * move;
	// if (map[(int)plr->pos_x][(int)(plr->pos_y + plr->dir_y * move)] == '1')
		plr->pos_y = plr->pos_y + plr->dir_y * move;
}

void move_back(t_p	*plr, char **map)
{
	(void)map;
	// if (map[(int)(plr->pos_x - plr->dir_x * move)][(int)(plr->pos_y)] == '1')
		plr->pos_x = plr->pos_x - plr->dir_x * move;
	// if (map[(int)plr->pos_x][(int)(plr->pos_y - plr->dir_y * move)] == '1')
		plr->pos_y = plr->pos_y - plr->dir_y * move;
}

void rotate_right(t_p *plr)
{
	double dir_x;
	double plane_x;

	dir_x = plr->dir_x;
	plane_x = plr->plane_x;

	plr->dir_x = plr->dir_x * cos(turn) - plr->dir_y * sin(turn);
	plr->dir_y = dir_x * sin(turn) + plr->dir_y * cos(turn);
	plr->plane_x = plr->plane_x *cos(turn) - plr->plane_y * sin(turn);
	plr->plane_y = plane_x * sin(turn) + plr->plane_y * cos(turn);
}

void rotate_left(t_p *plr)
{
	double dir_x;
	double plane_x;

	dir_x = plr->dir_x;
	plane_x = plr->plane_x;

	plr->dir_x = plr->dir_x * cos(-turn) - plr->dir_y * sin(-turn);
	plr->dir_y = dir_x * sin(-turn) + plr->dir_y * cos(-turn);
	plr->plane_x = plr->plane_x *cos(-turn) - plr->plane_y * sin(-turn);
	plr->plane_y = plane_x * sin(-turn) + plr->plane_y * cos(-turn);
}

int controls(int key, t_all *all)
{
	// printf("%d\n", key);
	if (key == 53)
	{	
		mlx_destroy_window(all->lib.mlx, all->lib.win);
		exit_game_alt(&all->set);
	}
	if (key == 13)
		move_forward(&all->plr, all->set.map);
	if (key == 0)
		rotate_left(&all->plr);
	if (key == 1)
		move_back(&all->plr, all->set.map);
	if (key == 2)
		rotate_right(&all->plr);
	return(0);
 }
void player_init_add(t_p *plr)
{
	plr->dir_y = 0.0;
	plr->dir_x = 1.0;
	plr->plane_x = 0.0;
	plr->plane_y = 0.66;		
}

void player_init(t_p *plr, int spawn)
{
	if (spawn == 'N')
	{
		plr->dir_y = -1.0;
		plr->dir_x = 0.0;
		plr->plane_x = 0.66;
		plr->plane_y = 0.0;
	}
	else if (spawn ==  'S')
	{
		plr->dir_y = 1.0;
		plr->dir_x = 0.0;
		plr->plane_x = -0.66;
		plr->plane_y = 0.0;		
	}
	else if (spawn ==  'W')
	{
		plr->dir_y = 0.0;
		plr->dir_x = -1.0;
		plr->plane_x = 0.0;
		plr->plane_y = -0.66;		
	}
	else
		player_init_add(plr);
}

// TODO : ERROR HANDLING!
bool		game(t_all *all)
{	
	all->lib.mlx = all->set.textures.mlx;
	if (!(all->lib.win = mlx_new_window(all->lib.mlx, all->set.width, all->set.height, "cub3d")))
		return(false);
	all->img.img = mlx_new_image(all->lib.mlx, all->set.width, all->set.height);
	if (all->img.img == NULL)
		return(false);
	all->img.adr = mlx_get_data_addr(all->img.img, &all->img.bpp, &all->img.len, &all->img.end);
	if (all->img.img == NULL)
		return(false);
	all->plr.pos_x = (double)all->set.spawn_x + 0.5;
	all->plr.pos_y = (double)all->set.spawn_y + 0.5;
	player_init(&all->plr, all->set.spawn);
	// all->plr.pos_y = 2.460075;
	// all->plr.pos_x = 8.906560;
	// all->plr.plane_x = 0;
	// all->plr.plane_y = 0.66;
	// all->plr.dir_x = (all->set.spawn == 'E') + ((all->set.spawn == 'W') * -1);
	// all->plr.dir_y = (all->set.spawn =='S') + ((all->set.spawn == 'N') * -1);
	// all->plr.dir_x = 1;
	// all->plr.dir_y = 0;
	mlx_hook(all->lib.win, 2 , 1L<<0, controls, all);
	mlx_hook(all->lib.win, 17 , 0L ,exit_game_alt, &all->set);
	mlx_loop_hook(all->lib.mlx , ray_start, all);
	mlx_loop(all->lib.mlx);
	return(0);
}

int	ray_start(t_all *all)
{
	t_ray ray;
	double		y;
	double		x;

	//  all->plr.pos_x = 0.005;
	// all->plr.pos_y += 0.5;
	y = (double)arr_len(all->set.map);
	if (all->plr.pos_y > 1.0 && all->plr.pos_y < y)
		x = ft_strlen(all->set.map[(int)all->plr.pos_y]);
	else
		x = 0.0;
	ray.line = -1;
	// printf("X:%f\n", all->plr.pos_x);
	// printf("Y:%f\n", all->plr.pos_y);
	// 	printf("DirX:%f\n", all->plr.dir_x);
	// printf("DirY:%f\n", all->plr.dir_y);
	// 	printf("PlaneX:%f\n", all->plr.plane_x);
	// printf("PlaneY:%f\n", all->plr.plane_y);

	if (all->plr.pos_y > 1.0 && all->plr.pos_y < y - 1 && all->plr.pos_x > 1.0 && all->plr.pos_x < x - 1)
	{
		if((all->set.map[(int)all->plr.pos_y][(int)all->plr.pos_x] != ' ') && (all->set.map[(int)all->plr.pos_y][(int)all->plr.pos_x] != '1'))
			while (++ray.line < all->set.width)
			ray_cast(all, &ray);
		else
			draw_canwas(all);
	}
	else
		draw_canwas(all);
	mlx_put_image_to_window(all->lib.mlx, all->lib.win, all->img.img, 0, 0);
	return(1);
}
void inits(t_all *all, t_ray *ray)
{
	ray->pos_x = all->plr.pos_x;
	ray->pos_y = all->plr.pos_y;
	ray->map_x = (int)all->plr.pos_x;
	ray->map_y = (int)all->plr.pos_y;
	ray->cam_x = 2 * ray->line / (double)all->set.width - 1;
	ray->dir_x = all->plr.dir_x + all->plr.plane_x * ray->cam_x;
	ray->dir_y = all->plr.dir_y + all->plr.plane_y * ray->cam_x;
	ray->dd_x = fabs(1 / ray->dir_x);
	ray->dd_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
}

void step_prep(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = ray->dd_x * (ray->pos_x - ray->map_x);
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = ray->dd_x * (ray->map_x + 1.0 - ray->pos_x ) ;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->dist_y = ray->dd_y * (ray->pos_y - ray->map_y);
	}
	else
	{
		ray->step_y = 1;
		ray->dist_y = ray->dd_y * (ray->map_y + 1.0 - ray->pos_y);
	}	
}

void dda(t_ray *ray)
{
	if (ray->dist_x < ray->dist_y)
	{
		ray->dist_x = ray->dist_x + ray->dd_x;
		ray->map_x = ray->map_x + ray->step_x;
		if (ray->step_x == 1)
			ray->side = 1;
		else
			ray->side = 2;
	}
	else
	{
		ray->dist_y = ray->dist_y + ray->dd_y;
		ray->map_y = ray->map_y + ray->step_y;
		if (ray->step_y == 1)
			ray->side = 3;
		else
			ray->side = 4;
	}
}

void walls(t_all *all, t_ray *ray)
{
	if (ray->side < 3)
		ray->wall_d = ((1 - ray->step_x) / 2 + ray->map_x - ray->pos_x) / ray->dir_x;
	else
		ray->wall_d = ((1 - ray->step_y) / 2 + ray->map_y - ray->pos_y) / ray->dir_y;
	ray->wall_h = (int)(all->set.height / ray->wall_d);
	ray->wall_s = -ray->wall_h / 2 + all->set.height / 2;
	if (ray->wall_s < 0)
		ray->wall_s = 0;
	ray->wall_e = ray->wall_h / 2 + all->set.height / 2;
	if (ray->wall_e >= all->set.height)
		ray->wall_e = all->set.height;
}
void textures_draw(t_all *all, t_ray *ray, t_texture *img)
{
	int y;
	int color;

	ray->tex_s = 1.0 * img->h / ray->wall_h;
	ray->tex_p = ray->tex_s * (ray->wall_s - all->set.height / 2 + ray->wall_h / 2);
	y = -1;
	color = all->set.ceiling;
	while (++y < ray->wall_s)
		mlx_draw_pixel(&all->img, ray->line, y, color);
	while(y < ray->wall_e)
	{
		ray->tex_y = (int)ray->tex_p & (img->h - 1);
		ray->tex_p = ray->tex_p + ray->tex_s;
		color = mlx_get_pixel_color(img, ray->tex_x, ray->tex_y);
		mlx_draw_pixel(&all->img, ray->line , y , color);
		++y;
	}
	color = all->set.floor;
	while (y < all->set.height)
	{
		mlx_draw_pixel(&all->img, ray->line, y, color);
		y++;
	}
}


void draw_line(t_all *all, t_ray *ray)
{
	t_texture *temp;

	if (ray->side == 1)
		temp = all->set.textures.index[0];
	else if (ray->side == 2)
		temp = all->set.textures.index[1];
	else if (ray->side == 3)
		temp = all->set.textures.index[2];
	else
		temp = all->set.textures.index[3];
	if (ray->side > 2)
		ray->wall_x = ray->pos_x + ray->dir_x * ray->wall_d;
	else
		ray->wall_x = ray->pos_y + ray->dir_y * ray->wall_d;
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)temp->w);
	if (ray->side < 3 && ray->dir_x > 0)
		ray->tex_x = temp->w - ray->tex_x - 1;
	if (ray->side > 2 && ray->dir_y < 0)
		ray->tex_x = temp->w - ray->tex_x - 1;
	textures_draw(all, ray, temp);
}

void ray_cast(t_all *all, t_ray *ray)
{
	inits(all, ray);
	step_prep(ray);
	while (ray->hit == 0)
	{
		dda(ray);
		if(all->set.map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
	walls(all, ray);
	draw_line(all, ray);
}
