/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 10:51:45 by arissane          #+#    #+#             */
/*   Updated: 2024/12/20 14:42:08 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//Normalises the vector. Scales the magnitude(length) of the vector to a maximum of 1. This represents the direction of the vector
void	vec3_normalise(t_vec3 *vector)
{
	float	length;

	length = sqrtf((vector->x * vector->x) + (vector->y * vector->y)
			+ (vector->z * vector->z));
	vector->x = vector->x / length;
	vector->y = vector->y / length;
	vector->z = vector->z / length;
}

//Can be used to calculate movement from one point to another or as a part of larger calculations
t_vec3	vec3_add(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x + b->x;
	result.y = a->y + b->y;
	result.z = a->z + b->z;
	return (result);
}

//Check how far b is from a. If the result is smaller than the object radius, they are touching.Also gets the direction and magnitude of a vector pointing from b to a. And can be used for light direction and normal vector calculations
t_vec3	vec3_subtract(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->x - b->x;
	result.y = a->y - b->y;
	result.z = a->z - b->z;
	return (result);
}

//Calculate the cross product of two vectors. Creates a proportional perpendicular vector
t_vec3	vec3_crossproduct(t_vec3 *a, t_vec3 *b)
{
	t_vec3	result;

	result.x = a->y * b->z - a->z * b->y;
	result.y = a->z * b->x - a->x * b->z;
	result.z = a->x * b->y - a->y * b->x;
	return (result);
}

t_vec3	vec3_multiply(t_vec3 *a, float value)
{
	t_vec3	result;

	result.x = value * a->x;
	result.y = value * a->y;
	result.z = value * a->z;
	return (result);
}

//If the result is positive, the vectors point roughly in the same direction, if negative, they point in opposite directions. If the number is as large as possible (a * b), the vectors point in the same direction
float	vec3_dot(t_vec3 *a, t_vec3 *b)
{
	float	result;

	result = a->x * b->x + a->y * b->y + a->z * b->z;
	return (result);
}

//Can be used to scale a vector up or down to inrease or decrese it's magnitude
t_vec3	vec3_scale(t_vec3 *vector, float scale)
{
	t_vec3	result;

	result.x = vector->x * scale;
	result.y = vector->y * scale;
	result.z = vector->z * scale;
	return (result);
}
