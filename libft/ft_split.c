/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 08:15:48 by arissane          #+#    #+#             */
/*   Updated: 2024/07/12 09:48:35 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	string_count(char const *s, char c)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
	while (s[a] != '\0')
	{
		if (s[a] != c && (s[a + 1] == c || s[a + 1] == '\0'))
			b++;
		a++;
	}
	return (b);
}

static void	free_all(char **array)
{
	size_t	a;

	a = 0;
	while (array[a] != 0)
	{
		free(array[a]);
		a++;
	}
	free(array);
}

static void	add_strings(char **array, char const *s, char c, size_t d)
{
	size_t	a;
	size_t	b;
	size_t	x;

	a = 0;
	b = 0;
	x = string_count(s, c);
	while (b < x)
	{
		while (s[a] == c && s[a] != '\0')
			a++;
		if (s[a] != c && s[a] != '\0')
		{
			while (s[a] != c && s[a] != '\0')
			{
				array[b][d] = s[a];
				d++;
				a++;
			}
			array[b][d] = '\0';
			d = 0;
		}
		b++;
	}
	array[b] = (NULL);
}

static char	**allocation(char **array, char const *s, char c, size_t a)
{
	size_t	b;
	size_t	d;

	b = 0;
	d = 0;
	while (s[a] != 0)
	{
		if (s[a] != c && s[a] != '\0')
		{
			while (s[a + d] != c && s[a + d] != '\0')
				d++;
			a = a + d - 1;
			array[b] = malloc(sizeof(char) * (d + 1));
			if (!array[b])
			{
				free_all(array);
				return (NULL);
			}
			d = 0;
			b++;
		}
		a++;
	}
	add_strings(array, s, c, d);
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	x;
	size_t	a;

	a = 0;
	if (!s)
		return (NULL);
	x = string_count(s, c);
	array = malloc(sizeof(char *) * (x + 1));
	if (!array)
		return (NULL);
	array = allocation(array, s, c, a);
	return (array);
}
