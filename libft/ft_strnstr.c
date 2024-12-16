/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:44:22 by arissane          #+#    #+#             */
/*   Updated: 2024/04/26 13:51:44 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (needle[a] == '\0')
		return ((char *)haystack);
	while (haystack[a] != '\0' && a < len)
	{
		b = 0;
		while (haystack[a + b] && haystack[a + b] == needle[b] && a + b < len)
		{
			if (needle[b + 1] == '\0')
				return ((char *)haystack + a);
			b++;
		}
		a++;
	}
	return (NULL);
}
