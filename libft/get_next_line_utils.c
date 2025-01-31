/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:41:52 by arissane          #+#    #+#             */
/*   Updated: 2025/01/22 16:19:50 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	strlen_gnl(char	*str, char c)
{
	size_t	i;

	if (str == NULL)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*strchr_gnl(char *str, int c)
{
	size_t		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((char *) &str[i]);
		i++;
	}
	if (str[i] == c)
		return ((char *) &str[i]);
	return (NULL);
}

static char	*strjoinh_gnl(char *saved_text, char *buffer, char *str)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (saved_text[i] != '\0')
	{
		str[i] = saved_text[i];
		i++;
	}
	while (buffer[k] != '\0')
	{
		str[i + k] = buffer[k];
		k++;
	}
	str[i + k] = '\0';
	return (str);
}

char	*strjoin_gnl(char *saved_text, char *buffer)
{
	char	*str;
	size_t	len;

	if (saved_text == NULL)
	{
		saved_text = malloc(sizeof(char));
		if (saved_text == NULL)
			return (NULL);
		saved_text[0] = '\0';
	}
	len = strlen_gnl(saved_text, '\0') + strlen_gnl(buffer, '\0');
	str = malloc(sizeof(char) * len + 1);
	if (str == NULL)
	{
		return (free_address(&saved_text));
	}
	str = strjoinh_gnl(saved_text, buffer, str);
	free_address(&saved_text);
	return (str);
}

char	*substr_gnl(char *saved_text, size_t start, size_t len, size_t i)
{
	char	*str;

	if (saved_text == NULL)
		return (NULL);
	if (start > len)
	{
		str = malloc(sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
		return (str);
	}
	if (len - start < len)
		len = len - start;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	while (saved_text[start + i] != '\0')
	{
		str[i] = saved_text[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
