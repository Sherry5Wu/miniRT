/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 10:34:10 by arissane          #+#    #+#             */
/*   Updated: 2025/01/22 10:03:27 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Can be used to scale a vector up or down to inrease or decrese it's magnitude
 */
t_vec3	vec3_scale(t_vec3 vector, float scale)
{
	t_vec3	result;

	result.x = vector.x * scale;
	result.y = vector.y * scale;
	result.z = vector.z * scale;
	return (result);
}

/**
 * @function
 * Compute the project of vector a on vector b. Using when caculating the
 * ray intersection of cylinder.
*/
t_vec3	vec3_project(t_vec3 a, t_vec3 b)
{
	return (vec3_scale(b, vec3_dot(a, b) / vec3_dot(b, b)));
}

/**
 * @function
 * To calculate the lenght of a vector, also can be called as magnitude.
*/
float	vec3_length(t_vec3 v)
{
	return (sqrtf(v.x * v.x + v.y * v.y + v.z * v.z));
}

/**
 *  @brief
 *  To calculate the cosine fo the angle between two vectors
 */
float	vec3_cosine(t_vec3 a, t_vec3 b)
{
	return (vec3_dot(a, b) / vec3_length(a) * vec3_length(b));
}

/**
 *  @brief
 *  To compare whether two vectors are indentical.
 */
bool	vec3_compare(t_vec3 a, t_vec3 b)
{
	return (fabsf(a.x - b.x) < EPSILON && fabsf(a.y - b.y) < EPSILON
		&& fabsf(a.z - b.z) < EPSILON);
}
