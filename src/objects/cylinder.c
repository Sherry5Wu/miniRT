/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:47:58 by jingwu            #+#    #+#             */
/*   Updated: 2024/12/30 15:04:16 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	@function
	Intersect_cylinder will caculate if there is an intersection, if it
	does have, then save the intersection into *t, for other functions
	to use.

	@The intersection between a ray and a plane is calculated using the
	following formula:
	1. Ray Equation: P(t)=O+t⋅D
		O: Ray origin
		D: Ray direction
		t: Ray parameter, representing the distance from the ray origin to
		a point on the ray.
	2. Cylinder Equation: ∥Q−(Q⋅V)V∥^2 = r^2
		Q = P − P0 : A vector from the axis starting point of the cylinder to a given point.
		(Q⋅V)V: The projection of Q onto the direction vector V.
	3. Substituting the Ray Equation into the Cylinder Equation:
		Substitute P(t)=O+t⋅D into the cylinder equation:
			∥O+t⋅D−P0 −[(O+t⋅D−P0)⋅V]⋅V∥^2 =r^2
		Simplify to derive a quadratic equation:
				a * t^2 + b * t +c = 0
		where:
			a = ∥D−(D⋅V)V∥^2
			b = 2⋅(D−(D⋅V)V)⋅(O−P0 −[(O−P0 )⋅V]⋅V)
			c = ∥O -p0 - [(O - p0) * V] * V ∥ ^2 - r^2
*/
int	intersect_cylinder(t_ray *ray, t_object *cylinder, float *t)
{
	t_vec3	oc;

	oc = vec3_subtract(ray->position, cylinder->position);

}
