/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rt_object_allocate_memory.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:38:55 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/23 09:01:03 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	reallocate_object_array(t_minirt *mrt)
{
	int			i;
	t_object	*new_array;

	i = 0;
	new_array = ft_calloc(mrt->object_count + 1, sizeof(t_object));
	if (!new_array)
	{
		free(mrt->object);
		return (write_error("allocation failure"));
	}
	while (i < mrt->object_count)
	{
		new_array[i] = mrt->object[i];
		i++;
	}
	free(mrt->object);
	mrt->object = new_array;
	return (0);
}

int	allocate_new_object(t_minirt *mrt)
{
	if (mrt->object_count == 0)
	{
		mrt->object = ft_calloc(1, sizeof(t_object));
		if (!mrt->object)
			return (write_error("allocation failure"));
	}
	else
	{
		if (reallocate_object_array(mrt))
			return (1);
	}
	return (0);
}
