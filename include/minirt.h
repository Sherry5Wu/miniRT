/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:55:13 by arissane          #+#    #+#             */
/*   Updated: 2025/02/03 14:50:47 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <stdbool.h>
# include <errno.h>
# include <stdio.h>

# ifndef WIN_WIDTH
#  define WIN_WIDTH 300
# endif
# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 300
# endif
# define FLOAT_MAX 340282346638528859811704183484516925440.0
# define DEGREE_TO_RADIAN 0.008726646259971647737
# define EPSILON 1e-6
# define M_PI 3.14159265358979323846

/***  define colour***/
# define GR "\033[0;32m"
# define BL "\033[1;94m"
# define RS "\033[0m"

typedef struct s_colour
{
	int	red;
	int	green;
	int	blue;
}		t_colour;

typedef struct s_vec4
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
typedef enum s_object_shape
{
	PLANE = 1,
	SPHERE = 2,
	CYLINDER = 3,
}			t_shape;

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
 * 	cy_hit_normal: the normal vector for the intersection point;(calculate it
 * 	in ray_intersection_plane/sphere/cylinder functions)
 * 	camera_inside: save the information of the camera is inside of a
 * 	cylinder or a sphere, but for plane, it means it is on the bottom side of
 * 	the plane(against the plane normal vector)
 * 	light_inside: save the information of the camera is inside of a
 * 	cylinder or a sphere, but for plane, it means it is on the bottom side of
 * 	the plane(against the plane normal vector)
 */
typedef struct s_object
{
	t_shape		shape;
	int			id;
	t_vec3		position;
	t_vec3		orientation;
	t_vec4		rotation;
	t_colour	colour;
	float		radius;
	float		height;
	bool		camera_inside;
	bool		light_inside;
	t_vec3		cy_hit_normal;
}	t_object;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		direction;
	t_vec3		right;
	t_vec3		up;
	float		aspect_ratio;
	int			fov;
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
	bool		light_on_surface;
	t_colour	base_colour;
	t_colour	ambient_added;
	t_ray		ambient;
	t_camera	camera;
	t_ray		light;
	t_object	*object;
}		t_minirt;

/**** tools ****/
void		free_window(t_minirt *mrt);
int			end_event(t_minirt *mrt);
t_vec4		angle_to_quaternion(t_vec3 *axis, float angle);
void		free_array(char **array);
void		fatal_error(char *message, int error);

/**** handle input ****/
int			key_input(int keycode, t_minirt *mrt);
int			object_controls(int keycode, t_minirt *mrt, int object_id);
int			camera_controls(int keycode, t_camera *camera);
int			light_controls(int keycode, t_ray *light);
int			adjust_ambient_brightness(int keycode, t_ray *ambient);
void		build_rotation_matrix(char axis, float angle, float matrix[3][3]);

/**** read rt file ****/
int			read_rt_file(t_minirt *mrt, char *file);
int			check_cylinder_data(t_minirt *mrt, char **values);
int			check_plane_data(t_minirt *mrt, char **values);
int			check_sphere_data(t_minirt *mrt, char **values);
int			check_light_data(t_minirt *mrt, char **values);
int			check_camera_data(t_minirt *mrt, char **values);
int			check_ambient_data(t_minirt *mrt, char **values);
int			check_number_of_variables(char **values, int min, int max);
int			add_colour_values(t_colour *colour, char *str, char *target);
int			add_xyz_values(t_vec3 *xyz, char *str, char *target, int type);
int			check_if_normalised(t_vec3 orientation, char *object);
int			write_error(char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			validate_number_array(char **array, int type);
int			validate_decimal_string(char *str);
int			validate_number_string(char *str);
float		ft_atofloat(char *str);
int			read_close_return(int fd);
int			allocate_new_object(t_minirt *mrt);

/**** vector_math ****/
void		vec3_normalise(t_vec3 *vector);
t_vec3		vec3_add(t_vec3 a, t_vec3 b);
t_vec3		vec3_subtract(t_vec3 a, t_vec3 b);
t_vec3		vec3_crossproduct(t_vec3 a, t_vec3 b);
float		vec3_dot(t_vec3 a, t_vec3 b);
t_vec3		vec3_scale(t_vec3 a, float scale);
t_vec3		vec3_project(t_vec3 a, t_vec3 b);
float		vec3_length(t_vec3 v);
float		vec3_cosine(t_vec3 a, t_vec3 b);
bool		vec3_compare(t_vec3 a, t_vec3 b);

/**** vector4_math ****/
float		vec4_dot(t_vec4	*a, t_vec4 *b);
t_vec3		quaternion_to_vec3(t_vec4 *q);
t_vec4		vec3_to_quaternion(t_vec3 *v);
void		vec4_normalise(t_vec4 *q);
t_vec4		vec4_multiply(t_vec4 *q1, t_vec4 *q2);

/**** calculate intersections ****/
float		ray_intersects_sphere(t_camera *camera_ray, t_object *sphere);
float		ray_intersects_plane(t_camera *ray, t_object *plane);
float		ray_intersects_cylinder(t_camera *ray, t_object *cylinder);
float		intersects_cylinder_side(t_camera *ray, t_object *cylinder);

/**** render ****/
void		render(t_minirt *mrt);
t_vec3		get_hit_normal(t_object *ob, t_vec3 hit_point);
t_camera	create_camera_ray(t_camera *camera, t_vec2 *pixel);
void		add_ambient(t_minirt *mrt);
void		modulate_colour(t_minirt *mrt, t_colour *final,
				float light_intensity);
float		diffusion(t_minirt *mrt, t_camera *camera_ray, t_object *object,
				float t);
int			calculate_colour(t_minirt *mrt, t_vec2 *pixel);
bool		is_intersected(t_camera *ray, t_object *ob, float *t);
bool		is_obscured_from_hitpoint_to_light(t_object *ob, t_minirt *mrt,
				t_camera *c_ray, float t);
void		set_camera_light_position_info_for_objects(t_minirt *mrt);

#endif
