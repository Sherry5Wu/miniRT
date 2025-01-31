/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_controls.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:10:59 by arissane          #+#    #+#             */
/*   Updated: 2025/01/22 09:45:51 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	adjust_ambient_brightness(int keycode, t_ray *ambient)
{
	if (keycode == 93)
	{
		ambient->brightness += 0.1;
		if (ambient->brightness > 1.0)
			ambient->brightness = 0.0;
	}
	else if (keycode == 91)
	{
		ambient->brightness -= 0.1;
		if (ambient->brightness < 0.0)
			ambient->brightness = 1.0;
	}
	else
		return (1);
	return (0);
}

static int	adjust_light_brightness(int keycode, t_ray *light)
{
	if (keycode == 65434)
	{
		light->brightness += 0.1;
		if (light->brightness > 1.0)
			light->brightness = 0.0;
	}
	else if (keycode == 65435)
	{
		light->brightness -= 0.1;
		if (light->brightness < 0.0)
			light->brightness = 1.0;
	}
	else
		return (1);
	return (0);
}

int	light_controls(int keycode, t_ray *light)
{
	if (keycode == 65431)
		light->position.z += 0.5;
	else if (keycode == 65437)
		light->position.z -= 0.5;
	else if (keycode == 65430)
		light->position.x -= 0.5;
	else if (keycode == 65432)
		light->position.x += 0.5;
	else if (keycode == 65429)
		light->position.y += 0.5;
	else if (keycode == 65436)
		light->position.y -= 0.5;
	else if (adjust_light_brightness(keycode, light) == 0)
		return (0);
	else
		return (1);
	return (0);
}
