/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modulate_colour.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:26:40 by arissane          #+#    #+#             */
/*   Updated: 2025/01/15 09:53:47 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	modulate_colour(t_colour *colour, float light_intensity)
{
	if (light_intensity < 0.0f)
		light_intensity = 0.0f;
	if (light_intensity > 1.0f)
		light_intensity = 1.0f;
	colour->red = (int)(colour->red * light_intensity);
	colour->green = (int)(colour->green * light_intensity);
	colour->blue = (int)(colour->blue * light_intensity);
	// if (colour->red > 255)
	// 	colour->red = 255;
	// if (colour->green > 255)
	// 	colour->green = 255;
	// if (colour->blue > 255)
	// 	colour->blue = 255;
}
