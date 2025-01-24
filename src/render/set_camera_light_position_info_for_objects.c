/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera_light_position_info_for_objects.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:34:27 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/22 09:06:39 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	bottom_side_of_plane(t_object *plane, t_vec3 point)
{
	t_vec3	point_dir;
	float	dot;

	point_dir = vec3_subtract(point, plane->position);
	dot = vec3_dot(plane->orientation, point_dir);
	if (dot < 0)
		return (true);
	else
		return (false);
}

static bool	point_inside_sphere(t_object *sphere, t_vec3 point)
{
	t_vec3	center_to_point;

	center_to_point = vec3_subtract(point, sphere->position);
	if (vec3_length(center_to_point) < sphere->radius)
		return (true);
	else
		return (false);
}

/**
 *	@brief
 *	we can break the problem into two parts:
 *	1. Radius check: The perpendicular distance from A to the cylinder's
 *	     central axis must be less than or equal to the radius.
 *	2. Height check: The projection of A onto the cylinder's axis must fall
 *	      within the cylinder's height range.
 *	@return
 *	True: inside;
 *	False: Not inside;
 */
static bool	point_inside_cylinder(t_object *cy, t_vec3 point)
{
	t_vec3	center_to_point;
	float	projection_length;
	t_vec3	closest_point_on_axis;
	t_vec3	perpend_vector;
	double	distance_squared;

	center_to_point = vec3_subtract(point, cy->position);
	projection_length = vec3_dot(center_to_point, cy->orientation);
	if (projection_length < -cy->height / 2
		|| projection_length > cy->height / 2)
		return (false);
	closest_point_on_axis = vec3_scale(cy->orientation, projection_length);
	perpend_vector = vec3_subtract(center_to_point, closest_point_on_axis);
	distance_squared = vec3_dot(perpend_vector, perpend_vector);
	return (distance_squared <= cy->radius * cy->radius);
}

/**
 * 	@result
 * 	True: camera and light are on the same side of the objects.(both inside/
 * 	outside sphere or cylinder). In this case, NEED calculate diffusion.
 * 	False: camera and light are on the different side of the bojects. In this
 * 	case, it does NOT need calculate diffusion.
 */
void	set_camera_light_position_info_for_objects(t_minirt *mrt)
{
	int			i;
	t_object	*ob;

	i = -1;
	while (++i < mrt->object_count)
	{
		ob = &mrt->object[i];
		if (ob->shape == PLANE)
		{
			ob->camera_inside = bottom_side_of_plane(ob, mrt->camera.position);
			ob->light_inside = bottom_side_of_plane(ob, mrt->light.position);
		}
		else if (ob->shape == SPHERE)
		{
			ob->camera_inside = point_inside_sphere(ob, mrt->camera.position);
			ob->light_inside = point_inside_sphere(ob, mrt->light.position);
		}
		else
		{
			ob->camera_inside = point_inside_cylinder(ob, mrt->camera.position);
			ob->light_inside = point_inside_cylinder(ob, mrt->light.position);
		}
	}
}
