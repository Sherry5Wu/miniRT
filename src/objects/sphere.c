/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:24:20 by arissane          #+#    #+#             */
/*   Updated: 2025/01/08 11:13:52 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//calculate if the camera ray hits the radius of the sphere from it's center
float	ray_intersects_sphere(t_camera *camera_ray, t_object *sphere)
{
	t_vec3	camera_distance;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t1;
	float	t2;

	camera_distance = vec3_subtract(camera_ray->position, sphere->position);
	a = vec3_dot(camera_ray->direction, camera_ray->direction);
	b = 2.0f * vec3_dot(camera_distance, camera_ray->direction);
	c = vec3_dot(camera_distance, camera_distance) - sphere->radius * sphere->radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant < 0.000001)
		return (-1);
	t1 = (-b - sqrtf(discriminant)) * (1 / 2.0f * a);
	t2 = (-b + sqrtf(discriminant)) * (1 / 2.0f * a);
	if (t1 > 0 && (t1 < t2 || t2 <= 0))
		return (t1);
	if (t2 > 0)
		return (t2);
	return (-1);
}
