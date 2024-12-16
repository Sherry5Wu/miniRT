/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 10:45:36 by arissane          #+#    #+#             */
/*   Updated: 2024/04/30 13:11:55 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	a;
	size_t	b;

	a = ft_strlen(s1);
	b = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (a + b + 1));
	if (!str)
		return (NULL);
	a = 0;
	while (s1[a] != '\0')
	{
		str[a] = s1[a];
		a++;
	}
	b = 0;
	while (s2[b] != '\0')
	{
		str[a] = s2[b];
		a++;
		b++;
	}
	str[a] = '\0';
	return (str);
}
