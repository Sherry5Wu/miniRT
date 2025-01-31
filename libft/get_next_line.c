/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:41:36 by arissane          #+#    #+#             */
/*   Updated: 2025/01/23 08:27:00 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_address(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}

static char	*new_line(char *saved_text)
{
	char	*new_line;
	size_t	len;
	size_t	i;

	i = 0;
	while (saved_text[i] != '\n' && saved_text[i] != '\0')
		i++;
	if (saved_text[i] == '\0')
		return (free_address(&saved_text));
	len = strlen_gnl(saved_text, '\0');
	new_line = substr_gnl(saved_text, i + 1, len, 0);
	free_address(&saved_text);
	if (new_line == NULL)
		return (NULL);
	return (new_line);
}

static char	*get_line(char *saved_text)
{
	char	*line;
	size_t	len;
	size_t	i;

	i = 0;
	len = strlen_gnl(saved_text, '\n');
	if (saved_text[len] == '\n')
		len++;
	line = malloc(sizeof(char) * len + 1);
	if (line == NULL)
		return (NULL);
	while (i < len)
	{
		line[i] = saved_text[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*read_line(int fd, char *saved_text)
{
	ssize_t	bytes;
	char	*buffer;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (free_address(&saved_text));
	bytes = 1;
	while (bytes > 0 && strchr_gnl(saved_text, '\n') == NULL)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(buffer);
			return (free_address(&saved_text));
		}
		if (bytes == 0)
			break ;
		buffer[bytes] = '\0';
		saved_text = strjoin_gnl(saved_text, buffer);
	}
	free(buffer);
	if (strlen_gnl(saved_text, '\0') > 0)
		return (saved_text);
	return (free_address(&saved_text));
}

char	*get_next_line(int fd)
{
	static char	*saved_text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	saved_text = read_line(fd, saved_text);
	if (saved_text == NULL)
		return (NULL);
	line = get_line(saved_text);
	if (line == NULL)
		return (free_address(&saved_text));
	saved_text = new_line(saved_text);
	return (line);
}
