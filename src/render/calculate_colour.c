/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_colour.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:13:34 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/30 12:55:33 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *  @brief
 * 	change the colour with a multiplier of the distance from the camera and
 * 	clamp it to a range of 0-255
 */
static void	check_base_colour(t_object *object, t_minirt *mrt, float t)
{
	float	depth;
	float	max_distance;

	max_distance = 500.0f;
	depth = expf(-t / max_distance);
	mrt->base_colour.red = (object->colour.red * depth);
	mrt->base_colour.green = (object->colour.green * depth);
	mrt->base_colour.blue = (object->colour.blue * depth);
	if (mrt->base_colour.red > 255)
		mrt->base_colour.red = 255;
	if (mrt->base_colour.green > 255)
		mrt->base_colour.green = 255;
	if (mrt->base_colour.blue > 255)
		mrt->base_colour.blue = 255;
	mrt->ambient_added.red = mrt->base_colour.red;
	mrt->ambient_added.green = mrt->base_colour.green;
	mrt->ambient_added.blue = mrt->base_colour.blue;
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

static float	update_intensity(t_object *ob, t_minirt *mrt,
	t_camera *camera_ray, float t)
{
	float	intensity;

	intensity = 0.0;
	if (is_obscured_from_hitpoint_to_light(ob, mrt, camera_ray, t) == false)
		intensity = diffusion(mrt, camera_ray, ob, t);
	return (intensity);
}

/**
 *  @brief
 * 	Check what colour the pixel should be depending on if and how the camera
 * 	rays hit the object
 */
int	calculate_colour(t_minirt *mrt, t_vec2 *pixel)
{
	t_camera	camera_ray;
	t_colour	final;
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
		check_base_colour(&mrt->object[id], mrt, t);
		add_ambient(mrt);
		if (mrt->light_on_surface == false)
		{
			if (mrt->object[id].camera_inside == mrt->object[id].light_inside)
				intensity = update_intensity(&mrt->object[id], mrt,
						&camera_ray, t);
		}
		modulate_colour(mrt, &final, intensity);
		return ((final.red << 16) | (final.green << 8) | final.blue);
	}
	return (0x000000);
}
