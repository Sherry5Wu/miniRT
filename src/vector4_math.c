/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:30:31 by arissane          #+#    #+#             */
/*   Updated: 2025/01/16 10:30:50 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec4_dot(t_vec4	*a, t_vec4 *b)
{
	float	result;

	result = a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
	return (result);
}

void	vec4_normalise(t_vec4 *q)
{
	float	length;

	length = sqrtf(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
	if (length > 0.0f)
	{
		q->x /= length;
		q->y /= length;
		q->z /= length;
		q->w /= length;
	}
}

t_vec4	vec4_multiply(t_vec4 *q1, t_vec4 *q2)
{
	t_vec4	result;

	result.w = q1->w * q2->w - q1->x * q2->x - q1->y * q2->y - q1->z * q2->z;
	result.x = q1->w * q2->x + q1->x * q2->w + q1->y * q2->z - q1->z * q2->y;
	result.y = q1->w * q2->y - q1->x * q2->z + q1->y * q2->w + q1->z * q2->x;
	result.z = q1->w * q2->z + q1->x * q2->y - q1->y * q2->x + q1->z * q2->w;
	vec4_normalise(&result);
	return (result);
}
