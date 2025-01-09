/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:53:16 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/09 14:24:27 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief
 * cylinder equation is |(P-C) - [(P-C)*N]*N|^2 = r^2
 * 		P is a point on the cylinder surface
 * 		C is a point on the cylinder axis(cap)
 * 		N is cylinder direction
 * P is the R(t) = O + tD
 * The eqaution is: |(O + tD - C) - [(O + tD - C)*N]*N|^2 = r^2
 * set V = O-C
 * 		|V + tD - (V*N + tD*N)*N|^2 - r^2 = 0
 * 		|t[D - (D*N)N] + [V-(V*N)N]|^2 - r^2 = 0
 * 		t^2*[D-(D*N)N]^2 + 2t*[D-(D*N)N]*[V-(V*N)N] + [V-(V*N)N]^2 -r^2 = 0
 * So at^2 + bt + c = 0:
 * 		a = [D-(D*N)N]^2 = D*D -2(D*N)^2 + (D*N)^2*N^2
 * 		b = 2*[D-(D*N)N]*[V-(V*N)N] = 2*(D*V - D(V*N)N -V(D*N)N + (D*N)(V*N)*N^2
 * 		c = [V-(V*N)N]^2 -r^2 = V^2 - 2(V*N)^2 + (V*N)^2*N^2 - r^2
 * as normal * normal = 1, so D*D = N*N = 1
 * 		a = 1 - (D*N)^2
 * 		b = 2 * [D*V - (D*N)(V*N)]
 * 		c = V^2 - (V*N)^2 - r^2
 *
 * @param vec vector from ray origin to cylinder cap center
 * @param dn dot_product(D, N), D is ray normal, N is cylinder norml
 * @param vn dot_product(vec, N)
 */
static void	set_cyl_equation(t_camera *ray, t_object *cy, t_equation *eq)
{
	t_vec3	vector;
	float	dn;
	float	vn;
	t_vec3	top_center;

	top_center = vec3_add(cy->position,
		vec3_scale(cy->orientation, -cy->height * 0.5));// does it matter it is cy->height or -cy->height
	vector = vec3_subtract(ray->position,top_center);
	dn = vec3_dot(ray->direction, cy->orientation);
	vn = vec3_dot(vector, cy->orientation);
	eq->a = 1 - powf(dn, 2);
	eq->b = 2 * (vec3_dot(ray->direction, vector) - (dn * vn));
	eq->c = vec3_dot(vector, vector) - powf(vn ,2) - powf(cy->radius, 2);
	eq->discriminant = powf(eq->b, 2) - 4 * eq->a * eq->c;
	eq->t1 = -1;
	eq->t2 = -1;
}

/**
 * 	@brief
 * 	Check if there is valid hit on the side of a cylinder.
 *
 * 	@param
 *
 */
static float	intersects_cylinder_side(t_camera *ray, t_object *cy,
	float t)
{
	t_vec3	vector;
	t_vec3	hit;
	t_vec3	hit_a;
	float	offset;
	float	length;

	if (t < DIFFER)
		return (-1);
	hit = vec3_add(ray->position, vec3_scale(ray->direction, t));
	vector = vec3_subtract(ray->position, cy->cap_t);
	offset = vec3_dot(ray->direction, cy->orientation) * t
		+ vec3_dot(vector, cy->orientation);
	hit_a = vec3_add(cy->cap_t, vec3_scale(cy->orientation, offset));
	length = vec3_length(vec3_subtract(hit, hit_a));
	offset -= DIFFER;
	length -= DIFFER;
	if (offset >= 0 && offset <= cy->height && length <= cy->radius)
	{
		cy->cy_hp = hit_a;
		return (t);
	}
	return (-1);
}
/*
	@function
	To caculate the intersection on the top/bottom of a cylinder.

	@return
	return the intersection if there is one; otherwise, return -1.
*/

static float	intersects_cylinder_cap(t_camera *ray, t_object *cy,
t_vec3 center)
{
	t_object	plane;
	t_vec3		point;
	float		offset;
	float		t;

	plane.position = center;
	plane.orientation = cy->orientation;// why here is equal to cy normal?
	plane.colour = cy->colour; // why she sets it as black.
	t = ray_intersects_plane(ray, &plane);
	if (t != -1)
	{
		point = vec3_add(ray->position, vec3_scale(ray->direction, t));
		offset = vec3_length(vec3_subtract(point, center));
		if (offset <= cy->radius)// what the others conditions for?
		{
			cy->cy_hp = center;
			return (t);
		}
	}
	return (-1);
}

float	solve_equation(t_equation *eq)
{
	if (eq->a == 0.0 && eq->b == !0.0)
	{
		eq->t1 = -eq->c / eq->b;
		return (0);
	}
	else
	{
		if (eq->discriminant < 0)
			return (-1);
		eq->t1 = (-eq->b - sqrtf(eq->discriminant)) / 2 * eq->a;
		eq->t2 = (-eq->b + sqrtf(eq->discriminant)) / 2 * eq->a;
	}
	return (eq->discriminant);
}
static float	find_smaller_positive(float t1,  float t2)
{
	if (t1 > t2 && t2 > 0)
		return (t2);
	else if (t2 > t1 && t1 > 0)
		return (t1);
	else if (t1 < 0 && t2 < 0)
		return (-1);
	else if (t1 > 0)
		return (t1);
	else
		return (t2);
}

/**
 * 	@brief
 * 	check if there is any hit point.
 * 	It will check the side first, if both t are valid, then don't need to check
 * 	on the top and bottom any more; If the valid t is less than 2, then need
 * 	to check top and bottom too.
 */
static float	hit_check_cylinder(t_camera *ray, t_object *cy, t_equation *eq)
{
	float	smallest_t;
	float	t1;
	float	t2;

	smallest_t = -1;
	t1 = intersects_cylinder_side(ray, cy, eq->t1);
	t2 = intersects_cylinder_side(ray, cy, eq->t2);
	if (t1 == -1 || t2 == -1)
	{
		smallest_t = find_smaller_positive(t1, t2);
		t1 = intersects_cylinder_cap(ray, cy, cy->cap_t);// top
		if (t1 > 0 && smallest_t < t1)
			smallest_t = t1;
		t2 = intersects_cylinder_cap(ray, cy, cy->cap_b);// bottom
		if (t2 > 0 && smallest_t < t2)
			smallest_t = t2;
	}
	if (smallest_t < 0)
		return (-1);
	return (smallest_t);
}

float	ray_intersects_cylinder(t_camera *ray, t_object *cy)
{
	t_equation	eq;

	set_cyl_equation(ray, cy, &eq);
	if (solve_equation(&eq) != -1 && (eq.t1 > DIFFER || eq.t2 > DIFFER))
		return (hit_check_cylinder(ray, cy, &eq));
	return (-1);
}

