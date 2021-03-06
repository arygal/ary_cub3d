#include "cub3d.h"

static bool	map_assemley(t_set *set, t_map_list *map_src)
{
	char		**map;
	int			ct;
	t_map_node	*temp;

	ct = 0;
	map = malloc(sizeof(char *) * (map_src->len + 1));
	if (map == NULL)
		return (false);
	while (map_src->head != NULL)
	{
		temp = map_src->head;
		map_src->head = map_src->head->next;
		map[ct] = temp->line;
		++ct;
		free(temp);
	}
	map[ct] = NULL;
	set->m = map;
	return (true);
}

static bool	make_map_line(t_map_node **node, char *line)
{
	(*node) = malloc(sizeof(t_map_node));
	if (!(*node))
		return (false);
	(*node)->line = line;
	(*node)->next = NULL;
	return (true);
}

static bool	add_to_map_list(t_map_list *map, char *line)
{
	t_map_node	*temp;

	if (!(make_map_line(&temp, line)))
		return (i_free(line));
	++map->len;
	if (map->head == NULL)
	{
		map->head = temp;
		map->tail = temp;
		return (true);
	}
	map->tail->next = temp;
	map->tail = temp;
	return (true);
}

static bool	map_proc(t_set *set, t_map_list *map, char *first, int fd)
{
	char	*line;
	int		ret;

	ret = 1;
	map->len = 0;
	map->head = NULL;
	line = first;
	set->sprites = 0;
	while (*line != '\0')
	{
		if (!(map_line_check(set, line)))
			return (i_free(line));
		if (!(add_to_map_list(map, line)))
			return (false);
		if (map->len > 2 && ret == 0 && set->s != 0)
			return (true);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (false);
	}
	return (false);
}

bool	get_map(t_set *set, int fd)
{
	char		*line;
	t_map_list	map;

	if (get_next_line(fd, &line) <= 0)
		return (false);
	while (*line == '\0')
	{
		free(line);
		if (get_next_line(fd, &line) <= 0)
			return (false);
	}
	map.len = 0;
	set->s = 0;
	if (!(map_proc(set, &map, line, fd)))
		return (free_map_list(&map));
	if (!(map_assemley(set, &map)))
		return (free_map_list(&map));
	return (map_chek(set, 0, 0, 0));
}
