/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:24:20 by arissane          #+#    #+#             */
/*   Updated: 2025/01/14 13:29:09 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//calculate if the camera ray hits the radius of the sphere from it's center
float	ray_intersects_sphere(t_camera *camera_ray, t_object *sphere)
{
	t_vec3		camera_distance;
	t_equation	eq;

	camera_distance = vec3_subtract(camera_ray->position, sphere->position);
	eq.a = vec3_dot(camera_ray->direction, camera_ray->direction);
	eq.b = 2.0f * vec3_dot(camera_distance, camera_ray->direction);
	eq.c = vec3_dot(camera_distance, camera_distance)
		- sphere->radius * sphere->radius;
	eq.discriminant = eq.b * eq.b - 4.0f * eq.a * eq.c;
	if (eq.discriminant < 0.000001)
		return (-1);
	eq.t1 = (-eq.b - sqrtf(eq.discriminant)) * (1 / 2.0f * eq.a);
	eq.t2 = (-eq.b + sqrtf(eq.discriminant)) * (1 / 2.0f * eq.a);
	if (eq.t1 > 0 && (eq.t1 < eq.t2 || eq.t2 <= 0))
		return (eq.t1);
	if (eq.t2 > 0)
		return (eq.t2);
	return (-1);
}
