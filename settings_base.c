#include "cub3d.h"

static bool	index_textures(t_set *set)
{
	t_texture	*temp;

	set->textures.index = malloc(sizeof(t_texture *) * set->textures.len);
	if (set->textures.index == NULL)
		return (false);
	temp = texture_find(set, "EA");
	set->textures.index[0] = temp;
	temp = texture_find(set, "WE");
	set->textures.index[1] = temp;
	temp = texture_find(set, "SO");
	set->textures.index[2] = temp;
	temp = texture_find(set, "NO");
	set->textures.index[3] = temp;
	temp = texture_find(set, "S");
	set->textures.index[4] = temp;
	return (true);
}

static bool	basic_textures_check(t_set *set)
{
	if (texture_list_name_check(set, "SO"))
		return (free_set(set));
	if (texture_list_name_check(set, "NO"))
		return (free_set(set));
	if (texture_list_name_check(set, "EA"))
		return (free_set(set));
	if (texture_list_name_check(set, "WE"))
		return (free_set(set));
	if (texture_list_name_check(set, "S"))
		return (free_set(set));
	if (!(index_textures(set)))
		return (free_set(set));
	return (true);
}

static bool	get_settings_chek(t_set *set)
{
	if (set->ceiling == -1 || set->floor == -1 || set->height == -1)
		return (false);
	if (set->textures.len != 5)
		return (false);
	return (true);
}

static bool	get_settings_hub(t_set *set, int fd)
{
	char	*line;
	char	**s;

	if (get_next_line(fd, &line) <= 0)
		return (false);
	while (*line == '\0')
	{
		free(line);
		if (get_next_line(fd, &line) <= 0)
			return (false);
	}
	s = ft_split(line, ' ');
	if (*s == NULL)
		return (i_free(line));
	if (s[1] == NULL)
		return (split_free(s));
	free(line);
	if (s[0][0] == 'R' && s[0][1] == '\0' && set->height == -1 && s[2] != NULL)
		return (get_res(set, s));
	if (s[0][0] == 'C' && s[0][1] == '\0' && set->ceiling == -1 && s[2] == NULL)
		return (get_color(set, s, 'C'));
	if (s[0][0] == 'F' && s[0][1] == '\0' && set->floor == -1 && s[2] == NULL)
		return (get_color(set, s, 'F'));
	return (get_textures(set, s));
}

bool	get_settings(t_set *set, int fd)
{
	set->ceiling = -1;
	set->floor = -1;
	set->height = -1;
	set->textures.head = NULL;
	set->textures.tail = NULL;
	set->m = NULL;
	set->textures.len = 0;
	set->textures.mlx = NULL;
	set->textures.index = NULL;
	set->textures.mlx = mlx_init();
	if (set->textures.mlx == NULL)
		return (false);
	while (true)
	{
		if (!(get_settings_hub(set, fd)))
			return (free_set(set));
		if (get_settings_chek(set))
			return (basic_textures_check(set));
	}
}
