/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_tuple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 09:48:48 by jingwu            #+#    #+#             */
/*   Updated: 2024/12/16 14:56:59 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "learning.h"

/*
	@function
	To check if the passed two float numbers are equal or not.

	@return
	true: equal;
	false: are not equal;
*/
bool	is_equal_float(float x, float y)
{
	if (abs(x - y) < EPSILON)
		return (true);
	else
		return (false);
}

/*
	@function
	To check if the two points are the same points.
*/
bool	is_same_point(t_tuple a, t_tuple b)
{
	// need to consider this condistion more when using.
	if (is_equal_float(a.type, 0.0) == true
			|| is_equal_float(b.type, 0.0) == true)
	{
		printf("the passed coordinate is not a point\n");
		return (false);
	}
	if (is_equal_float(a.x, b.x) == false || is_equal_float(a.y, b.y) == false
			|| is_equal_float(a.z, b.z) == false)
			return (false);
	return (true);
}
/*
	@function
	Adding two tuples(vector + point, vector + vector. btw, adding point +
	point doesn't make sense.)
	vector + point  --> point
	vector + vector --> vector

	@return
	Return a new tuple representing a new point/vector.
*/
t_tuple	adding_tuples(t_tuple a, t_tuple b)
{
	t_tuple c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	c.type = a.type + b.type;
	return (c);
}

/*
	@function
	Adding two tuples(point - vector, pointer- pointer, vector - vector.
	btw, substracing vetcor - pointer doesn't make sense)
	pointer - vector  --> point
	pointer - pointer --> vector
	vector - vector  --> vector

	@return
	Return a new tuple representing a new point/vector.
*/
t_tuple	substracing_tuple(t_tuple a, t_tuple b)
{
	t_tuple c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	c.type = a.type - b.type;
	return (c);
}

t_tuple	multiplying_tuple(t_tuple a, float scalar)
{
	t_tuple c;

	c.x = a.x * scalar;
	c.y = a.y * scalar;
	c.z = a.z * scalar;
	c.type = a.type * scalar; // kinda for the debugging;
	return (c);
}

t_tuple	dividing_tuple(t_tuple a, float scalar)
{
	t_tuple c;

	c.x = a.x / scalar;
	c.y = a.y / scalar;
	c.z = a.z / scalar;
	c.type = a.type / scalar; // kinda for the debugging;
	return (c);
}

/*
	@function
	Normalizate a vector. Frist caculating the magnitude/lenth of a vector.
	Then each axis (tuple components) divides by its magnitude.
*/
void	normalizing_tuple(t_tuple a)
{
	float	magnitude;

	magnitude = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
	a.x = a.x/ magnitude;
	a.y = a.y / magnitude;
	a.z = a.z / magnitude;
	a.type = a.type / magnitude; // kinda for the debugging
}

/*
	@function
	Ccaculating the dot product of two vectors.
*/
float	dot_tuple(t_tuple a, t_tuple b)
{
	 return (a.x * b.x + a.y * a.y + a.z * a.z + a.type *a.type);
}

t_tuple	cross(t_tuple a, t_tuple b)
{
	t_tuple c;

	c.x = a.y * b.z - a.z * b.y;
	c.y = a.z * b.x - a.x * b.z;
	c.z = a.x * b.y - a.y * b.x;
}
