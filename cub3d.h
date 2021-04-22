#ifndef CUB3D_H
# define CUB3D_H

# include "ary_libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdbool.h>
# include "mlx/mlx.h"
# include <math.h>

# ifndef MOVE
#  define MOVE 0.10
# endif

# ifndef TURN
#  define TURN 0.05
# endif

# ifndef TR_COLOR
#  define TR_COLOR 9961608
# endif

/* GNL header */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8192
# endif

typedef struct s_node
{
	char			*val;
	int				valsz;
	struct s_node	*next;
}					t_node;

typedef struct s_list
{
	t_node		*head;
	t_node		*tail;
	int			len;
	int			firstch;
	int			linesz;
	int			eof;
}				t_list;

/*  settings parser header */

typedef struct s_rgb
{
	short	r;
	short	g;
	short	b;
}			t_rgb;

typedef struct s_texture
{
	void				*img;
	char				*name;
	int					w;
	int					h;
	int					len;
	int					end;
	int					bpp;
	void				*adr;
	struct s_texture	*next;
}						t_texture;

typedef struct s_texture_list
{
	t_texture	*head;
	t_texture	*tail;
	t_texture	**index;
	t_texture	*act;
	int			len;
	void		*mlx;
}				t_texture_list;

typedef struct s_set
{
	t_texture_list	textures;
	char			**m;
	int				width;
	int				height;
	int				floor;
	int				ceiling;
	int				sprites;
	int				s;
	int				spawn_x;
	int				spawn_y;
	bool			bmp;
}					t_set;

typedef struct s_map_node
{
	char				*line;
	struct s_map_node	*next;
}						t_map_node;

typedef struct s_map_list
{
	int			len;
	t_map_node	*head;
	t_map_node	*tail;
}				t_map_list;

/* game header */

typedef struct s_p
{
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	pos_x;
	double	pos_y;
}			t_p;

typedef struct s_img
{
	void	*img;
	int		len;
	int		end;
	int		bpp;
	void	*adr;
}			t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}			t_mlx;

typedef struct s_sprite
{
	int		x;
	int		y;
}			t_sprite;

typedef struct s_sprites
{
	t_sprite	index;
	char		*line_y;
}				t_sprites;

typedef struct s_keys
{
	bool		up;
	bool		down;
	bool		left;
	bool		right;
	bool		rot_left;
	bool		rot_right;
}				t_keys;

typedef struct s_all
{
	t_set		set;
	t_mlx		lib;
	t_p			plr;
	t_img		img;
	t_sprites	spr;
	t_keys		key;
}				t_all;

typedef struct s_ray
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
	int		side;
	int		line;
}			t_ray;

typedef struct s_spr
{
	double	inv_d;
	double	tr_x;
	double	tr_y;
	double	spr_x;
	double	spr_y;
	int		spr_h;
	int		spr_w;
	int		drw_sx;
	int		drw_ex;
	int		drw_sy;
	int		drw_ey;
	int		tex_x;
	int		tex_y;
	int		scr_x;
	int		ln;
}			t_spr;

/* utils */

int						clear_atoui(char *line);
int						i_strcmp(char *line1, char *line2);
int						i_free(void *line);
int						split_free(char **ret);
int						arr_len(char **arr);

/*----------------------settings parser--------------------------------------*/

bool					texture_list_name_check(t_set *set, char *name);
int						trgb(int t, int r, int g, int b);
bool					map_line_check(t_set *set, char *line);
bool					map_chek(t_set *set, int x, int y, int len1);
bool					get_map(t_set *set, int fd);
int						get_next_line(int fd, char **line);
bool					get_settings(t_set *set, int fd);
bool					get_res(t_set *set, char **split);
bool					get_color(t_set *set, char **split, int def);
bool					get_textures(t_set *set, char **split);
int						free_textures_list(t_set *set);
int						free_map_list(t_map_list *map);
int						free_set(t_set *set);
void					screen_res(t_all *all);
t_texture				*texture_find(t_set *set, char *name);

/*----------------------ray_cast---------------------------------------------*/

void					step_prep(t_ray *ray);
void					dda(t_ray *ray);
void					walls(t_all *all, t_ray *ray);
void					sprites(t_all *all, t_spr *spr, int x, int y);
void					line(t_all *all, t_ray *ray);

/*----------------------inits------------------------------------------------*/

void					base_inits(t_all *all);
void					inits(t_all *all, t_ray *ray);
void					player_init(t_p *plr, int spawn, int x, int y);

/*----------------------game-------------------------------------------------*/

bool					game(t_all *all);
int						exit_game(t_all *all);
void					draw_sprites(t_all *all, t_spr *spr, int x, int y);
void					draw_textures(t_all *all, t_ray *ray, int y, int c);
void					draw_canwas(t_all *all);
void					ray_cast(t_all *all, t_ray *ray);
bool					screenshot(t_img *img, int x, int y, bool *s);
int						controls_press(int key, t_all *all);
int						controls_release(int key, t_all *all);
void					controls(t_p *plr, t_keys *key);

#endif
