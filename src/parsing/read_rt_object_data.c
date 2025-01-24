/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_object_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:55:05 by arissane          #+#    #+#             */
/*   Updated: 2025/01/23 11:58:48 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_sphere_data(t_minirt *mrt, char **values)
{
	t_object	sphere;

	if (allocate_new_object(mrt) == 1)
		return (1);
	if (check_number_of_variables(values, 4, 4) == 1)
		return (write_error("Invalid number of variables for a sphere"));
	sphere.shape = SPHERE;
	sphere.id = mrt->object_count + 1;
	if (add_xyz_values(&sphere.position, values[1],
			"Sphere coordinates ", 1) == 1)
		return (1);
	if (validate_decimal_string(values[2]) == 1)
		return (write_error("Sphere diameter should be a decimal number"));
	sphere.radius = ft_atofloat(values[2]);
	if (sphere.radius < 0.0f)
		return (write_error("Sphere diameter should be positive"));
	if (sphere.radius != 0)
		sphere.radius = sphere.radius / 2;
	if (add_colour_values(&sphere.colour, values[3], "Sphere ") == 1)
		return (1);
	mrt->object[mrt->object_count] = sphere;
	mrt->object_count++;
	return (0);
}

int	check_plane_data(t_minirt *mrt, char **values)
{
	t_object	plane;

	if (allocate_new_object(mrt) == 1)
		return (1);
	if (check_number_of_variables(values, 4, 4) == 1)
		return (write_error("Invalid number of variables for a plane"));
	plane.shape = PLANE;
	plane.id = mrt->object_count + 1;
	if (add_xyz_values(&plane.position, values[1],
			"Plane coordinates ", 1) == 1)
		return (1);
	if (add_xyz_values(&plane.orientation, values[2],
			"Plane orientation ", 2) == 1)
		return (1);
	plane.rotation = vec3_to_quaternion(&plane.orientation);
	if (add_colour_values(&plane.colour, values[3], "Plane ") == 1)
		return (1);
	mrt->object[mrt->object_count] = plane;
	mrt->object_count++;
	return (0);
}

static int	check_cylinder_data2(t_object *cylinder, char **values)
{
	cylinder->rotation = vec3_to_quaternion(&cylinder->orientation);
	if (validate_decimal_string(values[3]) == 1)
		return (write_error("Cylinder diameter should be a decimal number"));
	cylinder->radius = ft_atofloat(values[3]);
	if (cylinder->radius < 0.0f)
		return (write_error("Cylinder diameter should be positive"));
	if (cylinder->radius != 0)
		cylinder->radius = cylinder->radius / 2;
	if (validate_decimal_string(values[4]) == 1)
		return (write_error("Cylinder height should be a decimal number"));
	cylinder->height = ft_atofloat(values[4]);
	if (cylinder->height < 0.0f)
		return (write_error("Cylinder height should be positive"));
	if (add_colour_values(&cylinder->colour, values[5], "Cyinder ") == 1)
		return (1);
	return (0);
}

int	check_cylinder_data(t_minirt *mrt, char **values)
{
	t_object	cylinder;

	if (allocate_new_object(mrt) == 1)
		return (1);
	if (check_number_of_variables(values, 6, 6) == 1)
		return (write_error("Cylinder; invalid number of variables"));
	cylinder.shape = CYLINDER;
	cylinder.id = mrt->object_count + 1;
	if (add_xyz_values(&cylinder.position, values[1],
			"Cylinder coordinates ", 1) == 1)
		return (1);
	if (add_xyz_values(&cylinder.orientation, values[2],
			"Cylinder orientation ", 2) == 1)
		return (1);
	if (check_cylinder_data2(&cylinder, values) == 1)
		return (1);
	mrt->object[mrt->object_count] = cylinder;
	mrt->object_count++;
	return (0);
}
