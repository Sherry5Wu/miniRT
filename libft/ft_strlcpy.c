/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:26:09 by arissane          #+#    #+#             */
/*   Updated: 2024/04/26 14:31:48 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	a;

	a = 0;
	if (dstsize != 0)
	{
		while (src[a] != '\0' && a < dstsize - 1)
		{
			dst[a] = src[a];
			a++;
		}
		dst[a] = '\0';
	}
	while (src[a] != '\0')
		a++;
	return (a);
}
