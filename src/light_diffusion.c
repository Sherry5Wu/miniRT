/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_diffusion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 11:30:47 by arissane          #+#    #+#             */
/*   Updated: 2025/01/08 11:29:09 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	add_diffusion_multiplier(t_colour *colour, t_vec3 normal, t_vec3 light_direction)
{
	float	diffusion;

	diffusion = vec3_dot(normal, light_direction);
	if (diffusion < 0.0f)
		diffusion = 0.0f;
	colour->red = (int)(colour->red * diffusion);
	colour->green = (int)(colour->green * diffusion);
	colour->blue = (int)(colour->blue * diffusion);
	if (colour->red > 255)
		colour->red = 255;
	if (colour->green > 255)
		colour->green = 255;
	if (colour->blue > 255)
		colour->blue = 255;
}

void	light_diffusion(t_minirt *mrt, t_camera *camera_ray, t_object *object, t_colour *colour, float t)
{
	t_vec3		intersection;
	t_vec3		intersection_normal;
	t_vec3		scaled;

	scaled = vec3_scale(camera_ray->direction, t);
	intersection = vec3_add(mrt->camera.position, scaled);
	if (object->shape == PLANE)
		intersection_normal = object->orientation;
	else if (object->shape == SPHERE)
	{
		intersection_normal = vec3_subtract(intersection, object->position);
		vec3_normalise(&intersection_normal);
	}
	else
	{
		intersection.y = 0;
		intersection_normal = vec3_subtract(intersection, object->position);
		vec3_normalise(&intersection_normal);
	}
	add_diffusion_multiplier(colour, intersection_normal, mrt->light.position);
}
