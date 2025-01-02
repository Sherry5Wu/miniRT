/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_source.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 12:25:53 by arissane          #+#    #+#             */
/*   Updated: 2025/01/02 12:26:24 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	light_diffusion(t_colour *colour, t_vec3 normal, t_vec3 light_direction)
{
	float	diffusion;

	diffusion = vec3_dot(&normal, &light_direction);
	if (diffusion < 0.0f)
		diffusion = 0.0f;
	colour->red = (int)(colour->red * diffusion);
	colour->green = (int)(colour->green * diffusion);
	colour->blue = (int)(colour->blue * diffusion);
}
