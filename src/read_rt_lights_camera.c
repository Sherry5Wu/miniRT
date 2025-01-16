/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_lights_camera.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:03:10 by arissane          #+#    #+#             */
/*   Updated: 2025/01/15 11:11:27 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* If the positive z axis is our default forward direction,
 * the normal vector 0,0,1 is looking forward, 1,0,0 is right, 0,1,0 is up.
 * If the starting orientation is the "forward" direction,
 * the "right" vector can be calculated with the cross product
 * of "forward" and "up" 0,1,0
 * The up vector is put as 0,1,-0.1 in order to avoid a zero vector
 * from the cross product if the forward direction is also along
 * the same direction
 */
static void	set_camera_default_orientation(t_minirt *mrt)
{
	t_vec3	up;

	up.x = 0;
	up.y = 1;
	up.z = -EPSILON;
	mrt->camera.right = vec3_crossproduct(mrt->camera.direction, up);
	mrt->camera.up = vec3_crossproduct(mrt->camera.right,
			mrt->camera.direction);
	vec3_normalise(&mrt->camera.up);
}

int	check_ambient_data(t_minirt *mrt, char **values)
{
	int	i;

	i = 0;
	mrt->ambient_count++;
	if (mrt->ambient_count > 1)
		return (write_error("Number of ambient lighting exceeds 1"));
	while (values[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of variables for "
				"ambient lighting"));
	if (validate_decimal_string(values[1]) == 1)
		return (write_error("Syntax error for ambient light ratio, "
				"should be in a range from 0.0 to 1.0"));
	mrt->ambient.brightness = ft_atofloat(values[1]);
	if (mrt->ambient.brightness > 1.0 || mrt->ambient.brightness < 0.0)
		return (write_error("Ambient light ratio should be in the "
				"range from 0.0 to 1.0"));
	if (add_colour_values(&mrt->ambient.colour, values[2],
			"Ambient light ") == 1)
		return (1);
	return (0);
}

int	check_camera_data(t_minirt *mrt, char **values)
{
	int	i;

	i = 0;
	mrt->camera_count++;
	if (mrt->camera_count > 1)
		return (write_error("Number of cameras exceeds 1"));
	while (values[i])
		i++;
	if (i != 4)
		return (write_error("Invalid number of variables for the camera"));
	if (add_xyz_values(&mrt->camera.position, values[1],
			"Camera coordinates ", 1) == 1)
		return (1);
	if (add_xyz_values(&mrt->camera.direction, values[2],
			"Camera orientation ", 2) == 1)
		return (1);
	mrt->camera.rotation = vec3_to_quaternion(&mrt->camera.direction);
	mrt->camera.fov = ft_atoi(values[3]);
	if (mrt->camera.fov < 0 || mrt->camera.fov > 180)
		return (write_error("Camera FOV should be between 0 to 180"));
	if (WIN_WIDTH < 1 || WIN_HEIGHT < 1)
		return (write_error("Window dimensions are too small"));
	mrt->camera.aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	set_camera_default_orientation(mrt);
	return (0);
}

int	check_light_data(t_minirt *mrt, char **values)
{
	int	i;

	i = 0;
	mrt->light_count++;
	if (mrt->light_count > 1)
		return (write_error("Number of lights exceeds 1"));
	while (values[i])
		i++;
	if (i < 3 || i > 4)
		return (write_error("Invalid number of variables for the light"));
	if (add_xyz_values(&mrt->light.position, values[1],
			"Light coordinates ", 1) == 1)
		return (1);
	if (validate_decimal_string(values[2]) == 1)
		return (write_error("Syntax error; the light brightness "
				"ratio should be a decimal number"));
	mrt->light.brightness = ft_atofloat(values[2]);
	if (values[3])
	{
		if (add_colour_values(&mrt->light.colour, values[3], "Light ") == 1)
			return (1);
	}
	return (0);
}
