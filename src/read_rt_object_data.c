/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_object_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:55:05 by arissane          #+#    #+#             */
/*   Updated: 2025/01/14 11:29:08 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	allocate_new_object(t_minirt *mrt)
{
	int			i;
	t_object	*new_array;

	i = 0;
	if (mrt->object_count == 1)
	{
		mrt->object = ft_calloc(2, sizeof(t_object));
		if (!mrt->object)
			return (write_error("allocation failure"));
	}
	else
	{
		new_array = ft_calloc(mrt->object_count, sizeof(t_object));
		if (!new_array)
			return (write_error("allocation failure"));
		while (i < mrt->object_count)
		{
			new_array[i] = mrt->object[i];
			i++;
		}
		free(mrt->object);
		mrt->object = new_array;
	}
	return (0);
}

int	check_sphere_data(t_minirt *mrt, char **values)
{
	int			i;
	t_object	sphere;

	i = 0;
	mrt->object_count++;
	if (allocate_new_object(mrt) == 1)
		return (1);
	while (values[i])
		i++;
	if (i != 4)
		return (write_error("Invalid number of variables for a sphere"));
	sphere.shape = SPHERE;
	sphere.id = mrt->object_count;
	if (add_xyz_values(&sphere.position, values[1],
			"Sphere coordinates ", 1) == 1)
		return (1);
	if (validate_decimal_string(values[2]) == 1)
		return (write_error("Sphere diameter should be a decimal number"));
	sphere.radius = ft_atofloat(values[2]);
	if (sphere.radius != 0)
		sphere.radius = sphere.radius / 2;
	if (add_colour_values(&sphere.colour, values[3], "Sphere ") == 1)
		return (1);
	mrt->object[mrt->object_count - 1] = sphere;
	return (0);
}

int	check_plane_data(t_minirt *mrt, char **values)
{
	int			i;
	t_object	plane;

	i = 0;
	mrt->object_count++;
	if (allocate_new_object(mrt) == 1)
		return (1);
	while (values[i])
		i++;
	if (i != 4)
		return (write_error("Invalid number of variables for a plane"));
	plane.shape = PLANE;
	plane.id = mrt->object_count;
	if (add_xyz_values(&plane.position, values[1],
			"Plane coordinates ", 1) == 1)
		return (1);
	if (add_xyz_values(&plane.orientation, values[2],
			"Plane orientation ", 2) == 1)
		return (1);
	plane.rotation = vec3_to_quaternion(&plane.orientation);
	if (add_colour_values(&plane.colour, values[3], "Plane ") == 1)
		return (1);
	mrt->object[mrt->object_count - 1] = plane;
	return (0);
}

int	check_cylinder_data(t_minirt *mrt, char **values)
{
	int			i;
	t_object	cylinder;

	i = 0;
	mrt->object_count++;
	if (allocate_new_object(mrt) == 1)
		return (1);
	while (values[i])
		i++;
	if (i != 6)
		return (write_error("Cylinder; invalid number of variables"));
	cylinder.shape = CYLINDER;
	cylinder.id = mrt->object_count;
	if (add_xyz_values(&cylinder.position, values[1],
			"Cylinder coordinates ", 1) == 1)
		return (1);
	if (add_xyz_values(&cylinder.orientation, values[2],
			"Cylinder orientation ", 2) == 1)
		return (1);
	cylinder.rotation = vec3_to_quaternion(&cylinder.orientation);
	if (validate_decimal_string(values[3]) == 1)
		return (write_error("Cylinder diameter should be a decimal number"));
	cylinder.radius = ft_atofloat(values[3]);
	if (cylinder.radius != 0)
		cylinder.radius = cylinder.radius / 2;
	if (validate_decimal_string(values[4]) == 1)
		return (write_error("Cylinder height should be a decimal number"));
	cylinder.height = ft_atofloat(values[4]);
	if (add_colour_values(&cylinder.colour, values[5], "Cyinder ") == 1)
		return (1);
	mrt->object[mrt->object_count - 1] = cylinder;
	cylinder.cap_t = vec3_add(cylinder.position,
			vec3_scale(cylinder.orientation, cylinder.height * 0.5));
	cylinder.cap_b = vec3_add(cylinder.position,
			vec3_scale(cylinder.orientation, -cylinder.height * 0.5));
	// printf_vector(cylinder.cap_t);// for testing only
	// printf_vector(cylinder.cap_b);// for testing only
	return (0);
}
