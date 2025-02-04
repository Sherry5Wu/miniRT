/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:53:49 by arissane          #+#    #+#             */
/*   Updated: 2025/02/04 09:10:49 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_controls(void)
{
	ft_putstr_fd(BL"Object controls:\n"RS GR" - Selection:"RS" =/-\n", 1);
	ft_putstr_fd(GR" - Translation:\n"RS"     * -x/+x: ←/→\n     ", 1);
	ft_putstr_fd("* +y/-y: Space/Ctrl\n     * +z/-z:  ↑/↓\n", 1);
	ft_putstr_fd(GR" - Rotation\n"RS"     * X-axis: J\n     ", 1);
	ft_putstr_fd("* Y-axis: K\n     * Z-axis: L\n", 1);
	ft_putstr_fd(GR" - Resize\n"RS"     * Diameter(-/+): ,/.\n     ", 1);
	ft_putstr_fd("* Height(-/+): N/M\n", 1);
	ft_putstr_fd(BL"\nCamera controls(based on global x,y and z):\n"RS
		GR" - Translation\n"RS, 1);
	ft_putstr_fd("     * -x/+x: A/D\n     * +y/-y: R/F\n     ", 1);
	ft_putstr_fd("* +z/-z: W/S\n", 1);
	ft_putstr_fd(GR" - Rotation\n"RS"     * X-axis(up/down): Z/X\n     ", 1);
	ft_putstr_fd("* Y-axis(left/right): Q/E\n     * Z-axis(left/right): "
		"C/V\n", 1);
	ft_putstr_fd(BL"\nLight controls:\n"RS GR" - Translation\n"RS"     * "
		"-x/+x: 4/6\n     * +y/-y: 7/1\n     * +z/-z: 8/5\n",
		1);
	ft_putstr_fd(GR" - Brightness(-/+): "RS"9/3\n\n", 1);
	ft_putstr_fd(BL"Ambient Light\n"RS GR" - Brightness(-/+):"RS" [/]\n", 1);
	ft_putstr_fd(BL"\n************************************************\n"RS, 1);
}

static int	check_number_of_elements(t_minirt *mrt)
{
	if (mrt->camera_count == 0 || mrt->ambient_count == 0
		|| mrt->light_count == 0 || mrt->object_count == 0)
	{
		ft_putstr_fd("Error\n", 2);
		if (mrt->camera_count == 0)
			ft_putstr_fd("No camera found in the rt file\n", 2);
		if (mrt->ambient_count == 0)
			ft_putstr_fd("No ambient light found in the rt file\n", 2);
		if (mrt->light_count == 0)
			ft_putstr_fd("No light found in the rt file\n", 2);
		if (mrt->object_count == 0)
			ft_putstr_fd("No objects found in the rt file\n", 2);
		if (mrt->object)
			free(mrt->object);
		return (1);
	}
	return (0);
}

static void	initialise(t_minirt *mrt, char *filename)
{
	int		i;
	char	*name;

	i = 0;
	name = filename;
	while (filename[i])
	{
		if (filename[i] == '/' && filename[i + 1])
			name = &filename[i + 1];
		i++;
	}
	mrt->mlx = mlx_init();
	if (!mrt->mlx)
		fatal_error("mlx init failed", ENOMEM);
	mrt->win = mlx_new_window(mrt->mlx, WIN_WIDTH, WIN_HEIGHT, name);
	if (!mrt->win)
		fatal_error("mlx init window failed", ENOMEM);
	mrt->img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!mrt->img)
		fatal_error("mlx init image failed", ENOMEM);
	mrt->data_addr = mlx_get_data_addr(mrt->img, &mrt->bits_per_pixel,
			&mrt->line_length, &mrt->endian);
	if (!mrt->data_addr)
		fatal_error("mlx init data addresses failed", ENOMEM);
}

static int	check_window_size(void)
{
	if (WIN_WIDTH < 50 || WIN_WIDTH > 2000 || WIN_HEIGHT < 50
		|| WIN_HEIGHT > 2000)
	{
		ft_putstr_fd("Error\nWindow width/height should be"
			" between 50 and 2000\n", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_minirt	mrt;

	if (argc != 2 || argv[1] == NULL)
		return (write_error("Invalid number of arguments"));
	if (check_window_size() == 1)
		return (1);
	ft_bzero(&mrt, sizeof(t_minirt));
	if (read_rt_file(&mrt, argv[1]) == 1)
	{
		if (mrt.object)
			free(mrt.object);
		return (1);
	}
	if (check_number_of_elements(&mrt) == 1)
		return (1);
	initialise(&mrt, argv[1]);
	render(&mrt);
	print_controls();
	mlx_hook(mrt.win, 17, 0, end_event, &mrt);
	mlx_key_hook(mrt.win, key_input, &mrt);
	mlx_loop(mrt.mlx);
	return (0);
}
