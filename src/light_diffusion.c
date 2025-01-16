/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_diffusion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:30:47 by arissane          #+#    #+#             */
/*   Updated: 2025/01/15 14:02:31 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	get_hit_normal(t_object *ob, t_vec3 hit_point, t_vec3 l_dir)
{
	t_vec3	normal;

	if (ob->shape == PLANE)
	{
		if (vec3_dot(ob->orientation, l_dir) <= 0)
			normal = vec3_scale(ob->orientation, -1);
		else
			normal = ob->orientation;
	}
	else if (ob->shape == SPHERE)
		normal = vec3_subtract(hit_point, ob->position);
	else
		normal = ob->cy_hit_normal;
	vec3_normalise(&normal);
	return (normal);
}

float	diffusion(t_minirt *mrt, t_camera *c_ray, t_object *ob, float t)
{
	t_vec3	hit_point;// position
	t_vec3	light_dir; // vector
	float	attenuation;
	float	cos_angle;
	t_vec3	hit_normal;
	float	diffuse_ratio;

	hit_point = vec3_add(c_ray->position, vec3_scale(c_ray->direction, t));
	light_dir = vec3_subtract(mrt->light.position, hit_point);
	attenuation = fmin(1.0, 60.0 / vec3_length(light_dir));
	vec3_normalise(&light_dir);
	hit_normal = get_hit_normal(ob, hit_point, light_dir);
	cos_angle = vec3_cosine(hit_normal, light_dir);
	if (cos_angle <= 0)
		return (0);
	diffuse_ratio = mrt->light.brightness * cos_angle * attenuation;
	return (diffuse_ratio);
}
