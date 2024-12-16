/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:39:18 by arissane          #+#    #+#             */
/*   Updated: 2024/05/01 08:52:32 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*sorc;
	size_t	a;

	if (!dst && !src)
		return (dst);
	dest = (char *)dst;
	sorc = (char *)src;
	a = 0;
	while (a < n)
	{
		dest[a] = sorc[a];
		a++;
	}
	return (dst);
}
