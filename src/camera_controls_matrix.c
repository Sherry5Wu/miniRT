/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_controls_matrix.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 11:30:56 by jingwu            #+#    #+#             */
/*   Updated: 2025/01/27 10:53:53 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	matrix_for_x(float matrix[3][3], float cosa, float sina)
{
	matrix[0][0] = 1;
	matrix[0][1] = 0;
	matrix[0][2] = 0;
	matrix[1][0] = 0;
	matrix[1][1] = cosa;
	matrix[1][2] = -sina;
	matrix[2][0] = 0;
	matrix[2][1] = sina;
	matrix[2][2] = cosa;
}

static void	matrix_for_y(float matrix[3][3], float cosa, float sina)
{
	matrix[0][0] = cosa;
	matrix[0][1] = 0;
	matrix[0][2] = sina;
	matrix[1][0] = 0;
	matrix[1][1] = 1;
	matrix[1][2] = 0;
	matrix[2][0] = -sina;
	matrix[2][1] = 0;
	matrix[2][2] = cosa;
}

static void	matrix_for_z(float matrix[3][3], float cosa, float sina)
{
	matrix[0][0] = cosa;
	matrix[0][1] = -sina;
	matrix[0][2] = 0;
	matrix[1][0] = sina;
	matrix[1][1] = cosa;
	matrix[1][2] = 0;
	matrix[2][0] = 0;
	matrix[2][1] = 0;
	matrix[2][2] = 1;
}

void	build_rotation_matrix(char axis, float angle, float matrix[3][3])
{
	float	rad;
	float	cosa;
	float	sina;

	rad = angle * M_PI / 180.0;
	cosa = cos(rad);
	sina = sin(rad);
	if (axis == 'X')
		matrix_for_x(matrix, cosa, sina);
	else if (axis == 'Y')
		matrix_for_y(matrix, cosa, sina);
	else if (axis == 'Z')
		matrix_for_z(matrix, cosa, sina);
}
