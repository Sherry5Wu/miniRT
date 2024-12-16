/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:53:49 by arissane          #+#    #+#             */
/*   Updated: 2024/12/12 15:09:09 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	initialise(t_minirt *mrt)
{
	mrt->mlx = mlx_init();
	mrt->win = mlx_new_window(mrt->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	mrt->img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
	mrt->data_addr = mlx_get_data_addr(mrt->img, &mrt->bits_per_pixel,
			&mrt->line_length, &mrt->endian);
}

int	main(void)
{
	t_minirt	mrt;

	initialise(&mrt);
	create_scene(&mrt);
	render(&mrt);
	mlx_hook(mrt.win, 17, 0, end_event, &mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
