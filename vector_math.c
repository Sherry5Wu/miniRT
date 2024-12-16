/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:51:45 by arissane          #+#    #+#             */
/*   Updated: 2024/12/12 15:18:41 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vec3_normalise(t_vec3 *vector)
{
	float	length;

	length = sqrtf((vector->x * vector->x) + (vector->y * vector->y)
			+ (vector->z * vector->z));
	vector->x = vector->x / length;
	vector->y = vector->y / length;
	vector->z = vector->z / length;
}

t_vec3	vec3_add(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

t_vec3	vec3_substract(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

float	vec3_dot(t_vec3 *a, t_vec3 *b)
{
	float	result;

	result = a->x * b->x + a->y * b->y + a->z * b->z;
	return (result);
}

void	vec3_scale(t_vec3 *vector, float scale)
{
	vector->x = vector->x * scale;
	vector->y = vector->y * scale;
	vector->z = vector->z * scale;
}
