/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:30:55 by megen             #+#    #+#             */
/*   Updated: 2021/03/21 19:50:43 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool get_color(t_set *set,char **split, int def)
{
	t_rgb temp;
	char	**rgb;

	if(!(rgb = ft_split(split[1], ',')))
		return(split_free(split));
	split_free(split);
	if ((ft_strlen(rgb[0]) > 3) || (ft_strlen(rgb[1]) > 3) || (ft_strlen(rgb[2]) > 3))
		return(split_free(rgb));
	temp.r = clear_atoui(rgb[0]);
	temp.g = clear_atoui(rgb[1]);
	temp.b = clear_atoui(rgb[2]);
	split_free(rgb);
	if ((temp.b > 255 || temp.b < 0) || (temp.r > 255 
	|| temp.r < 0) || (temp.g > 255 || temp.g < 0))
		return(false);
	if (def == 'F')
		set->floor = temp;
	else
		set->ceiling = temp;
	return(true);	
}