/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersects_cylinder_side.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:48:45 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/21 09:12:42 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
	@brief
	calculate the a,b,c values and save them into t_equation *eq for later use.
*/
static void	set_cyl_equation(t_camera *ray, t_object *cylinder, t_equation *eq)
{
	t_vec3	ray_to_cyl;
	t_vec3	d_perpendicular;
	t_vec3	oc_project;
	t_vec3	oc_perpendicular;

	ray_to_cyl = vec3_subtract(ray->position, cylinder->position);
	d_perpendicular = vec3_subtract(ray->direction,
			vec3_project((ray->direction), (cylinder->orientation)));
	oc_project = vec3_project((ray_to_cyl), (cylinder->orientation));
	oc_perpendicular = vec3_subtract(ray_to_cyl, oc_project);
	eq->a = vec3_dot(d_perpendicular, d_perpendicular);
	eq->b = 2 * vec3_dot(d_perpendicular, oc_perpendicular);
	eq->c = vec3_dot(oc_perpendicular, oc_perpendicular)
		-(cylinder->radius) * (cylinder->radius);
	eq->discriminant = eq->b * eq->b - 4 * eq->a * eq->c;
	eq->t1 = -1;
	eq->t2 = -1;
}

static float	get_closest_t(float *t, float *t_closest, t_camera *ray,
	t_object *cy)
{
	int		i;
	float	tmp;
	t_vec3	hit_point;
	t_vec3	center_to_point;
	float	h;

	i = -1;
	while (++i < 2)
	{
		tmp = t[i];
		if (tmp < 0)
			continue ;
		hit_point = vec3_add(ray->position, vec3_scale(ray->direction, tmp));
		center_to_point = vec3_subtract(hit_point, cy->position);
		h = vec3_dot(center_to_point, cy->orientation);
		if (h >= -cy->height / 2 && h <= cy->height / 2)
		{
			if (*t_closest < 0 || tmp < *t_closest)
				*t_closest = tmp;
		}
	}
	return (*t_closest);
}

/*
	@function
	To calculate the intersections on the side of a cylinder. If there are two
	intersections,it will return the one closer to the camera.

	@return
	the closer intersection.
*/
float	intersects_cylinder_side(t_camera *ray, t_object *cylinder)
{
	t_equation	eq;
	float		t[2];
	float		t_closest;

	set_cyl_equation(ray, cylinder, &eq);
	if (eq.discriminant < 0)
		return (-1);
	t_closest = -1;
	t[0] = (-eq.b - sqrt(eq.discriminant)) / (2 * eq.a);
	t[1] = (-eq.b + sqrt(eq.discriminant)) / (2 * eq.a);
	return (get_closest_t(t, &t_closest, ray, cylinder));
}
