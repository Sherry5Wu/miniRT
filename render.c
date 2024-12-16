/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:02 by arissane          #+#    #+#             */
/*   Updated: 2024/12/12 15:09:33 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ray_intersects_sphere(t_minirt *mrt, t_ray *camera_ray)
{
	t_vec3	oc;
	float	a;
	float	b;
	float	c;
	float	discriminant;

	oc = vec3_substract(&mrt->camera.position, &mrt->object[0].position);
	a = vec3_dot(&camera_ray->orientation, &camera_ray->orientation);
	b = 2.0f * vec3_dot(&oc, &camera_ray->orientation);
	c = vec3_dot(&oc, &oc) - mrt->object[0].radius * mrt->object[0].radius;
	discriminant = b * b - 4.0f * a * c;
	if (discriminant > 0)
	{
		return (1);
	}
	return (0);
}

int	calculate_colour(t_minirt *mrt, t_vec2 *pixel)
{
	t_ray	camera_ray;
	float	normal_x;
	float	normal_y;

	normal_x = (2 * (pixel->x + 0.5) / WIN_WIDTH) - 1;
	normal_y = (2 * (pixel->y + 0.5) / WIN_HEIGHT) - 1;
	camera_ray.orientation.x = normal_x;
	camera_ray.orientation.y = normal_y;
	camera_ray.orientation.z = mrt->camera.orientation.z;
	vec3_normalise(&camera_ray.orientation);

	if (ray_intersects_sphere(mrt, &camera_ray))
	{
		return(0xFFFFFF);
	}
	return (0x000000);
}

static void	put_pixel(t_minirt *mrt, t_vec2 *pixel, int colour)
{
	char	*dst;

	dst = mrt->data_addr + ((int)pixel->y * mrt->line_length
		+ (int)pixel->x * (mrt->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

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
