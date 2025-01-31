/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_camera_light_position_info_for_objects.        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:34:27 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/27 10:28:56 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief there are two functions. First, checking passed point whether it is
 * on the bottom side of the given plane. Second, when the parameter light is
 * true, then check whether the light is on the plane.
 *
 * @param plane use to check if the passed point whether on the bottom of it;
 * @param point the point is needed to be checked;
 * @param mrt mrt includes the information about the scene;
 * @param light when light is true, then need to check if the light is on the
 * plane or not; otherwise, don't need check.
 *
 * @return true, the point is on the bottom side of the plane;
 * @return false, Not on the bottom;
 */
static bool	pl_bottom(t_object *plane, t_vec3 point, t_minirt *mrt, bool light)
{
	t_vec3	point_dir;
	float	dot;

	point_dir = vec3_subtract(point, plane->position);
	dot = vec3_dot(plane->orientation, point_dir);
	if (light == true && dot == 0)
		mrt->light_on_surface = true;
	if (dot < 0)
		return (true);
	else
		return (false);
}

/**
 * @brief there are two functions. First, checking passed point whether it is
 * inside of the given sphere. Second, when the parameter light is true, then
 * check whether the light is on the sphere surface.
 *
 * @param sphere use to check if the passed point whether inside of it;
 * @param point the point is needed to be checked;
 * @param mrt mrt includes the information about the scene;
 * @param light when light is true, then need to check if the light is on the
 * surface or not; otherwise, don't need check.
 *
 * @return true, the point is inside of the sphere;
 * @return false, Not inside;
 */
static bool	inside_sp(t_object *sphere, t_vec3 point, t_minirt *mrt, bool light)
{
	t_vec3	center_to_point;
	float	length;

	center_to_point = vec3_subtract(point, sphere->position);
	length = vec3_length(center_to_point);
	if (light == true && length == sphere->radius)
		mrt->light_on_surface = true;
	if (length < sphere->radius)
		return (true);
	else
		return (false);
}

/**
 * @brief there are two functions. First, checking passed point whether it is
 * inside of the given cylinder. Second, when the parameter light is true,
 * then check whether the light is on the sphere surface.
 *
 * @param cylinder use to check if the passed point whether inside of it;
 * @param point the point is needed to be checked;
 * @param mrt mrt includes the information about the scene;
 * @param light when light is true, then need to check if the light is on the
 * surface or not; otherwise, don't need check.
 *
 * @return true, the point is inside of the cylinder;
 * @return false, Not inside;
 */
static bool	inside_cy(t_object *cy, t_vec3 point, t_minirt *mrt, bool light)
{
	t_vec3	center_to_point;
	float	projection_length;
	t_vec3	closest_point_on_axis;
	t_vec3	perpend_vector;
	float	distance_squared;

	center_to_point = vec3_subtract(point, cy->position);
	projection_length = vec3_dot(center_to_point, cy->orientation);
	if (projection_length < -cy->height / 2
		|| projection_length > cy->height / 2)
		return (false);
	closest_point_on_axis = vec3_scale(cy->orientation, projection_length);
	perpend_vector = vec3_subtract(center_to_point, closest_point_on_axis);
	distance_squared = vec3_dot(perpend_vector, perpend_vector);
	if (light == true && distance_squared - cy->radius * cy->radius >= -EPSILON
		&& distance_squared - cy->radius * cy->radius <= EPSILON)
		mrt->light_on_surface = true;
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
			ob->camera_inside = pl_bottom(ob, mrt->camera.position, mrt, false);
			ob->light_inside = pl_bottom(ob, mrt->light.position, mrt, true);
		}
		else if (ob->shape == SPHERE)
		{
			ob->camera_inside = inside_sp(ob, mrt->camera.position, mrt, false);
			ob->light_inside = inside_sp(ob, mrt->light.position, mrt, true);
		}
		else
		{
			ob->camera_inside = inside_cy(ob, mrt->camera.position, mrt, false);
			ob->light_inside = inside_cy(ob, mrt->light.position, mrt, true);
		}
	}
}
