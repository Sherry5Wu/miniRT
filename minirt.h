/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arissane <arissane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:55:13 by arissane          #+#    #+#             */
/*   Updated: 2024/12/12 15:01:37 by arissane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <math.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 800

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

typedef struct s_object
{
	int			type;
	t_vec3		position;
	t_vec3		normal;
	t_colour	col;
	float		radius;
}		t_object;

typedef struct s_ray
{
	t_vec3		position;
	t_vec3		orientation;
	float		fov;
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
	t_object	*object;
	t_ray		camera;
}		t_minirt;

void	create_scene(t_minirt *mrt);
void	free_window(t_minirt *mrt);
int		end_event(t_minirt *mrt);
void	render(t_minirt *mrt);

/**** vector_math ****/
void	vec3_normalise(t_vec3 *vector);
t_vec3	vec3_add(t_vec3 *a, t_vec3 *b);
t_vec3	vec3_substract(t_vec3 *a, t_vec3 *b);
float	vec3_dot(t_vec3 *a, t_vec3 *b);
void	vec3_scale(t_vec3 *a, float scale);

#endif
