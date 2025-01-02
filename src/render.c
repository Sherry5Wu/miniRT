/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:02 by arissane          #+#    #+#             */
/*   Updated: 2025/01/02 13:41:03 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//change the colour with a multiplier of the distance from the camera and clamp it to a range of 0-255
void	check_base_colour(t_object *object, t_colour *col, float t)
{
	float	depth;
	float	max_distance = 500.0f;

	depth = expf(-t / max_distance);//exponential decay
//	depth = 1.0f / (1.0f * t);//direct inverse decay
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

//Check what colour the pixel should be depending on if and how the camera rays hit the object
int	calculate_colour(t_minirt *mrt, t_vec2 *pixel)
{
	t_camera	camera_ray;
	t_colour	colour;
	float		t;
	float		t_temp;
	int		i;
	int		object_id;
	int		found_object;
	t_vec3		intersection;
	t_vec3		intersection_normal;
	t_vec3		scaled;
//	float	normal_x;
//	float	normal_y;

//test version without data from rt file:
//	normal_x = (2 * (pixel->x + 0.5) / WIN_WIDTH) - 1;
//	normal_y = (2 * (pixel->y + 0.5) / WIN_HEIGHT) - 1;
//	camera_ray.direction.x = normal_x;
//	camera_ray.direction.y = normal_y;
//	camera_ray.direction.z = mrt->camera.direction.z;
//	vec3_normalise(&camera_ray.direction);

//check if there is a sphere, since only spheres can be calculated currently
//this need to be changed to a function that finds the closest object once we have functions for planes and cylinders as well
	i = 0;
	t = -1;
	object_id = 0;
	found_object = 0;
	camera_ray = create_camera_ray(&mrt->camera, pixel);
	while (i < mrt->object_count)
	{
		if (mrt->object[i].shape == PLANE)
		{
			t_temp = ray_intersects_plane(mrt, &camera_ray, i);
			if (t_temp > 0 && (t_temp < t || t == -1))
			{
				object_id = i;
				t = t_temp;
			}
			found_object++;
		}
		else if (mrt->object[i].shape == SPHERE)
		{
			t_temp = ray_intersects_sphere(mrt, &camera_ray, i);
			if (t_temp > 0 && (t_temp < t || t == -1))
			{
				object_id = i;
				t = t_temp;
			}
			found_object++;
		}
		else if (mrt->object[i].shape == CYLINDER)
		{
			t_temp = ray_intersects_cylinder(mrt, &camera_ray, i);
			if (t_temp > 0 && (t_temp < t || t == -1))
			{
				object_id = i;
				t = t_temp;
			}
			found_object++;
		}
		i++;
	}
	if (found_object == 0)
		return (0x000000);

	if (t > 0)
	{
		check_base_colour(&mrt->object[object_id], &colour, t);

		scaled = vec3_scale(&camera_ray.direction, t);
		intersection = vec3_add(&mrt->camera.position, &scaled);
		intersection_normal = vec3_subtract(&intersection, &mrt->object[object_id].position);
		vec3_normalise(&intersection_normal);
		light_diffusion(&colour, intersection_normal, mrt->light.position);

		add_ambient_light(&colour, mrt->ambient.brightness);
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
