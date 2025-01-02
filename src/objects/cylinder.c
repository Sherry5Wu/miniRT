/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:47:58 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/02 13:40:17 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	@function
	Using for select the closer intersection for cylinder.
*/
static float	select_intersection(float a, float b, float discriminant)
{
	float	t1;
	float	t2;

	t1 = (-b - sqrt(discriminant)) / (2 * a);
	t2 = (-b + sqrt(discriminant)) / (2 * a);
	if (t1 > 0 && t2 < 0)
		return (t1);
	else if (t1 < 0 && t2 >= 0)
		return (t2);
	else if ( t1 > 0 && t2 >=0)
	{
		if (t1 < t2)
			return (t1);
		else
			return (t2);
	}
	else
		return (-1);
}

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
		Q = P − P0 : A vector from the axis starting point of the cylinder to
		             a given point.
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
	@return value
	-1: when there are no intersections or intersections are behind of the
		light
	t: when there are intersections, return the intersection is closer to the
		light.
*/
float	ray_intersects_cylinder(t_camera *ray, t_object *cylinder)
{
	t_vec3	cyl_to_ray;
	t_vec3	d_project;
	t_vec3	d_perpendicular;
	t_vec3	oc_project;
	t_vec3	oc_perpendicular;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	cyl_to_ray = vec3_subtract(&(ray->position), &(cylinder->position));
	d_project = vec3_project(&(ray->direction), &(cylinder->orientation));
	d_perpendicular = vec3_subtract(&(ray->direction), &d_project);
	oc_project = vec3_project(&(cyl_to_ray), &(cylinder->orientation));
	oc_perpendicular = vec3_subtract(&(cyl_to_ray), &(oc_project));
	a = vec3_dot(&d_perpendicular, &d_perpendicular);
	b = 2 * vec3_dot(&d_perpendicular, &oc_perpendicular);
	c = vec3_dot(&oc_perpendicular, &oc_perpendicular) - (cylinder->radius)
		* (cylinder->radius);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return (select_intersection(a, b, discriminant));
}

