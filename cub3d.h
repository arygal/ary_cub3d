/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:36:38 by megen             #+#    #+#             */
/*   Updated: 2021/03/22 17:16:43 by megen            ###   ########.fr       */
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

typedef struct 			s_rgb
{
	short				r;
	short				g;
	short				b;
}						t_rgb;

typedef struct 			s_texture
{
	char				*path;
	char				*name;
	struct s_texture 	*next;
}						t_texture;

typedef struct			s_texture_list
{
	t_texture			*head;
	t_texture			*tail;
	int					len;
}						t_texture_list;

typedef struct			s_set 
{
	int					width;
	int					height;
	t_texture_list		textures;
	t_rgb				floor;
	t_rgb				ceiling;
	int					spawn;
	char				**map;
}						t_set;

// typedef struct 			s_map_node
// {
// 	int					place;
// 	char				*line;
// 	t_map_node			*next;
// }						t_map_node;

// typedef struct			s_map_list
// {
// 	int					len;
// 	t_map_node			*head;
// 	t_map_node			*tail;
// }						t_map_list;

int						clear_atoui(char *line);
bool					ft_strcmp(char *line1, char *line2);
bool					texture_list_name_check(t_set *set, char *name);
int						get_next_line(int fd, char **line);
bool 					get_settings(t_set *set, int fd);
bool 					get_res(t_set *set, char **split);
bool 					get_color(t_set *set,char **split, int def);
bool					get_textures(t_set *set,char **split);
bool					free_textures_list(t_set *set);
int						i_free(char *line);
int						split_free(char **ret);
int						free_set(t_set *set);
#endif