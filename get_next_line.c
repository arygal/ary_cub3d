/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 13:05:01 by megen             #+#    #+#             */
/*   Updated: 2021/04/22 13:56:55 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	pop_node(t_list *pts)
{
	t_node	*temp;

	temp = pts->head;
	if (pts->head->next)
		pts->head = pts->head->next;
	pts->linesz -= temp->valsz;
	free(temp->val);
	free(temp);
	--(pts->len);
	pts->firstch = 0;
	if (pts->len == 0)
	{
		pts->head = NULL;
		pts->tail = NULL;
	}
	return (pts->len);
}

static char	*process_pts_alt(t_list *pts, int lnpos, int mv)
{
	int		linelen;
	char	*ln;

	linelen = pts->linesz - (pts->tail->valsz - lnpos) - pts->firstch + 1;
	ln = malloc(linelen);
	if (!ln)
	{
		while (pts->len != 0)
			pop_node(pts);
		return (NULL);
	}
	while (pts->head != pts->tail)
	{
		ft_memcpy(ln + mv, pts->head->val + pts->firstch,
			pts->head->valsz - pts->firstch);
		mv += pts->head->valsz - pts->firstch;
		pop_node(pts);
	}
	ft_memcpy(ln + mv, pts->tail->val + pts->firstch, lnpos - pts->firstch);
	ln[lnpos + mv - pts->firstch] = '\0';
	pts->firstch = ++lnpos;
	if (pts->eof)
		pop_node(pts);
	return (ln);
}

static int	read_to_node(t_node **node, int fd)
{
	char	*buffer;
	int		ret;

	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		return (-1);
	ret = read(fd, buffer, BUFFER_SIZE);
	(*node) = malloc(sizeof(t_node));
	if (ret > 0 && !(*node))
		ret = -1;
	if (ret > 0)
		(*node)->valsz = ret;
	(*node)->val = malloc((*node)->valsz);
	if (ret > 0 && !((*node)->val))
	{
		free(*node);
		ret = -1;
	}
	if (ret > 0)
	{
		ft_memcpy((*node)->val, buffer, (*node)->valsz);
		(*node)->next = NULL;
	}
	free(buffer);
	return (ret);
}

static int	read_to_list(t_list *pts, int fd, int ret)
{
	t_node	*temp;

	ret = read_to_node(&temp, fd);
	if (ret < 0)
	{
		while (pts->len != 0)
			pop_node(pts);
		return (-1);
	}
	else if (ret == 0)
	{
		pts->eof = 1;
		return (0);
	}
	if ((pts->len) == 0)
		pts->head = temp;
	else
		pts->tail->next = temp;
	pts->tail = temp;
	pts->linesz += temp->valsz;
	++(pts->len);
	pts->eof = 0;
	return (pts->len);
}

int	get_next_line(int fd, char **line)
{
	static t_list	pts;
	int				i;
	int				ret;

	if (!line || fd < 0 || BUFFER_SIZE < 1)
		return (-1);
	i = pts.firstch;
	while (1)
	{
		while (pts.len > 0 && (i < pts.tail->valsz || pts.eof))
		{
			if ((i >= pts.tail->valsz - 1 && pts.eof)
				|| pts.tail->val[i++] == '\n')
			{
				(*line) = process_pts_alt(&pts, i - 1, 0);
				if (!(*line))
					return (-1);
				return (!pts.eof);
			}
		}
		ret = read_to_list(&pts, fd, 0);
		if (ret < 0 || (ret + pts.len == 0))
			return (((ret < 0) || !(*line = ft_calloc(1, 1))) * -1);
		i = pts.eof * (pts.tail->valsz + 1);
	}
}
