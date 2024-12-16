/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:38:55 by jingwu            #+#    #+#             */
/*   Updated: 2024/12/16 09:50:06 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "learning.h"

/*
	@function
	Generate a new type based on the x, y ,z and type values that are passing
	through the parameters.

	@return
	return a t_tuple type data.
*/
t_tuple	generate_tuple(float x, float y, float z, float type)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.type = type;
	return (tuple);
}
/*
	@function
	Generate a new point based on the x, y ,z values that are passing
	through the parameters.

	@return
	return a t_tuple type data.
*/
t_tuple	generate_point(float x, float y, float z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.type = 1.0;
	return (tuple);
}
/*
	@function
	Generate a new vector based on the x, y ,z values that are passing
	through the parameters.

	@return
	return a t_tuple type data.
*/
t_tuple	generate_vector(float x, float y, float z)
{
	t_tuple	tuple;

	tuple.x = x;
	tuple.y = y;
	tuple.z = z;
	tuple.type = 0.0;
	return (tuple);
}

