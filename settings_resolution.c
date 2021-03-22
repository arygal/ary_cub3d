/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_resolution.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 18:27:53 by megen             #+#    #+#             */
/*   Updated: 2021/03/21 18:44:55 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool get_res(t_set *set, char **split)
{
	if (ft_strlen(split[1]) > 4 || ft_strlen(split[2]) > 4)
		return(split_free(split));
	set->width = clear_atoui(split[1]);
	if (set->width > 3840 || set->width < 1)
			return(split_free(split));
	set->height = clear_atoui(split[2]);	
	if (set->height > 2160 || set->height < 1)
			return(split_free(split));
	split_free(split);
	return(true);
}