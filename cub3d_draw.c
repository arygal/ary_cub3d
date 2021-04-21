#include "cub3d.h"

static void mlx_draw_pixel(t_img *img, int width,int height, int argb)
{
	char *dest;

	dest = img->adr + (height * img->len + width * (img->bpp / 8));
	*(unsigned int*)dest = argb;
}

static int mlx_get_pixel_color(t_texture *img, int width,int height)
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

void draw_textures(t_all *all, t_ray *ray, int y, int c)
{
	ray->tex_s = 1.0 * all->set.textures.act->h / ray->wall_h;
	ray->tex_p = ray->tex_s * (ray->wall_s - all->set.height
	/ 2 + ray->wall_h / 2);
	while (++y < ray->wall_s)
		if (all->spr.line_y[y] == 0)
			mlx_draw_pixel(&all->img, ray->line, y, c);
	while(y < ray->wall_e)
	{
		ray->tex_y = (int)ray->tex_p & (all->set.textures.act->h - 1);
		ray->tex_p = ray->tex_p + ray->tex_s;
		if (all->spr.line_y[y] == 0)
		{
			c = mlx_get_pixel_color(all->set.textures.act
			, ray->tex_x, ray->tex_y);
			mlx_draw_pixel(&all->img, ray->line , y , c);
		}
		++y;
	}
	c = all->set.floor;
	while (y <= all->set.height)
	{
		if (all->spr.line_y[y] == 0)
			mlx_draw_pixel(&all->img, ray->line, y, c);
		++y;
	}
}

void draw_sprites(t_all *all, t_spr *spr,int x , int y)
{
	int color;
	
	if (x > spr->drw_sx && x < spr->drw_ex)
	{
		spr->tex_x = (int)((x - (-spr->spr_w / 2 + spr->scr_x))
		* all->set.textures.index[4]->w / spr->spr_w);
		if (spr->tr_y > 0 && x > 0 && x < all->set.width)
			{
				y = spr->drw_sy - 1;
				while (++y < spr->drw_ey)
				{
					if (all->spr.line_y[y] == 1)
						continue ;
					spr->tex_y = (((y  * 2 - all->set.height + spr->spr_h)
					* all->set.textures.index[4]->h) / spr->spr_h) / 2;
					color = mlx_get_pixel_color(all->set.textures.index[4]
					, spr->tex_x, spr->tex_y);
					if (color != TR_COLOR)
						{
							mlx_draw_pixel(&all->img, x, y , color);
							all->spr.line_y[y] = 1;
						}
				}
			}
	}
}