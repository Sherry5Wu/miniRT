/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:55:13 by arissane          #+#    #+#             */
/*   Updated: 2024/12/30 12:37:37 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>

# define FLOAT_MAX 340282346638528859811704183484516925440.0
# define DEGREE_TO_RADIAN 0.008726646259971647737
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200

# define PLANE 1
# define SPHERE 2
# define CYLINDER 3

typedef struct s_colour
{
	int	red;
	int	green;
	int	blue;
}		t_colour;

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
	PLANE = 0,
	SPHERE,
	CYLINDER
}				t_shape;

/*
	parameters for all kinds shapes:
	position: the coordinates of the center point of the plane shape
	orientation (normal): the normal vector. should be int the range[-1,1] for each axis.
	color: represent in RGB[0,255]
	radius: used in shpere and cylinder shape, 1/2 of diameter.
	height: used in cylinder shape.
*/
typedef struct s_object
{
	//int			type;
	t_shape		shape; // change the type into a structure type , it will be easy for us to add more shape in the future if we want.
	t_vec3		position;
	t_vec3		orientation;// should we change to normal? why name it as orientation?
	t_colour	colour;
	float		radius;
	float		height;
}	t_object;


typedef struct s_camera
{
	t_vec3		position;
	t_vec3		direction;
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

/**** vector_math ****/
void	vec3_normalise(t_vec3 *vector);
t_vec3	vec3_add(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_subtract(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_crossproduct(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_multiply(t_vec3 *a, float value);
float	vec3_dot(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_scale(t_vec3 *a, float scale);

#endif
