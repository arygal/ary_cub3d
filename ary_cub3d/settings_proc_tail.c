/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_proc_tail.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 18:13:32 by megen             #+#    #+#             */
/*   Updated: 2021/03/18 20:15:52 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		name_check(char *line, char *name)
{
	while (*name)
	{
		if (*name != *line)
			return(0);
		++name;
		++line;
	}
	return(1);
}

/* 0 if wrong name   ||   1 if same name */

int		res_pattern(char *line)
{
	while(*line == ' ')
		++line;
	while (*line > 47 && *line < 58)
		++line;
	if(*line == '\0')
		return(0);
	while(*line == ' ')
		++line;
	if(*line == '\0')
		return(0);
	while (*line > 47 && *line < 58)
		++line;
	while(*line == ' ')
		++line;
	if(*line == '\0')
		return(1);
	else
		return(0);
}

/* 0 if wrong pattern || 1 if good pattern */

int color_pattern(char *line)
{
	if (*line == ',')
		return(0);
	while (*line > 47 && *line < 58)
		++line;
	if (*line == ',')
		++line;
	else
		return(0);
	if (*line == ',' || *line == ' ')
		return(0);
	while (*line > 47 && *line < 58)
		++line;
	if (*line == ',')
		++line;
	else
		return(0);
	if (*line == ',' || *line == ' ')
		return(0);
	while (*line > 47 && *line < 58)
		++line;
	if (*line == '\0')
		return(1);
	else
		return(0);	
}

/* 0 if wrong pattern || 1 if good pattern ... i dont like that!*/

int		i_free(char *line)
{
	free(line);
	return(1);
}

/* it is free but it returns 1  */



int		texture_list_name_name_check(t_set *set, char *name)
{
	t_texture	*temp;

	temp = set->textures.head;
	while (temp != NULL)
	{
		if (!(name_check(temp->name, name)))
			return(1);
		temp = temp->next;
	}
	return(0);
}

/* 0 if not found name in list || 1 if found name in list */
