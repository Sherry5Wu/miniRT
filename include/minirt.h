/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:55:13 by arissane          #+#    #+#             */
/*   Updated: 2025/01/09 13:49:11 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <stdio.h> // for testing only

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
#include <stdbool.h>

# define FLOAT_MAX 340282346638528859811704183484516925440.0
# define DEGREE_TO_RADIAN 0.008726646259971647737
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200
# define DIFFER	(1e-6)

// # define PLANE 1
// # define SPHERE 2
// # define CYLINDER 3

typedef struct s_colour
{
	int	red;
	int	green;
	int	blue;
}		t_colour;

typedef struct	s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}		t_vec3;

typedef struct s_vec2
{
	float	x;
	float	y;
}		t_vec2;

/*
	The supported shapes
*/
typedef enum	s_object_shape
{
	PLANE = 1,
	SPHERE = 2,
	CYLINDER = 3,
}				t_shape;

/*
	Use when caculating the intersections for sphere and cylinder,
	to save the some temporary values.
*/
typedef struct s_equation
{
	float	a;
	float	b;
	float	c;
	float	discriminant;
	float	t1;
	float	t2;
}			t_equation;

/**
 * 	@brief
 * 	parameters for all kinds shapes.
 *
 * 	position: the coordinates of the center point of the plane shape
 * 	orientation (normal): the normalized vector, as unit vector.
 * 	rotation: quaternion used to calculate accurate object rotation.
 * 	color: represent in RGB[0,255]
 * 	radius: used in shpere and cylinder shape.
 * 	height: used in cylinder shape.
 * 	cap_t: the top center of a cylinder.
 * 	cap_b: the bottom center of a cyliner.
 * 	cy_hp: The projection position of the intersection point on the cylinder axis.
 */
typedef struct s_object
{
	t_shape		shape;
	t_vec3		position;
	t_vec3		orientation;
	t_vec4		rotation;
	t_colour	colour;
	float		radius;
	float		height;
	t_vec3		cap_t;
	t_vec3		cap_b;
	t_vec3		cy_hp;
}	t_object;


typedef struct s_camera
{
	t_vec3		position;
	t_vec3		direction;
	t_vec4		rotation;
	t_vec3		right;
	t_vec3		up;
	float		aspect_ratio;
	int		fov;
}		t_camera;

typedef struct s_ray
{
	t_vec3		position;
	t_vec3		direction;
	t_colour	colour;
	float		brightness;
}		t_ray;

typedef struct s_minirt
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			number_of_objects;
	int			ambient_count;
	int			light_count;
	int			camera_count;
	int			object_count;
	t_ray		ambient;
	t_camera	camera;
	t_ray		light;
	t_object	*object;
}		t_minirt;

int		read_rt_file(t_minirt *mrt, char *file);
void	free_window(t_minirt *mrt);
int		end_event(t_minirt *mrt);
int		key_input(int keycode, t_minirt *mrt);
t_camera	create_camera_ray(t_camera *camera, t_vec2 *pixel);
void	render(t_minirt *mrt);
void	add_ambient_light(t_colour *colour, float light_intensity);
float	ray_intersects_sphere(t_camera *camera_ray, t_object *sphere);
float	ray_intersects_plane(t_camera *ray, t_object *plane);
float	ray_intersects_cylinder(t_camera *ray, t_object *cylinder);
void	light_diffusion(t_minirt *mrt, t_camera *camera_ray, t_object *object, t_colour *colour, float t);
t_vec4	spherical_linear_interpolation(t_vec4 *q1, t_vec4 *q2, float t);
t_vec4	angle_to_quaternion(t_vec3 *axis, float angle);

/**** vector_math ****/
void	vec3_normalise(t_vec3 *vector);
t_vec3	vec3_add(t_vec3 a, t_vec3 b);
t_vec3	vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3	vec3_crossproduct(t_vec3 a, t_vec3 b);
float	vec3_dot(t_vec3 a, t_vec3 b);
t_vec3	vec3_scale(t_vec3 a, float scale);
t_vec3	vec3_project(t_vec3 a, t_vec3 b);
float	vec3_length(t_vec3 v);

/**** vector4_math ****/
float	vec4_dot(t_vec4	*a, t_vec4 *b);
t_vec3	quaternion_to_vec3(t_vec4 *q);
t_vec4	vec3_to_quaternion(t_vec3 *v);
void	vec4_normalise(t_vec4 *q);
t_vec4	vec4_multiply(t_vec4 *q1, t_vec4 *q2);

#endif
