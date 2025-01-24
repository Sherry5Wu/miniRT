/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:53:16 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/22 09:29:13 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	@function
	To calculate the intersection on the top/bottom of a cylinder.
	if T < 0, then the cap is at back of the camera.

	@return
	return the intersection if there is one; otherwise, return -1.
*/

static float	intersects_cylinder_cap(t_camera *ray, t_object *cylinder,
t_vec3 center)
{
	float	denom;
	float	t;
	float	distance;
	t_vec3	hit_point;
	t_vec3	vector;

	denom = vec3_dot(ray->direction, (cylinder->orientation));
	if (fabs(denom) < EPSILON)
		return (-1);
	t = vec3_dot(vec3_subtract(center, ray->position),
			cylinder->orientation) / denom;
	if (t < 0)
		return (-1);
	hit_point = vec3_add(ray->position, vec3_scale(ray->direction, t));
	vector = vec3_subtract(hit_point, center);
	distance = vec3_dot(vector, vector);
	if (distance > cylinder->radius * cylinder->radius)
		return (-1);
	return (t);
}

static float	smallest_positive(float a, float b, float c)
{
	float	smallest;

	smallest = -1;
	if (a > 0 && (smallest < 0 || a < smallest))
		smallest = a;
	if (b > 0 && (smallest < 0 || b < smallest))
		smallest = b;
	if (c > 0 && (smallest < 0 || c < smallest))
		smallest = c;
	return (smallest);
}

static t_vec3	get_side_hit_normal(t_camera *ray, t_object *cy, float t)
{
	t_vec3	hit_point;
	t_vec3	hit_to_center;
	float	projection_lenght;
	t_vec3	projection_point;
	t_vec3	normal;

	hit_point = vec3_add(ray->position, vec3_scale(ray->direction, t));
	hit_to_center = vec3_subtract(hit_point, cy->position);
	projection_lenght = vec3_dot(hit_to_center, cy->orientation);
	projection_point = vec3_add(cy->position,
			vec3_scale(cy->orientation, projection_lenght));
	normal = vec3_subtract (hit_point, projection_point);
	vec3_normalise(&normal);
	return (normal);
}

/*
	@function
	Intersect_cylinder will calculate if there is an intersection, if it
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
	4. Check Cylinder Height: After finding valid t values from the quadratic
	equation, calculate the intersection point P(t). Project P(t) onto the
	cylinder axis to determine if it lies within the height limits:
			h=(P(t)−C)⋅V
	Ensure:
		0≤ h≤ height
	@return value
	-1: when there are no intersections or intersections are behind of the
		light
	t: when there are intersections, return the intersection is closer to the
		light.
*/
float	ray_intersects_cylinder(t_camera *ray, t_object *cy)
{
	float	t_side;
	float	t_top;
	float	t_bottom;
	float	t_closest;
	t_vec3	deviation;

	t_side = intersects_cylinder_side(ray, cy);
	deviation = vec3_scale((cy->orientation), cy->height / 2);
	t_top = intersects_cylinder_cap(ray, cy, vec3_add(cy->position, deviation));
	t_bottom = intersects_cylinder_cap(ray, cy,
			vec3_subtract(cy->position, deviation));
	t_closest = smallest_positive(t_side, t_bottom, t_top);
	if (t_closest < 0)
		return (-1);
	if (t_closest == t_side)
		cy->cy_hit_normal = get_side_hit_normal(ray, cy, t_side);
	else if (t_closest == t_top)
		cy->cy_hit_normal = cy->orientation;
	else
		cy->cy_hit_normal = vec3_scale(cy->orientation, -1);
	return (t_closest);
}
