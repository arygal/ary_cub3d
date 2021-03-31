/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:36:38 by megen             #+#    #+#             */
/*   Updated: 2021/03/31 20:50:04 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H
# define __CUB3D_H

# include "ary_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include <mlx.h>
# include <math.h>

# ifndef move
#  define move 0.30
# endif

# ifndef turn
#  define turn 0.10
# endif


/* GNL header */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif


typedef struct			s_node
{
	char				*val;
	int					valsz;
	struct s_node		*next;
}						t_node;

typedef struct			s_list
{
	t_node				*head;
	t_node				*tail;
	int					len;
	int					firstch;
	int					linesz;
	int					eof;
}						t_list;

/*  map parser header */

typedef struct 			s_rgb
{
	short				r;
	short				g;
	short				b;
}						t_rgb;

typedef struct 			s_texture
{
	void				*img;
	char				*name;
	int					w;
	int					h;
	int					len;
	int					end;
	int					bpp;
	void				*adr;
	struct s_texture 	*next;
}						t_texture;

typedef struct			s_texture_list
{
	t_texture			*head;
	t_texture			*tail;
	t_texture			**index;
	int					len;
	void				*mlx;
}						t_texture_list;

typedef struct			s_set 
{
	int					width;
	int					height;
	t_texture_list		textures;
	int					floor;
	int					ceiling;
	int					spawn;
	int					spawn_x;
	int					spawn_y;
	char				**map;
}						t_set;

typedef struct			s_map_node
{
	char *line;
	struct s_map_node	*next;
}						t_map_node;


typedef struct			s_map_list
{
	int					len;
	t_map_node			*head;
	t_map_node			*tail;
}						t_map_list;

/* mlx header */

typedef struct			s_p
{
	double dir_x;
	double dir_y;
	double plane_x;
	double plane_y;
	double pos_x;
	double pos_y;
}						t_p;

typedef struct			s_img
{
	void				*img;
	int					len;
	int					end;
	int					bpp;
	void				*adr;
}						t_img;



typedef struct			s_mlx
{
	void				*mlx;
	void				*win;
}						t_mlx;

typedef struct			s_all
{
	t_set				set;
	t_mlx				lib;
	t_p					plr;
	t_img				img;
}						t_all;


typedef struct			s_ray
{
	double	tex_p;
	double	tex_s;
	double	cam_x;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	dd_x;
	double	dd_y;
	double	dist_x;
	double	dist_y;
	double	wall_x;
	double	wall_d;
	int		wall_h;
	int		wall_s;
	int		wall_e;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		tex_x;
	int		tex_y;
	int		hit;
	int		side;
	int		line;
	
}						t_ray;



/* utils */

int						clear_atoui(char *line);
int						i_strcmp(char *line1, char *line2);
int						i_free(void *line);
int						split_free(char **ret);
int 					arr_len(char **arr);

/* map parser */

bool					texture_list_name_check(t_set *set, char *name);
int						trgb(int t , int r, int g, int b);
bool					make_map_line(t_map_node **node , char *line);
bool					map_line_check(t_set *set,char *line);
bool					map_chek(t_set *set, int x, int y);
bool 					get_map(t_set *set,int fd);
int						get_next_line(int fd, char **line);
bool 					get_settings(t_set *set, int fd);
bool 					get_res(t_set *set, char **split);
bool 					get_color(t_set *set,char **split, int def);
bool					get_textures(t_set *set,char **split);
int						free_textures_list(t_set *set);
int 					free_map_list(t_map_list *map);
int						free_set(t_set *set);
t_texture				*texture_find(t_set *set, char *name);

/*----------------------game--------------------------------------------------*/

bool					game(t_all *all);
#endif