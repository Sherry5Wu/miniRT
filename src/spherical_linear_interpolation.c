/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spherical_linear_interpolation.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:35:24 by arissane          #+#    #+#             */
/*   Updated: 2025/01/09 11:03:59 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec4	linear_interpolation(t_vec4 *q1, t_vec4 *q2, float t)
{
	t_vec4	result;

	result.x = q1->x + t * (q2->x - q1->x);
	result.y = q1->y + t * (q2->y - q1->y);
	result.z = q1->z + t * (q2->z - q1->z);
	result.w = q1->w + t * (q2->w - q1->w);
	vec4_normalise(&result);
	return (result);
}

#include <stdio.h>
t_vec4	spherical_linear_interpolation(t_vec4 *q1, t_vec4 *q2, float t)
{
	t_vec4	result;
	t_vec4	q2_temp;
	float	dot;
	float	theta;

	dot = vec4_dot(q1, q2);
	//if the quaternions are too close, do linear interpolation
	if (dot > 0.9998f)
		return (linear_interpolation(q1, q2, t));
	//if negative, flip one quaternion to ensure the shortest path
	if (dot < 0.0f)
	{
		q2->x = -q2->x;
		q2->y = -q2->y;
		q2->z = -q2->z;
		q2->w = -q2->w;
		dot = -dot;
	}
	if (dot > 1.0f)
		dot = 1.0f;
	if (dot < -1.0f)
		dot = -1.0f;
	theta = (acosf(dot)) * t;
	q2_temp.x = q2->x - q1->x * dot;
	q2_temp.y = q2->y - q1->y * dot;
	q2_temp.z = q2->z - q1->z * dot;
	q2_temp.w = q2->w - q1->w * dot;
	vec4_normalise(&q2_temp);
	result.x = q1->x * cosf(theta) + q2_temp.x * sinf(theta);
	result.y = q1->y * cosf(theta) + q2_temp.y * sinf(theta);
	result.z = q1->z * cosf(theta) + q2_temp.z * sinf(theta);
	result.w = q1->w * cosf(theta) + q2_temp.w * sinf(theta);
	vec4_normalise(&result);
	printf("result x = %f y = %f z = %f w = %f\n", result.x, result.y, result.z, result.w);
	return (result);
}
