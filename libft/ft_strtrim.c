/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:16:57 by arissane          #+#    #+#             */
/*   Updated: 2024/05/11 09:22:07 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	startpoint(char const *s1, char const *set)
{
	int	a;
	int	b;
	int	start;

	a = 0;
	b = 0;
	start = 0;
	while (set[a] != '\0')
	{
		if (set[a] == s1[b])
		{
			a = 0;
			b++;
			start++;
		}
		if (set[a] != s1[b])
			a++;
	}
	return (start);
}

static int	endpoint(char const *s1, char const *set, int len)
{
	int	a;
	int	b;
	int	end;

	a = 0;
	b = len - 1;
	end = 0;
	while (set[a] != '\0')
	{
		if (set[a] == s1[b])
		{
			a = 0;
			b--;
			end++;
		}
		if (set[a] != s1[b])
			a++;
	}
	return (len - end);
}

static char	*wrtstr(char const *s1, char *str, size_t start, int end)
{
	int	a;

	a = 0;
	if (end != 0)
	{
		while (a < end)
		{
			str[a] = s1[start];
			a++;
			start++;
		}
	}
	str[a] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	int		len;
	char	*str;

	len = ft_strlen(s1);
	start = startpoint(s1, set);
	end = endpoint(s1, set, len) - start;
	if (end < 0)
		end = 0;
	if ((end - start) > 0)
		len = end;
	else
		len = 0;
	str = malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (NULL);
	str = wrtstr(s1, str, start, end);
	return (str);
}
