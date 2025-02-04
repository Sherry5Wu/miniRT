/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:24:26 by arissane          #+#    #+#             */
/*   Updated: 2025/01/31 09:15:20 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	calculate_forward_vector(t_camera *camera, t_vec2 *normal)
{
	t_vec3	right_vector;
	t_vec3	up_vector;
	t_vec3	added;
	t_vec3	forward_vector;

	right_vector = vec3_scale(camera->right, normal->x);
	up_vector = vec3_scale(camera->up, normal->y);
	added = vec3_add(right_vector, up_vector);
	forward_vector = vec3_add(camera->direction, added);
	vec3_normalise(&forward_vector);
	return (forward_vector);
}

/**
 * Set up camera ray. Calculate normalised device coordinates, clamp to
 * range 0 to 1 and scale to -1 to 1 range, apply aspect_ratio to x and
 * fov scaling to both. Then set the horizontal and vertical rotation
 * and the coordinates of the camera ray origin
 */
t_camera	create_camera_ray(t_camera *camera, t_vec2 *pixel)
{
	t_camera	camera_ray;
	t_vec2		normal;

	ft_bzero(&camera_ray, sizeof(t_ray));
	normal.x = (1.0f - (2.0f * (pixel->x + 0.5f) / WIN_WIDTH))
		* camera->aspect_ratio * tan(camera->fov * DEGREE_TO_RADIAN);
	normal.y = (1.0f - (2.0f * (pixel->y + 0.5f) / WIN_HEIGHT))
		* tan(camera->fov * DEGREE_TO_RADIAN);
	camera_ray.direction = calculate_forward_vector(camera, &normal);
	camera_ray.position = camera->position;
	return (camera_ray);
}
