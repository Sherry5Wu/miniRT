/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_lights_camera.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 11:03:10 by arissane          #+#    #+#             */
/*   Updated: 2025/02/03 14:53:12 by arissane         ###   ########.fr       */
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
	vec3_normalise(&mrt->camera.right);
	mrt->camera.up = vec3_crossproduct(mrt->camera.right,
			mrt->camera.direction);
	vec3_normalise(&mrt->camera.up);
}

int	check_ambient_data(t_minirt *mrt, char **values)
{
	mrt->ambient_count++;
	if (mrt->ambient_count > 1)
		return (write_error("Number of ambient lights exceeds 1"));
	if (check_number_of_variables(values, 3, 3) == 1)
		return (write_error("Invalid number of variables for "
				"ambient light"));
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
	mrt->camera_count++;
	if (mrt->camera_count > 1)
		return (write_error("Number of cameras exceeds 1"));
	if (check_number_of_variables(values, 4, 4) == 1)
		return (write_error("Invalid number of variables for the camera"));
	if (add_xyz_values(&mrt->camera.position, values[1],
			"Camera coordinates ", 1) == 1)
		return (1);
	if (add_xyz_values(&mrt->camera.direction, values[2],
			"Camera orientation ", 2) == 1)
		return (1);
	if (check_if_normalised(mrt->camera.direction, "Camera") == 1)
		return (1);
	if (validate_number_string(values[3]) == 1)
		return (write_error("Camera FOV is not an integer"));
	mrt->camera.fov = ft_atoi(values[3]);
	if (mrt->camera.fov < 0 || mrt->camera.fov > 180)
		return (write_error("Camera FOV should be between 0 to 180"));
	mrt->camera.aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;
	set_camera_default_orientation(mrt);
	return (0);
}

int	check_light_data(t_minirt *mrt, char **values)
{
	mrt->light_count++;
	if (mrt->light_count > 1)
		return (write_error("Number of lights exceeds 1"));
	if (check_number_of_variables(values, 3, 4) == 1)
		return (write_error("Invalid number of variables for the light"));
	if (add_xyz_values(&mrt->light.position, values[1],
			"Light coordinates ", 1) == 1)
		return (1);
	if (validate_decimal_string(values[2]) == 1)
		return (write_error("Light brightness "
				"ratio should be a decimal number"));
	mrt->light.brightness = ft_atofloat(values[2]);
	if (mrt->light.brightness > 1.0 || mrt->light.brightness < 0.0)
		return (write_error("Light brightness should be in the "
				"range from 0.0 to 1.0"));
	if (values[3])
	{
		if (add_colour_values(&mrt->light.colour, values[3], "Light ") == 1)
			return (1);
	}
	return (0);
}
