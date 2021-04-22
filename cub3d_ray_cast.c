#include "cub3d.h"

void	step_prep(t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->dist_x = ray->dd_x * (ray->pos_x - ray->map_x);
	}
	else
	{
		ray->step_x = 1;
		ray->dist_x = ray->dd_x * (ray->map_x + 1.0 - ray->pos_x);
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

void	dda(t_ray *ray)
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

void	walls(t_all *all, t_ray *ray)
{
	if (ray->side < 3)
		ray->wall_d = ((1 - ray->step_x) / 2 + ray->map_x - ray->pos_x)
			/ ray->dir_x;
	else
		ray->wall_d = ((1 - ray->step_y) / 2 + ray->map_y - ray->pos_y)
			/ ray->dir_y;
	ray->wall_h = (int)(all->set.height / ray->wall_d);
	ray->wall_s = -ray->wall_h / 2 + all->set.height / 2;
	if (ray->wall_s < 0)
		ray->wall_s = 0;
	ray->wall_e = ray->wall_h / 2 + all->set.height / 2;
	if (ray->wall_e > all->set.height)
		ray->wall_e = all->set.height;
}

void	sprites(t_all *all, t_spr *spr, int x, int y)
{
	spr->spr_x = x - (all->plr.pos_x - 0.5);
	spr->spr_y = y - (all->plr.pos_y - 0.5);
	spr->inv_d = 1.0 / (all->plr.plane_x * all->plr.dir_y
			- all->plr.plane_y * all->plr.dir_x);
	spr->tr_x = spr->inv_d * (all->plr.dir_y * spr->spr_x
			- all->plr.dir_x * spr->spr_y);
	spr->tr_y = spr->inv_d * (-all->plr.plane_y * spr->spr_x
			+ all->plr.plane_x * spr->spr_y);
	spr->scr_x = (int)((1 + spr->tr_x / spr->tr_y) * (all->set.width / 2));
	spr->spr_h = abs((int)(all->set.height / spr->tr_y));
	spr->drw_sy = -spr->spr_h / 2 + all->set.height / 2;
	if (spr->drw_sy < 0)
		spr->drw_sy = 0;
	spr->drw_ey = spr->spr_h / 2 + all->set.height / 2;
	if (spr->drw_ey >= all->set.height)
		spr->drw_ey = all->set.height - 1;
	spr->spr_w = abs((int)(all->set.height / spr->tr_y));
	spr->drw_sx = -spr->spr_w / 2 + spr->scr_x;
	if (spr->drw_sx < 0)
		spr->drw_sx = 0;
	spr->drw_ex = spr->spr_w / 2 + spr->scr_x;
	if (spr->drw_ex >= all->set.width)
		spr->drw_ex = all->set.width - 1;
	draw_sprites(all, spr, spr->ln, 0);
}

void	line(t_all *all, t_ray *ray)
{
	if (ray->side == 1)
		all->set.textures.act = all->set.textures.index[0];
	else if (ray->side == 2)
		all->set.textures.act = all->set.textures.index[1];
	else if (ray->side == 3)
		all->set.textures.act = all->set.textures.index[2];
	else
		all->set.textures.act = all->set.textures.index[3];
	if (ray->side > 2)
		ray->wall_x = ray->pos_x + ray->dir_x * ray->wall_d;
	else
		ray->wall_x = ray->pos_y + ray->dir_y * ray->wall_d;
	ray->wall_x = ray->wall_x - floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)all->set.textures.act->w);
	if (ray->side < 3 && ray->dir_x > 0)
		ray->tex_x = all->set.textures.act->w - ray->tex_x - 1;
	if (ray->side > 2 && ray->dir_y < 0)
		ray->tex_x = all->set.textures.act->w - ray->tex_x - 1;
	draw_textures(all, ray, -1, all->set.ceiling);
}
