/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:15:56 by arissane          #+#    #+#             */
/*   Updated: 2025/01/30 11:11:01 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_window(t_minirt *mrt)
{
	if (!mrt)
		return ;
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
	exit (1);
}

int	end_event(t_minirt *mrt)
{
	free_window(mrt);
	return (0);
}

void	fatal_error(char *message, int error)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	exit (error);
}
