/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:16:27 by arissane          #+#    #+#             */
/*   Updated: 2025/01/23 15:06:16 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	adjust_height(int keycode, t_object *object)
{
	float	temp;

	if (keycode == 110 && object->shape == CYLINDER)
	{
		object->height -= 0.5;
		if (object->height < 0.1)
			object->height = 0.1;
	}
	else if (keycode == 109 && object->shape == CYLINDER)
	{
		temp = object->height + 0.5;
		if (temp - 0.5 > object->height + EPSILON
			|| temp - 0.5 < object->height - EPSILON)
			object->height = FLOAT_MAX;
		else
			object->height = temp;
	}
	else
		return (1);
	return (0);
}

static int	object_resize(int keycode, t_object *object)
{
	float	temp;

	if (keycode == 44 && object->shape != PLANE)
	{
		object->radius -= 0.5;
		if (object->radius < 0.1)
			object->radius = 0.1;
	}
	else if (keycode == 46 && object->shape != PLANE)
	{
		temp = object->radius + 0.5;
		if (temp - 0.5 > object->radius + EPSILON
			|| temp - 0.5 < object->radius - EPSILON)
			object->radius = FLOAT_MAX;
		else
			object->radius = temp;
	}
	else if (adjust_height(keycode, object) == 0)
		return (0);
	else
		return (1);
	return (0);
}

/**
 * Checks which axis is used to rotate around based on the input,
 * calculates the angle into a quaternion representation, then applies
 * it to the current rotation value of the selected object and sets
 * the xyz orientation based on the xyzw rotation for the rendering
 */
static int	object_rotation(int keycode, t_object *object)
{
	t_vec3	rotation_axis;
	t_vec4	target_quaternion;

	rotation_axis.x = 0;
	rotation_axis.y = 0;
	rotation_axis.z = 0;
	if (keycode == 106)
		rotation_axis.x = 1.0f;
	else if (keycode == 107)
		rotation_axis.y = 1.0f;
	else if (keycode == 108)
		rotation_axis.z = 1.0f;
	else
		return (1);
	target_quaternion = angle_to_quaternion(&rotation_axis, 0.1f);
	object->rotation = vec4_multiply(&object->rotation,
			&target_quaternion);
	object->orientation = quaternion_to_vec3(&object->rotation);
	vec3_normalise(&object->orientation);
	return (0);
}

int	object_controls(int keycode, t_minirt *mrt, int object_id)
{
	if (keycode == 65362)
		mrt->object[object_id].position.z += 0.5;
	else if (keycode == 65364)
		mrt->object[object_id].position.z -= 0.5;
	else if (keycode == 65507)
		mrt->object[object_id].position.y -= 0.5;
	else if (keycode == 32)
		mrt->object[object_id].position.y += 0.5;
	else if (keycode == 65361)
		mrt->object[object_id].position.x -= 0.5;
	else if (keycode == 65363)
		mrt->object[object_id].position.x += 0.5;
	else if (object_rotation(keycode, &mrt->object[object_id]) == 0)
		return (0);
	else if (object_resize(keycode, &mrt->object[object_id]) == 0)
		return (0);
	else
		return (1);
	return (0);
}
