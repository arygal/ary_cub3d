#include "cub3d.h"

void	inits(t_all *all, t_ray *ray)
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
}

static void	player_init_add(t_p *plr)
{
	plr->dir_y = 0.0;
	plr->dir_x = 1.0;
	plr->plane_x = 0.0;
	plr->plane_y = 0.66;
}

void	player_init(t_p *plr, int spawn, int x, int y)
{
	plr->pos_x = (double)x + 0.5;
	plr->pos_y = (double)y + 0.5;
	if (spawn == 'N')
	{
		plr->dir_y = -1.0;
		plr->dir_x = 0.0;
		plr->plane_x = 0.66;
		plr->plane_y = 0.0;
	}
	else if (spawn == 'S')
	{
		plr->dir_y = 1.0;
		plr->dir_x = 0.0;
		plr->plane_x = -0.66;
		plr->plane_y = 0.0;
	}
	else if (spawn == 'W')
	{
		plr->dir_y = 0.0;
		plr->dir_x = -1.0;
		plr->plane_x = 0.0;
		plr->plane_y = -0.66;
	}
	else
		player_init_add(plr);
}

void	base_inits(t_all *all)
{
	all->lib.mlx = all->set.textures.mlx;
	all->spr.line_y = NULL;
	all->lib.win = NULL;
	all->img.img = NULL;
	all->img.adr = NULL;
	all->key.down = false;
	all->key.up = false;
	all->key.rot_left = false;
	all->key.rot_right = false;
	all->key.left = false;
	all->key.right = false;
}
