/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 12:41:10 by arissane          #+#    #+#             */
/*   Updated: 2025/01/22 10:49:16 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	calculate_hit_point(t_object *ob, t_camera *c_ray, float t)
{
	t_vec3	hit_point;
	t_vec3	offset_normal;

	hit_point = vec3_add(c_ray->position, vec3_scale(c_ray->direction, t));
	offset_normal = vec3_scale(get_hit_normal(ob, hit_point), 0.0001f);
	hit_point = vec3_add(hit_point, offset_normal);
	return (hit_point);
}

/**
 * 	@brief
 * 	To check if between the light and the intersection(hit_point), there are
 * 	another objects or not. If there is one, then the intersection is obscured;
 * 	otherwise, it isn't obscured.
 *
 * 	@details
 * 	1. get the light_ray's position and direction(normal);
 * 	2. get the distance between the intersection and the light;
 * 	3. Loop the objects in the scene, if the current the ob is the inter_ob,
 * 	   then continue; otherwise, using is_intersected function to check if
 * 	   there is a intersection , and the distance to the light is shorter than
 * 	   the checked_intersection, then it is obscured.
 *
 * 	@return
 * 	true : it is obsucred;
 * 	false: it is not obscured;
 */
bool	is_obscured_from_hitpoint_to_light(t_object *ob, t_minirt *mrt,
	t_camera *c_ray, float t)
{
	t_vec3		hit_p;
	t_camera	light_ray;
	float		intersection_distance;
	float		light_distance;
	int			i;

	i = -1;
	hit_p = calculate_hit_point(ob, c_ray, t);
	light_ray.position = hit_p;
	light_ray.direction = vec3_subtract(mrt->light.position, hit_p);
	vec3_normalise(&light_ray.direction);
	intersection_distance = vec3_length(vec3_subtract(mrt->light.position,
				hit_p));
	light_distance = vec3_length(vec3_subtract(mrt->light.position, hit_p));
	while (++i < mrt->object_count)
	{
		if (mrt->object[i].id == ob->id)
			continue ;
		if (is_intersected(&light_ray, &mrt->object[i], &intersection_distance)
			== true && intersection_distance < light_distance)
			return (true);
	}
	return (false);
}
