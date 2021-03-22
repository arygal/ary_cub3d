/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megen <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 18:38:00 by megen             #+#    #+#             */
/*   Updated: 2020/11/13 18:38:02 by megen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_calloc(size_t count, size_t size)
{
	unsigned long long	sum;
	void				*ptr;

	sum = count * size;
	ptr = (void *)malloc(sum);
	if (ptr)
		ft_memset(ptr, '\0', sum);
	return (ptr);
}
