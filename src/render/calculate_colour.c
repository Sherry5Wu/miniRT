/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:13:34 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/22 09:48:31 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *  @brief
 * 	change the colour with a multiplier of the distance from the camera and
 * 	clamp it to a range of 0-255
 */
static void	check_base_colour(t_object *object, t_colour *col, float t)
{
	float	depth;
	float	max_distance;

	max_distance = 500.0f;
	depth = expf(-t / max_distance);
	col->red = (object->colour.red * depth);
	col->green = (object->colour.green * depth);
	col->blue = (object->colour.blue * depth);
	if (col->red > 255)
		col->red = 255;
	if (col->green > 255)
		col->green = 255;
	if (col->blue > 255)
		col->blue = 255;
}

/**
 * 	@brief
 * 	To check if the ray with the passed shape has intersections. If there are
 * 	intersections, then save the closest distance t into *t.
 *
 * @return
 * 	true: there is intersection;
 * 	alse: no intersections;
 */
bool	is_intersected(t_camera *ray, t_object *ob, float *t)
{
	if (ob->shape == PLANE)
		*t = ray_intersects_plane(ray, ob);
	else if (ob->shape == SPHERE)
		*t = ray_intersects_sphere(ray, ob);
	else if (ob->shape == CYLINDER)
		*t = ray_intersects_cylinder(ray, ob);
	if (*t > 0)
		return (true);
	return (false);
}

static void	check_intersection(t_minirt *mrt, t_camera *camera_ray,
	float *t, int *object_id)
{
	int		i;
	float	t_temp;

	i = -1;
	t_temp = -1;
	while (++i < mrt->object_count)
	{
		if (is_intersected(camera_ray, &mrt->object[i], &t_temp) == true
			&& (t_temp < *t || *t == -1))
		{
			*object_id = i;
			*t = t_temp;
		}
	}
}

/**
 *  @brief
 * 	Check what colour the pixel should be depending on if and how the camera
 * 	rays hit the object
 */
int	calculate_colour(t_minirt *mrt, t_vec2 *pixel)
{
	t_camera	camera_ray;
	t_colour	colour;
	float		t;
	int			id;
	float		intensity;

	t = -1;
	id = 0;
	intensity = 0;
	camera_ray = create_camera_ray(&mrt->camera, pixel);
	check_intersection(mrt, &camera_ray, &t, &id);
	if (t > 0)
	{
		check_base_colour(&mrt->object[id], &colour, t);
		if (mrt->object[id].camera_inside == mrt->object[id].light_inside)
		{
			if (is_obscured_from_hitpoint_to_light(&mrt->object[id],
					mrt, &camera_ray, t) == false)
				intensity = diffusion(mrt, &camera_ray, &mrt->object[id], t);
		}
		intensity += mrt->ambient.brightness;
		modulate_colour(&colour, intensity);
		return ((colour.red << 16) | (colour.green << 8) | colour.blue);
	}
	return (0x000000);
}
