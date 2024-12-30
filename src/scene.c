/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:54:23 by arissane          #+#    #+#             */
/*   Updated: 2024/12/16 11:14:44 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//these values create a flat plane horizontally, like a floor
void	init_plane(t_object *object)
{
	object->type = PLANE;
	object->position.x = 0;
	object->position.y = 0;
	object->position.z = 0;
	object->normal.x = 0;
	object->normal.y = 1.0;
	object->normal.z = 0;
	object->col.red = 200;
	object->col.green = 0;
	object->col.blue = 200;
}

void	init_sphere(t_object *object)
{
	object->type = SPHERE;
	object->position.x = 1;
	object->position.y = 2;
	object->position.z = 6;
	object->radius = 8.0 / 2;
	object->col.red = 0;
	object->col.green = 240;
	object->col.blue = 255;
}

void	init_objects(t_minirt *mrt)
{
	mrt->number_of_objects = 2;
	mrt->object = ft_calloc(mrt->number_of_objects, sizeof(t_object));
	init_sphere(&mrt->object[0]);
	init_plane(&mrt->object[1]);
}

void	init_camera(t_minirt *mrt)
{
	mrt->camera.position.x = 0.0;
	mrt->camera.position.y = 0.0;
	mrt->camera.position.z = -5.0;
	mrt->camera.orientation.x = 0;
	mrt->camera.orientation.y = 0;
	mrt->camera.orientation.z = 1.0;
	mrt->camera.fov = 90;
}

void	create_scene(t_minirt *mrt)
{
	init_camera(mrt);
	init_objects(mrt);
}
