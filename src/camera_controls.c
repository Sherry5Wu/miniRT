/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 09:15:37 by arissane          #+#    #+#             */
/*   Updated: 2025/01/27 10:55:00 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec3	rotate_vector(t_vec3 v, float matrix[3][3])
{
	t_vec3	result;

	result.x = v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2];
	result.y = v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2];
	result.z = v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2];
	return (result);
}

static void	update_forward_up_right_vectors(t_camera *camera,
	float rotate_matrix[3][3])
{
	camera->direction = rotate_vector(camera->direction, rotate_matrix);
	vec3_normalise(&camera->direction);
	camera->up = rotate_vector(camera->up, rotate_matrix);
	vec3_normalise(&camera->up);
	camera->right = vec3_crossproduct(camera->direction, camera->up);
	vec3_normalise(&camera->right);
}

int	camera_rotation(int keycode, t_camera *camera)
{
	float	rotation_matrix[3][3];

	if (keycode == 101)
		build_rotation_matrix('Y', 5.0f, rotation_matrix);
	else if (keycode == 113)
		build_rotation_matrix('Y', -5.0f, rotation_matrix);
	else if (keycode == 120)
		build_rotation_matrix('X', 5.0f, rotation_matrix);
	else if (keycode == 122)
		build_rotation_matrix('X', -5.0f, rotation_matrix);
	else if (keycode == 118)
		build_rotation_matrix('Z', 5.0f, rotation_matrix);
	else if (keycode == 99)
		build_rotation_matrix('Z', -5.0f, rotation_matrix);
	else
		return (1);
	update_forward_up_right_vectors(camera, rotation_matrix);
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
	else if (camera_rotation(keycode, camera) == 0)
		return (0);
	else
		return (1);
	return (0);
}
