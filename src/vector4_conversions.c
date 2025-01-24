/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_conversions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:28:36 by arissane          #+#    #+#             */
/*   Updated: 2025/01/16 10:30:07 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	quaternion_to_vec3(t_vec4 *q)
{
	t_vec3	v;

	v.x = q->x;
	v.y = q->y;
	v.z = q->z;
	return (v);
}

t_vec4	vec3_to_quaternion(t_vec3 *v)
{
	t_vec4	q;
	float	length;

	q.x = v->x;
	q.y = v->y;
	q.z = v->z;
	length = (v->x * v->x + v->y * v->y + v->z * v->z);
	if (length > 1.0f)
		length = 1.0f;
	q.w = sqrtf(1.0f - length);
	return (q);
}

t_vec4	angle_to_quaternion(t_vec3 *axis, float angle)
{
	t_vec4	result;
	float	sin_half_angle;

	sin_half_angle = sinf(angle * 0.5);
	result.x = axis->x * sin_half_angle;
	result.y = axis->y * sin_half_angle;
	result.z = axis->z * sin_half_angle;
	result.w = cosf(angle);
	vec4_normalise(&result);
	return (result);
}
