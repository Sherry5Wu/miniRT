/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:17:00 by arissane          #+#    #+#             */
/*   Updated: 2025/01/23 08:57:54 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_values(t_minirt *mrt, char **values)
{
	if (!values[0])
		return (1);
	if (ft_strcmp(values[0], "A") == 0)
		return (check_ambient_data(mrt, values));
	if (ft_strcmp(values[0], "C") == 0)
		return (check_camera_data(mrt, values));
	if (ft_strcmp(values[0], "L") == 0)
		return (check_light_data(mrt, values));
	if (ft_strcmp(values[0], "sp") == 0)
		return (check_sphere_data(mrt, values));
	if (ft_strcmp(values[0], "pl") == 0)
		return (check_plane_data(mrt, values));
	if (ft_strcmp(values[0], "cy") == 0)
		return (check_cylinder_data(mrt, values));
	return (0);
}

static int	check_line(t_minirt *mrt, char *line)
{
	int		i;
	int		character_count;
	char	**values;

	i = 0;
	character_count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			character_count++;
		i++;
	}
	line[i] = '\0';
	if (character_count > 0)
	{
		values = ft_split(line, ' ');
		i = check_values(mrt, values);
		free_array(values);
		if (i == 1)
			return (1);
	}
	return (0);
}

static void	tabs_to_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

/**
 * 	@brief
 * 	To check if the passed file name follow the format: XXXX.rt
 *
 * 	@return
 * 	True: if the name is valid;
 * 	False: if the name is NOT valid;
 */
static bool	valid_file_name(char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 3] == '.' && file[i - 2] == 'r'
		&& file[i - 1] == 't')
		return (true);
	else
		return (false);
}

int	read_rt_file(t_minirt *mrt, char *file)
{
	int		fd;
	int		check;
	char	*line;

	if (valid_file_name(file) == false)
		return (write_error("The extension of the file is wrong"));
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write_error("Couldn't find or open the .rt file"));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tabs_to_spaces(line);
		check = check_line(mrt, line);
		free(line);
		if (check == 1)
			return (read_close_return(fd));
	}
	close(fd);
	return (0);
}
