/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 09:10:07 by jingwu            #+#    #+#             */
/*   Updated: 2024/12/30 14:55:15 by jingwu           ###   ########.fr       */
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
*/
int	intersect_plane(t_ray *ray, t_object *plane, float *t)
{
	float	denominator;
	t_vec3	plane_to_ray;

	denominator = vec3_dot(&(plane->orientation), &(ray->direction));
	if (fabsf(denominator) < 1e-6)
		return (0);
	oc = vec3_subtract(&(plane->position), &(ray->position));
	*t = dot(&oc, &(plane->orientation)) / denominator;
	return (*t >= 0);
}
