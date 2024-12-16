/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:03:15 by arissane          #+#    #+#             */
/*   Updated: 2024/04/26 08:22:59 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	unsigned char	copy;
	size_t			a;

	str = (unsigned char *) b;
	copy = (unsigned char) c;
	a = 0;
	while (a < len)
	{
		str[a] = copy;
		a++;
	}
	return (b);
}
