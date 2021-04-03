/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_sprite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:02:46 by megen             #+#    #+#             */
/*   Updated: 2021/04/03 21:10:32 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"


void reset_sprites(t_all *all)
{
	t_sprite *temp;

	temp = all->spr.head;
	all->spr.used = 0;
	if(temp->used == 0)
		return;
	while(temp->used != 0 )
	{
		temp->used = 0;
		if (temp->next == NULL)
			return;
		temp = temp->next;
	}
}

void list_swap(t_sprites *list, t_sprite *first, t_sprite *second)
{
	t_sprite *temp;	

	if (first == list->head)
	{
		first->next = second->next;
		second->next = first;
		list->head = second;
		return;
	}
	temp = list->head;
		while (temp->next != first)
			temp = temp->next;
	first->next = second->next;
	second->next = first;
	temp->next = second;
}

t_sprite *find_n_srite(t_sprites *list, int n)
{
	t_sprite *temp;
	int			ct;

	ct = -1;
	temp = list->head;
	while (++ct < n)
		temp = temp->next;
	return(temp);
}

void sort_sprites(t_all *all,int ct, double i, double j)
{
	t_sprite *first;
	t_sprite *second;

	if (all->spr.used == 2)
		{
			first = find_n_srite(&all->spr, ct);
			second = find_n_srite(&all->spr, ct + 1);
			i = pow(all->plr.pos_x - first->x, 2) + pow(all->plr.pos_y - first->y, 2);
			j = pow(all->plr.pos_x - second->x, 2) + pow(all->plr.pos_y - second->y, 2);
			if (i < j)
				list_swap(&all->spr, first, second);
			return;
		}
	while (ct < all->spr.used && ct + 1 != all->spr.used)
	{
		first = find_n_srite(&all->spr, ct);
		second = find_n_srite(&all->spr, ct + 1);
		i = pow(all->plr.pos_x - first->x, 2) + pow(all->plr.pos_y - first->y, 2);
		j = pow(all->plr.pos_x - second->x, 2) + pow(all->plr.pos_y - second->y, 2);
		if (i < j)
			{
				list_swap(&all->spr, first, second);
				ct = 0;
			}
		else
			++ct;
	}
}

void draw_sprites_tail(t_all *all, t_spr *spr,int x , int y)
{
	int color;
	int i;

	while (++x < spr->drw_ex)
		{
			spr->tex_x = (int)((x - (-spr->spr_w / 2 + spr->scr_x)) * all->set.textures.index[4]->w / spr->spr_w);
			if (spr->tr_y > 0 && x > 0 && x < all->set.width && spr->tr_y < all->spr.buf[x])
			{
				y = spr->drw_sy;
				while (y < spr->drw_ey)
					{
					i =  y * 2 - all->set.height + spr->spr_h ;

					spr->tex_y = ((i * all->set.textures.index[4]->h) / spr->spr_h) / 2;
					color = mlx_get_pixel_color(all->set.textures.index[4], spr->tex_x, spr->tex_y);
					// if (color !=  0)
					if (color != 9961608)
						mlx_draw_pixel(&all->img, x, y, color);
					// if (x == spr->drw_sx + 2)
					// 	printf("%d\n" , color);
					++y;
					}
			}
		}
}

void draw_sprites_body(t_all *all, t_spr *spr, t_sprite *node)
{
	spr->spr_x = node->x - (all->plr.pos_x - 0.5);
	spr->spr_y = node->y - (all->plr.pos_y - 0.5);
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
	draw_sprites_tail(all, spr, spr->drw_sx - 1, 0);
}

void draw_sprites_head(t_all *all)
{
	t_spr spr;

	spr.line = -1;
	sort_sprites(all, 0, 0.0, 0.0);
	while (++spr.line < all->spr.used)
		draw_sprites_body(all, &spr, find_n_srite(&all->spr, spr.line));
	reset_sprites(all);
}
