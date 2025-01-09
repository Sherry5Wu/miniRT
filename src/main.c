/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:53:49 by arissane          #+#    #+#             */
/*   Updated: 2025/01/07 15:16:55 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_controls(void)
{
	ft_putstr_fd("Select next object: =\n", 1);
	ft_putstr_fd("Select previous object: -\n", 1);
	ft_putstr_fd("Move the object with the arrow keys, control, and space\n", 1);
	ft_putstr_fd("Rotate the object's x, y and z axis with J, K, and L respectively\n", 1);
	ft_putstr_fd("\nCamera controls:\nMove in x and z axis with W, A, S, D\n", 1);
	ft_putstr_fd("Up and down with R, F\n", 1);
	ft_putstr_fd("Rotate with Q, E, Z, X\n", 1);
}

void	initialise(t_minirt *mrt)
{
	mrt->mlx = mlx_init();
	mrt->win = mlx_new_window(mrt->mlx, WIN_WIDTH, WIN_HEIGHT, "miniRT");
	mrt->img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
	mrt->data_addr = mlx_get_data_addr(mrt->img, &mrt->bits_per_pixel,
			&mrt->line_length, &mrt->endian);
}

int	main(int argc, char **argv)
{
	t_minirt	mrt;

	if (argc != 2 || argv[1] == NULL)
	{
		ft_putstr_fd("Invalid number of arguments", 2);
		return (1);
	}
	ft_bzero(&mrt, sizeof(t_minirt));
	initialise(&mrt);
	if (read_rt_file(&mrt, argv[1]) == 1)
		return (1);
	render(&mrt);
	print_controls();
	mlx_hook(mrt.win, 17, 0, end_event, &mrt);
	mlx_key_hook(mrt.win, key_input, &mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
