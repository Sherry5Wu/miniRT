/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_add_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:00:06 by arissane          #+#    #+#             */
/*   Updated: 2025/01/14 11:09:07 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	write_error2(char *target, char *message)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	add_colour_values(t_colour *colour, char *str, char *target)
{
	int		i;
	char	**colours;

	i = 0;
	colours = ft_split(str, ',');
	while (colours[i])
		i++;
	if (i != 3)
		return (write_error2(target, "should have 3 colour values"));
	if (validate_number_array(colours, 1) == 1)
		return (write_error2(target, "colour values should be integers"));
	colour->red = ft_atoi(colours[0]);
	colour->green = ft_atoi(colours[1]);
	colour->blue = ft_atoi(colours[2]);
	if (colour->red > 255 || colour->red < 0 || colour->green > 255
		|| colour->green < 0 || colour->blue > 255 || colour->blue < 0)
		return (write_error2(target,
				"colour values should be in the range from 0 to 255"));
	free_array(colours);
	return (0);
}

int	add_xyz_values(t_vec3 *xyz, char *str, char *target, int type)
{
	int		i;
	char	**values;

	values = ft_split(str, ',');
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
		return (write_error2(target, "should be 3 values"));
	if (validate_number_array(values, 2) == 1)
		return (write_error2(target, "should be decimal numbers"));
	xyz->x = ft_atofloat(values[0]);
	xyz->y = ft_atofloat(values[1]);
	xyz->z = ft_atofloat(values[2]);
	free_array(values);
	if (type == 2 && (xyz->x > 1.0 || xyz->x < -1.0 || xyz->y > 1.0
			|| xyz->y < -1.0 || xyz->z > 1.0 || xyz->z < -1.0))
		return (write_error2(target,
				"values should be within a range from -1.0 to 1.0"));
	return (0);
}