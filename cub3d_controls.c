#include "cub3d.h"

static void rotate_right(t_p *plr)
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

static void rotate_left(t_p *plr)
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

void controls(t_p *plr, t_keys * key)
{
	if (key->up)
	{
		plr->pos_x = plr->pos_x + plr->dir_x * move;
		plr->pos_y = plr->pos_y + plr->dir_y * move;
	}
	if (key->down)
	{
		plr->pos_x = plr->pos_x - plr->dir_x * move;
		plr->pos_y = plr->pos_y - plr->dir_y * move;
	}
	if(key->left)
	{
		plr->pos_x = plr->pos_x - plr->plane_x * move;
		plr->pos_y = plr->pos_y - plr->plane_y * move;
	}
	if (key->right)
	{
		plr->pos_x = plr->pos_x + plr->plane_x * move;
		plr->pos_y = plr->pos_y + plr->plane_y * move;
	}
	if (key->rot_left)
		rotate_left(plr);
	if (key->rot_right)
		rotate_right(plr);
 }

int controls_press(int key, t_all *all)
{
	if (key == 53)
		exit_game(all);
	else if (key == 124)
		all->key.rot_right = true;
	else if(key == 123)
		all->key.rot_left = true;
	else if (key == 13)
		all->key.up = true;
	else if (key == 0)
		all->key.left = true;
	else if (key == 1)
		all->key.down = true;
	else if (key == 2)
		all->key.right = true;
	return(0);
}

int controls_release(int key, t_all *all)
{
	if (key == 124)
		all->key.rot_right = false;
	else if(key == 123)
		all->key.rot_left = false;
	else if (key == 13)
		all->key.up = false;
	else if (key == 0)
		all->key.left = false;
	else if (key == 1)
		all->key.down = false;
	else if (key == 2)
		all->key.right = false;
	return(0);
}