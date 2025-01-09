/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:32:19 by arissane          #+#    #+#             */
/*   Updated: 2025/01/09 13:21:45 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_rotation(int keycode, t_camera *camera)
{
	t_vec3	rotation_axis;
	t_vec4	target_quaternion;

	rotation_axis.x = 0;
	rotation_axis.y = 0;
	rotation_axis.z = 0;
	if (keycode == 101)
		rotation_axis.y = -1.0f;
	else if (keycode == 113)
		rotation_axis.y = 1.0f;
	else if (keycode == 122)
		rotation_axis.x = 1.0f;
	else if (keycode == 120)
		rotation_axis.x = -1.0f;
	else
		return (1);
	target_quaternion = angle_to_quaternion(&rotation_axis, 0.1f);
	camera->rotation = vec4_multiply(&camera->rotation, &target_quaternion);
	camera->direction = quaternion_to_vec3(&camera->rotation);
	return (0);
}

int	camera_controls(int keycode, t_camera *camera)
{
	if (keycode == 97)
		camera->position.x -= 0.5;
	else if (keycode == 100)
		camera->position.x += 0.5;
	else if (keycode == 114)
		camera->position.y += 0.5;
	else if (keycode == 102)
		camera->position.y -= 0.5;
	else if (keycode == 119)
		camera->position.z += 0.5;
	else if (keycode == 115)
		camera->position.z -= 0.5;
	else if (keycode == 101 || keycode == 113 || keycode == 122 || keycode == 120)
		return (camera_rotation(keycode, camera));
	else
		return (1);
	return (0);
}

//Checks which axis is used to rotate around based on the input, calculates the angle into a quaternion representation, then applies it to the current rotation value of the selected object and sets the xyz orientation based on the xyzw rotation for the rendering
int	object_rotation(int keycode, t_object *object)
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
	//object->rotation = spherical_linear_interpolation(&object->rotation, &target_quaternion, 0.1f);//Can make the rotation smoother, but doesn't seem necessary
	object->rotation = vec4_multiply(&object->rotation, &target_quaternion);
	object->orientation = quaternion_to_vec3(&object->rotation);
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
	else if (keycode == 106 || keycode == 107 || keycode == 108)
		return (object_rotation(keycode, &mrt->object[object_id]));
	else
		return (camera_controls(keycode, &mrt->camera));
	return (0);
}

int	key_input(int keycode, t_minirt *mrt)
{
	static int	object_id;

	if (!object_id)
		object_id = 0;
	if (keycode == 65307)
		free_window(mrt);
	else if (keycode == 61)
	{
		object_id++;
		if (object_id >= mrt->object_count)
			object_id = 0;
		ft_printf("object id = %d\n", object_id);
	}
	else if (keycode == 45)
	{
		object_id--;
		if (object_id < 0)
			object_id = mrt->object_count - 1;
		ft_printf("object id = %d\n", object_id);
	}
	else if (object_controls(keycode, mrt, object_id) == 0)
	{
		if (mrt->img)
		{
			mlx_destroy_image(mrt->mlx, mrt->img);
			mrt->img = mlx_new_image(mrt->mlx, WIN_WIDTH, WIN_HEIGHT);
		}
		render(mrt);
	}
	else
	{
		if (keycode != 65293)
			ft_printf("Entered key == %d\n", keycode);
		return (-1);
	}
	return (0);
}
