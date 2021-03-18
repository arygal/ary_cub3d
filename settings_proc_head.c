/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_proc_head.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 20:48:02 by megen             #+#    #+#             */
/*   Updated: 2021/03/18 21:35:38 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static int		get_textures_add(char *line , t_set *set, char* specifier)
// {
// 	char *path;
// 	int fd;

// 	path = ft_strtrim(line, " ");
// 	fd = open(path, O_RDONLY);
// 	if (fd < 3)
// 		return(1);
// 	close(fd);
// 	if (!(revstrchr("NO", specifier)))
// 		set->north = path;
// 	else if (!(revstrchr("SO", specifier)))
// 		set->south = path;
// 	else if (!(revstrchr("WE", specifier)))
// 		set->west = path;
// 	else if (!(revstrchr("EA", specifier)))
// 		set->east = path;
// 	else
// 		set->sprite = path;
// 	return(0);	
// }

// static int		get_textures(int fd, t_set *set, char *specifier)
// {
// 	int len;
// 	int ct;
// 	char *line;

// 	ct = -1;
// 	if (get_next_line(fd, &line) <= 0)
// 		return(1);
// 	while(*line == '\0')
// 		{
// 			free(line);
// 			if (get_next_line(fd, &line) <= 0)
// 				return(1);
// 		}
// 	len = ft_strlen(specifier);
// 	while (++ct < len)
// 		if (line[ct] != specifier[ct])
// 			return(1);
// 	if (!(get_textures_add(line + len, set, specifier)))
// 	{
// 		free(line);
// 		return(1);
// 	}
// 	free(line);
// 	return(0);
// }

static int 		get_res_add(char *line, t_set *set)
{
	char **res;

	if (!(res = ft_split(line, ' ')))
		return(i_free(line));
	free(line);
	if (ft_strlen(res[0]) > 4 || ft_strlen(res[1]) > 4)
	{
		ft_split_free(res);
		return(1);
	}
	set->width = ft_atoi(res[0]);
	set->hegiht = ft_atoi(res[1]);
	ft_split_free(res);
	if (set->width <= 0 || set->hegiht <= 0)
		return(1);
	return(0);
}

static int		get_res(int fd, t_set *set)
{
	char *line;
	int ct;

	ct = 1;
	if (get_next_line(fd, &line) <= 0)
		return(1);
	while(*line == '\0')
		{
			free(line);
			if (get_next_line(fd, &line) <= 0)
				return(1);
		}
	if ((line[ct - 1] != 'R' && line[ct] != ' '))
		return(i_free(line));
	if (!(revstrchr(line + 1 ," 0123456789")))
		return(i_free(line));
	if (!(res_pattern(line + 1)))
		return(i_free(line));
	if (get_res_add(line + 1, set))
		return(i_free(line));
	free(line);
	return(0);		
}

static	int		add_to_textures_list(char *name, char *path, t_set *set)
{
	t_texture	*temp;
	char *tname;

	if (set->textures.head != NULL)
		if (texture_list_name_name_check(set, name))
			return(1);
	if (!(tname = ft_strdup(name)))
		return(1);
	if (!(make_textures_node(&temp, path, tname)))
		return(i_free(tname));
	if (set->textures.head == NULL && set->textures.tail == NULL)
		{
			set->textures.head = temp;
			set->textures.tail = temp;
			return(0);
		}
	set->textures.tail->next = temp;
	return(0);
}

static int	get_textures(int fd, t_set *set, char *name)
{
	char	*line;
	char	*path;
	int		pfd;

	if (get_next_line(fd, &line) <= 0)
		return(1);
	while(*line == '\0')
		{
			free(line);
			if (get_next_line(fd, &line) <= 0)
				return(1);
		}
	if (!(name_check(line, name)) || line[ft_strlen(name)] != ' ')
		return(i_free(line));
	if (!(path = ft_strtrim(line + ft_strlen(name), " ")))
		return(i_free(line));
	free(line);
	pfd = open(path, O_RDONLY);
	if (pfd < 3)
		return(i_free(path));
	close(pfd);
	if (!(add_to_textures_list(name , path, set)))
		return(i_free(path));
	return(0);
}



// TODO FREE TEXTURES AT THE END!
int		get_settings(int fd, t_set *set)
{	

	if (get_res(fd , set))
		return(1);
	set->textures.head = NULL;
	set->textures.tail = NULL;
	if (get_textures(fd, set, "NO"))
		return(1);
	if (get_textures(fd, set, "SO"))
		return(free_textures_list(set));
	if (get_textures(fd, set, "WE"))
		return(free_textures_list(set));
	if (get_textures(fd, set, "EA"))
		return(free_textures_list(set));
	if (get_textures(fd, set, "S"))
		return(free_textures_list(set));
	if (get_colors(fd, set, 'F'))
		return(free_textures_list(set));
	if (get_colors(fd, set, 'C'))
		return(free_textures_list(set));
	return(0);
}
