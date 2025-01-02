/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:26:40 by arissane          #+#    #+#             */
/*   Updated: 2025/01/02 12:27:14 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_ambient_light(t_colour *colour, float light_intensity)
{
	colour->red = (int)(colour->red + light_intensity * 255);
	colour->green = (int)(colour->green + light_intensity * 255);
	colour->blue = (int)(colour->blue + light_intensity * 255);
	if (colour->red > 255)
		colour->red = 255;
	if (colour->green > 255)
		colour->green = 255;
	if (colour->blue > 255)
		colour->blue = 255;
}
