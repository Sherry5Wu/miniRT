/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:24:20 by arissane          #+#    #+#             */
/*   Updated: 2025/01/02 12:25:08 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//calculate if the camera ray hits the radius of the sphere from it's center
float	ray_intersects_sphere(t_minirt *mrt, t_camera *camera_ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t1;
	float	t2;

	oc = vec3_subtract(&mrt->camera.position, &mrt->object[0].position);
	a = vec3_dot(&camera_ray->direction, &camera_ray->direction);
	b = 2.0f * vec3_dot(&oc, &camera_ray->direction);
	c = vec3_dot(&oc, &oc) - mrt->object[0].radius * mrt->object[0].radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant >= 0)
	{
		t1 = (-b - sqrtf(discriminant)) / (2.0f * a);
		t2 = (-b + sqrtf(discriminant)) / (2.0f * a);
		if (t1 > 0 && t1 < t2)
			return (t1);
		if (t2 > 0)
			return (t2);
	}
	return (-1);
}
