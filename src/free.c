/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:15:56 by arissane          #+#    #+#             */
/*   Updated: 2024/12/09 10:24:50 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_window(t_minirt *mrt)
{
	if (!mrt)
		exit(0);
	if (mrt->img)
		mlx_destroy_image(mrt->mlx, mrt->img);
	if (mrt->win && mrt->mlx)
		mlx_destroy_window(mrt->mlx, mrt->win);
	if (mrt->mlx)
	{
		mlx_loop_end(mrt->mlx);
		mlx_destroy_display(mrt->mlx);
		free(mrt->mlx);
	}
	if (mrt->object)
		free(mrt->object);
	exit(0);
}

int	end_event(t_minirt *mrt)
{
	free_window(mrt);
	return (0);
}
