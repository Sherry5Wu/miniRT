/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:32:19 by arissane          #+#    #+#             */
/*   Updated: 2024/12/16 11:37:37 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	key_input(int keycode, t_minirt *mrt)
{
	if (keycode == 65307)
		free_window(mrt);
	else
		return (-1);
	return (0);
}
