/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:52:29 by arissane          #+#    #+#             */
/*   Updated: 2024/04/26 13:23:44 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		a;
	char	c2;
	char	*str;

	a = 0;
	c2 = (char) c;
	str = (NULL);
	while (s[a] != '\0')
	{
		if (s[a] == c2)
			str = ((char *) &s[a]);
		a++;
	}
	if (s[a] == c2)
		str = ((char *) &s[a]);
	return (str);
}
