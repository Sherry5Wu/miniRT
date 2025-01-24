/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:32:19 by arissane          #+#    #+#             */
/*   Updated: 2025/01/16 09:45:39 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	scene_controls(int keycode, t_minirt *mrt, int object_id)
{
	if (object_controls(keycode, mrt, object_id) == 0)
		return (0);
	else if (light_controls(keycode, &mrt->light) == 0)
		return (0);
	else if (camera_controls(keycode, &mrt->camera) == 0)
		return (0);
	else if (adjust_ambient_brightness(keycode, &mrt->ambient) == 0)
		return (0);
	else
		return (1);
}

static void	display_type(int type)
{
	if (type == PLANE)
		ft_putstr_fd(" type = plane\n", 1);
	else if (type == SPHERE)
		ft_putstr_fd(" type = sphere\n", 1);
	else if (type == CYLINDER)
		ft_putstr_fd(" type = cylinder\n", 1);
}

static int	display_values(int keycode, t_minirt *mrt, int *object_id)
{
	if (keycode == 61)
	{
		(*object_id)++;
		if (*object_id >= mrt->object_count)
			(*object_id) = 0;
		ft_printf("Selected object id = %d", mrt->object[*object_id].id);
		display_type(mrt->object[*object_id].shape);
	}
	else if (keycode == 45)
	{
		(*object_id)--;
		if (*object_id < 0)
			(*object_id) = mrt->object_count - 1;
		ft_printf("Selected object id = %d", mrt->object[*object_id].id);
		display_type(mrt->object[*object_id].shape);
	}
	else
		return (1);
	return (0);
}

int	key_input(int keycode, t_minirt *mrt)
{
	static int	object_id;

	if (!object_id)
		object_id = 0;
	if (keycode == 65307)
		free_window(mrt);
	else if (display_values(keycode, mrt, &object_id) == 0)
		return (0);
	else if (scene_controls(keycode, mrt, object_id) == 0)
	{
		if (mrt->img)
		{
			mlx_destroy_image(mrt->mlx, mrt->img);
			mrt->img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
		}
		render(mrt);
	}
	else
	{
		if (keycode != 65293)
			ft_printf("Entered key == %d\n", keycode);
		return (1);
	}
	return (0);
}
