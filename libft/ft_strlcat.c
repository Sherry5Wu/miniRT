/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:23:49 by arissane          #+#    #+#             */
/*   Updated: 2024/04/29 10:29:18 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	a;
	size_t	dstlen;
	size_t	srclen;

	a = 0;
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen > dstsize)
		return (dstsize + srclen);
	if (dstsize != 0 && dstlen < dstsize)
	{
		while (a < dstsize - dstlen - 1 && src[a] != '\0')
		{
			dst[dstlen + a] = src[a];
			a++;
		}
		dst[dstlen + a] = '\0';
	}
	return (dstlen + srclen);
}
