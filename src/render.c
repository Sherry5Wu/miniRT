/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:02 by arissane          #+#    #+#             */
/*   Updated: 2025/01/15 14:02:42 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 *  @brief
 * 	change the colour with a multiplier of the distance from the camera and
 * 	clamp it to a range of 0-255
 */
void	check_base_colour(t_object *object, t_colour *col, float t)
{
	float	depth;
	float	max_distance = 500.0f;

	depth = expf(-t / max_distance);//exponential decay
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
 * 	To check if between the light and the intersection(hit_point), there are
 * 	another objects or not. If there is one, then the intersection is obscured;
 * 	otherwise, it isn't obscured.
 *
 * 	@details
 * 	1. get the light_ray's position and direction(normal);
 * 	2. get the distance between the intersection and the light;
 * 	3. Loop the objects in the scene, if the current the ob is the inter_ob,
 * 	   then continue; otherwise, using is_intersected function to check if
 * 	   there is a intersection , and the distance to the light is shorter than
 * 	   the checked_intersection, then it is obscured.
 *
 * 	@return
 * 	true : it is obsucred;
 * 	false: it is not obscured;
 */
bool	is_obscured_from_hitpoint_to_light(t_object *ob, t_minirt *mrt,
	t_camera *c_ray, float t)
{
	t_vec3		hit_p;
	t_camera	light_ray;
	float		distance;
	int			i;
	(void)ob;
	i = -1;
	hit_p = vec3_add(c_ray->position, vec3_scale(c_ray->direction, t));
	light_ray.position = vec3_add(hit_p, VEC_MIN);
	light_ray.direction = vec3_subtract(mrt->light.position, hit_p);
	vec3_normalise(&light_ray.direction);
	distance = vec3_length(vec3_subtract(mrt->light.position, hit_p));
	while (++i < mrt->object_count)
	{
		if (mrt->object[i].id == ob->id)
			continue ;
		if (is_intersected(&light_ray, &mrt->object[i], &distance) == true
			&& distance <
				vec3_length(vec3_subtract(mrt->light.position, hit_p)))
			return (true);
	}
	return (false);
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
	int	i;
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
	int		i;
	int		object_id;
	float	intensity;

	i = -1;
	t = -1;
	object_id = 0;
	intensity = 0;
	camera_ray = create_camera_ray(&mrt->camera, pixel);
	check_intersection(mrt, &camera_ray, &t, &object_id);
	if (t > 0)
	{
		check_base_colour(&mrt->object[object_id], &colour, t);
		if (is_obscured_from_hitpoint_to_light(&mrt->object[object_id],
			mrt, &camera_ray, t) == false)
			intensity = diffusion(mrt, &camera_ray, &mrt->object[object_id],t);
		intensity += mrt->ambient.brightness;
		modulate_colour(&colour, intensity);
		return((colour.red << 16) | (colour.green << 8) | colour.blue);
	}
	return (0x000000);
}

//Add the colour to the image based on it's data address
static void	put_pixel(t_minirt *mrt, t_vec2 *pixel, int colour)
{
	char	*dst;

	dst = mrt->data_addr + ((int)pixel->y * mrt->line_length
		+ (int)pixel->x * (mrt->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

//Find the colour for each pixel and print the whole image on the screen after it's complete
void	render(t_minirt *mrt)
{
	int		colour;
	t_vec2	pixel;

	pixel.y = 0;
	while (pixel.y < WIN_HEIGHT)
	{
		pixel.x = 0;
		while (pixel.x < WIN_WIDTH)
		{
			colour = calculate_colour(mrt, &pixel);
			put_pixel(mrt, &pixel, colour);
			pixel.x++;
		}
		pixel.y++;
	}
	mlx_put_image_to_window(mrt->mlx, mrt->win, mrt->img, 0, 0);
}
