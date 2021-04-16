/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:02:46 by megen             #+#    #+#             */
/*   Updated: 2021/04/16 22:37:49 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"


// void reset_sprites(t_all *all)
// {
// 	int ct;

// 	ct = 0;
// 	all->spr.used = 0;
// 	while (all->spr.index[ct]->used == 1)
// 	{
// 		all->spr.index[ct++]->used = 0;
// 		if (all->spr.index[ct] == NULL)
// 			return ;
// 	}
// }

void draw_sprites_tail(t_all *all, t_spr *spr,int x , int y)
{
	int color;
	if (x > spr->drw_sx && x < spr->drw_ex)
	{
		spr->tex_x = (int)((x - (-spr->spr_w / 2 + spr->scr_x)) * all->set.textures.index[4]->w / spr->spr_w);
		if (spr->tr_y > 0 && x > 0 && x < all->set.width)
			{
				y = spr->drw_sy;
				while (y < spr->drw_ey)
				{
					if (all->spr.line_y[y] == 1)
					{
						++y;
						continue ;
					}
					spr->tex_y = (((y * 2 - all->set.height + spr->spr_h) * all->set.textures.index[4]->h) / spr->spr_h) / 2;
					color = mlx_get_pixel_color(all->set.textures.index[4], spr->tex_x, spr->tex_y);
					// if (color !=  0)
					if (color != 9961608)
						{
							mlx_draw_pixel(&all->img, x, y, color);
							all->spr.line_y[y] = 1;
						}
					// if (x == spr->drw_sx + 2)
					// 	printf("%d\n" , color);
					++y;
				}
			}
	}
}

void draw_sprites_body(t_all *all, t_spr *spr, int x , int y)
{
	spr->spr_x = x - (all->plr.pos_x - 0.5);
	spr->spr_y = y - (all->plr.pos_y - 0.5);
	spr->inv_d = 1.0 / (all->plr.plane_x * all->plr.dir_y - all->plr.plane_y * all->plr.dir_x);
	spr->tr_x = spr->inv_d * (all->plr.dir_y * spr->spr_x - all->plr.dir_x * spr->spr_y);
	spr->tr_y = spr->inv_d * (-all->plr.plane_y * spr->spr_x + all->plr.plane_x * spr->spr_y);
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
	draw_sprites_tail(all, spr, spr->ln, 0);
}

void draw_sprites_head(t_all *all , int line , int x, int y)
{
	t_spr spr;
	// int ct;

	// ct = -1;
	spr.ln = line;
	// while (++ct <all->spr.used)
	draw_sprites_body(all, &spr, x, y);
	// reset_sprites(all);
}
