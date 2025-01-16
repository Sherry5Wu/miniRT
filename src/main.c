/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:53:49 by arissane          #+#    #+#             */
/*   Updated: 2025/01/15 10:50:14 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_controls(void)
{
	ft_putstr_fd("Select next object: =\n", 1);
	ft_putstr_fd("Select previous object: -\n", 1);
	ft_putstr_fd("Move the object with arrow keys, control and space\n", 1);
	ft_putstr_fd("Rotate the object's x, y and z axis with ", 1);
	ft_putstr_fd("J, K, and L respectively\n", 1);
	ft_putstr_fd("Resize object diameter with < and >\n", 1);
	ft_putstr_fd("Resize object height with N and M\n", 1);
	ft_putstr_fd("\nCamera controls:\nMove in x and z axis with W, A, S, D\n", 1);
	ft_putstr_fd("Up and down with R, F\n", 1);
	ft_putstr_fd("Rotate with Q, E, Z, X\n", 1);
	ft_putstr_fd("\nLight controls:\nMove in x and z axis with numpad 8, 4, 5, 6\n", 1);
	ft_putstr_fd("Up and down with numpad 7, 1\nAdjust brightness with numpad 9, 3\n", 1);
	ft_putstr_fd("\nAdjust ambient light brightness with  [ and ]\n", 1);
	ft_putstr_fd("\n*****************************************************\n", 1);
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
	if (read_rt_file(&mrt, argv[1]) == 1)
		return (1);
	initialise(&mrt);
	render(&mrt);
	print_controls();
	mlx_hook(mrt.win, 17, 0, end_event, &mrt);
	mlx_key_hook(mrt.win, key_input, &mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
