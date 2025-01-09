/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:10:07 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/08 11:13:34 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	@function
	Intersect_plane will caculate if there is an intersection, if it does have,
	then save the intersection into *t, for other functions to use.

	@ The intersection between a ray and a plane is calculated using the
	following formula:
	1. Ray Equation: P(t)=O+tD
		O: ray origin;
		D: ray direction;
		t: Parameter representing the distance from the origin to the
		   intersection point;
	2. Plane euqation: N⋅(P−P0)= 0
		N: plane normal vector;
		P0: A point on the plane;
		P: Any point on the plane.
	3. Intersection formula: t= N * (P0 - O) / (N * D)
	if N * D = 0, the ray is parallel to the plane and there is no intersection.

	Because the shape is plane, so if there are intersections, it will be just
	one.

	@return value
	-1: when there are no intersections or intersection is behind of the light
	t: when there is a intersection.
*/
float	ray_intersects_plane(t_camera *ray, t_object *plane)
{
	t_vec3	plane_to_ray;
	float	denominator;
	float	t;

	denominator = vec3_dot((plane->orientation), (ray->direction));
	if (fabsf(denominator) < DIFFER)
		return (-1);
	plane_to_ray = vec3_subtract(plane->position, ray->position);
	t = vec3_dot(plane_to_ray, (plane->orientation)) / denominator;
	if (t > 0)
		return (t);
	else
		return (-1);
}
