/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder 1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 08:53:16 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/08 10:04:05 by jingwu           ###   ########.fr       */
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
static void	set_cyl_equation(t_camera *ray, t_object *cylinder, t_equation *eq)
{
	t_vec3	vector;
	float	dn;
	float	vn;
	t_vec3	top_center;

	top_center = vec3_add(&cylinder->position, );
	vector = vec3_subtract(&ray->position,)
}

/*
	@function
	To caculate the intersections on the side of a cylinder. If there are two
	intersections,it will return the one closer to the camera.

	@return
	the closer intersection.
*/
static float	intersects_cylinder_side(t_camera *ray, t_object *cylinder)
{
	t_equation	eq;
	float	t[2];
	t_vec3	point;
	t_vec3 scale;
	t_vec3 vector;
	float	t_closest;
	float	tmp;
	int		i;
	float	h;

	set_cyl_equation(ray, cylinder, &eq);
	if (eq.discriminant < 0)
		return (-1);
	t_closest = -1;
	t[0] = -1;
	t[1] = -1;
	i = 0;
	t[0] = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	t[1] = (-eq.b + sqrt(eq.discriminant)) / (2 * eq.a);
	while (i < 2)
	{
        tmp = t[i];
		if (tmp < 0)
			continue; // Ignore intersections behind the ray
        // Compute intersection point
		scale = vec3_scale(&ray->direction, tmp);
        point = vec3_add(&ray->position, &scale);
        // Check if point lies within cylinder height
		vector = vec3_subtract(&point, &cylinder->position);
        h = vec3_dot(&vector, &cylinder->orientation);
        if (h >= 0 && h <= cylinder->height)
		{
            if (t_closest < 0 || tmp < t_closest)
                t_closest = tmp;
        }
		i++;
    }
    return t_closest;
}
/*
	@function
	To caculate the intersection on the top/bottom of a cylinder.

	@return
	return the intersection if there is one; otherwise, return -1.
*/

static float	intersects_cylinder_cap(t_camera *ray, t_object *cylinder,
t_vec3 center)
{
	float	denom;
	float	t;
	float	distance;
	t_vec3	center_to_ray;
	t_vec3	hit_point;
	t_vec3	vec_scale;
	t_vec3	vector;

	denom = vec3_dot(&ray->direction,&(cylinder->orientation));
	if (fabs(denom) < DIFFER)
		return (-1);
	center_to_ray = vec3_subtract(&center, &ray->position);
	t = vec3_dot(&center_to_ray, &cylinder->orientation) / denom;
	if ( t < 0)
		return (-1);// the disk is at back of the cramer
	vec_scale = vec3_scale(&ray->direction, t);
	hit_point = vec3_add(&ray->position, &vec_scale);
	vector = vec3_subtract(&hit_point, &center);
	distance = vec3_length(&vector);
	if ( distance > cylinder->radius)
		return (-1);
	return (t);
}

float smallest_positive(float a, float b, float c)
{
    float smallest;
    int found_positive;

	found_positive = 0;
	smallest = -1;
    if (a > 0)
	{
        smallest = a;
        found_positive = 1;
    }
    if (b > 0 && b < smallest)
	{
        smallest = b;
        found_positive = 1;
    }
    if (c > 0 && c < smallest)
	{
        smallest = c;
        found_positive = 1;
    }
	if (found_positive == 0)
		return (-1);
    return (smallest);
}


float	ray_intersects_cylinder(t_camera *ray, t_object *cylinder)
{
	t_equation	eq;
	float		t;

	set_cyl_equation(ray, cylinder, &eq);

	if (t_closest < 0)
		return (-1);
	return (t_closest);
}

