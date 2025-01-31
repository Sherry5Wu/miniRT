/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_colours.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 11:42:45 by arissane          #+#    #+#             */
/*   Updated: 2025/01/30 12:57:02 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * 	@brief
 * 	After getting the light brightness and diffusion intensity, then we change
 * 	the base colour.
 */
void	modulate_colour(t_minirt *mrt, t_colour *final, float light_intensity)
{
	if (light_intensity < 0.0f)
		light_intensity = 0.0f;
	if (light_intensity > 1.0f)
		light_intensity = 1.0f;
	final->red = (int)(mrt->base_colour.red * light_intensity)
		+ mrt->ambient_added.red;
	final->green = (int)(mrt->base_colour.green * light_intensity)
		+ mrt->ambient_added.green;
	final->blue = (int)(mrt->base_colour.blue * light_intensity)
		+ mrt->ambient_added.blue;
	if (final->red > 255)
		final->red = 255;
	if (final->green > 255)
		final->green = 255;
	if (final->blue > 255)
		final->blue = 255;
}

void	add_ambient(t_minirt *mrt)
{
	mrt->ambient_added.red = (mrt->base_colour.red
			* mrt->ambient.colour.red
			* mrt->ambient.brightness) / 255;
	mrt->ambient_added.green = (mrt->base_colour.green
			* mrt->ambient.colour.green
			* mrt->ambient.brightness) / 255;
	mrt->ambient_added.blue = (mrt->base_colour.blue
			* mrt->ambient.colour.blue
			* mrt->ambient.brightness) / 255;
	if (mrt->ambient_added.red > 255)
		mrt->ambient_added.red = 255;
	if (mrt->ambient_added.green > 255)
		mrt->ambient_added.green = 255;
	if (mrt->ambient_added.blue > 255)
		mrt->ambient_added.blue = 255;
	if (mrt->ambient_added.red < 0)
		mrt->ambient_added.red = 0;
	if (mrt->ambient_added.green < 0)
		mrt->ambient_added.green = 0;
	if (mrt->ambient_added.blue < 0)
		mrt->ambient_added.blue = 0;
}
