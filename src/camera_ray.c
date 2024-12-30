/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 10:24:26 by arissane          #+#    #+#             */
/*   Updated: 2024/12/19 15:58:39 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera	create_camera_ray(t_camera *camera, t_vec2 *pixel)
{
	t_camera	camera_ray;
	float		normal_x;
	float		normal_y;

	ft_bzero(&camera_ray, sizeof(t_ray));
	//calculate normalised device coordinates, clamp to range 0 to 1 and scale to -1 to 1 range, apply aspect_ratio to x and fov scaling to both
	normal_x = (1.0f - (2.0f * (pixel->x + 0.5f) / WIN_WIDTH) * camera->aspect_ratio * tan(camera->fov * DEGREE_TO_RADIAN));
	normal_y = (1.0f - (2.0f * (pixel->y + 0.5f) / WIN_WIDTH) * tan(camera->fov * DEGREE_TO_RADIAN));

	t_vec3	right_vector;
	t_vec3	up_vector;
	t_vec3	added;
	t_vec3	forward_vector;

	right_vector = vec3_multiply(&camera->right, normal_x);
	up_vector = vec3_multiply(&camera->up, normal_y);
	added = vec3_add(&right_vector, &up_vector);
	forward_vector = vec3_add(&camera->direction, &added);
	vec3_normalise(&forward_vector);
	camera_ray.direction = forward_vector;
	camera_ray.position = camera->position;
	return (camera_ray);
}
