/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 20:36:38 by megen             #+#    #+#             */
/*   Updated: 2021/03/18 21:34:16 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __CUB3D_H
# define __CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

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
}						t_texture_list;

typedef struct			s_set 
{
	int					width;
	int					hegiht;
	t_texture_list		textures;
	t_rgb				floor;
	t_rgb				ceiling;
}						t_set;

int						get_next_line(int fd, char **line);
size_t					ft_strlen(const char *s);
void					*ft_memcpy(void *dst, const void *src, size_t n);
int						get_settings(int fd, t_set *set);
void					*ft_memset(void *b, int c, size_t len);
void					*ft_calloc(size_t count, size_t size);
char					**ft_split(char const *s, char c);
int						ft_atoi(const char *str);
char					**ft_split_free(char **ret);
int						revstrchr(char *line, char* specifier);
char					*ft_strdup(const char *s1);
char					*ft_strtrim(char const *s1, char const *set);
int						name_check(char *line, char *name);
int						res_pattern(char *line);
int						i_free(char *line);
int						texture_list_name_name_check(t_set *set, char *name);
void					free_textures_node(t_set *set);
int						free_textures_list(t_set *set);
int						make_textures_node(t_texture **node , char *path , char *name);
int						get_colors(int fd ,t_set *set, int specifier);
int						color_pattern(char *line);
#endif