/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 10:39:02 by arissane          #+#    #+#             */
/*   Updated: 2025/01/21 12:14:42 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
/**
 * 	@brief
 * 	After getting the light brightness and diffusion intensity, then we change
 * 	the base colour.
 */
void	modulate_colour(t_colour *colour, float light_intensity)
{
	if (light_intensity < 0.0f)
		light_intensity = 0.0f;
	if (light_intensity > 1.0f)
		light_intensity = 1.0f;
	colour->red = (int)(colour->red * light_intensity);
	colour->green = (int)(colour->green * light_intensity);
	colour->blue = (int)(colour->blue * light_intensity);
}

/**
 * 	@brief
 * 	Add the colour to the image based on it's data address
 */
static void	put_pixel(t_minirt *mrt, t_vec2 *pixel, int colour)
{
	char	*dst;

	dst = mrt->data_addr + ((int)pixel->y * mrt->line_length
			+ (int)pixel->x * (mrt->bits_per_pixel / 8));
	*(unsigned int *)dst = colour;
}

/**
 *  @brief
 * 	Find the colour for each pixel and print the whole image on the screen
 * 	after it's complete
 */
void	render(t_minirt *mrt)
{
	int		colour;
	t_vec2	pixel;

	set_camera_light_position_info_for_objects(mrt);
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
