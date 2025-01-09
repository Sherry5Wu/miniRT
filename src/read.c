/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jingwu <jingwu@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:48:12 by arissane          #+#    #+#             */
/*   Updated: 2025/01/09 13:47:44 by jingwu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	write_error(char *str)
{
	ft_putstr_fd("Error!\n", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	validate_number_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	validate_decimal_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	if (str[i] == '-')
		i++;
	while (str[i] && str[i] != '.')
	{
		if (str[i] < '0' && str[i] > '9')
			return (1);
		i++;
	}
	if (str[i] && str[i] == '.')
	{
		i++;
		while (str[i])
		{
			if (str[i] < '0' || str[i] > '9')
				return (1);
			i++;
		}
	}
	return (0);
}

int	validate_number_array(char **array, t_shape type)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (type == PLANE)
		{
			if (validate_number_string(array[i]) == 1)
				return (1);
		}
		if (type == SPHERE)
		{
			if (validate_decimal_string(array[i]) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}

static float	get_fraction(char *str)
{
	int	i;
	double	fraction;
	double	divisor;

	i = 0;
	fraction = 0.0;
	divisor = 10.0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (fraction > FLOAT_MAX)
			return (-1.0);
		fraction = fraction + ((str[i] - 48) / divisor);
		divisor = 10.0 * divisor;
		i++;
	}
	return (fraction);
}

float	ft_atofloat(char *str)
{
	int	i;
	double	number;
	double	fraction;
	double	sign;

	i = 0;
	number = 0.0;
	sign = 1.0;
	if (str[0] == '-' || str[0] == '+')
	{
		if (str[0] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (number > FLOAT_MAX)
			return (FLOAT_MAX);
		number = number * 10.0 + (str[i] - 48);
		i++;
	}
	if (str[i] == '.')
	{
		fraction = get_fraction(&str[i + 1]);
		if (fraction == -1.0)
			return (FLOAT_MAX);
		number = number + fraction;
	}
	return ((float)(sign * number));
}

int	check_ambient_data(t_minirt *mrt, char **values)
{
	int	i;
	char	**colours;

	i = 0;
	mrt->ambient_count++;
	if (mrt->ambient_count > 1)
		return (write_error("Number of ambient lighting exceeds 1"));
	while (values[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of variables for ambient lighting"));
	if (validate_decimal_string(values[1]) == 1)
		return (write_error("Syntax error for ambient light ratio, should be in a range from 0.0 to 1.0"));
	mrt->ambient.brightness = ft_atofloat(values[1]);
	if (mrt->ambient.brightness > 1.0 || mrt->ambient.brightness < 0.0)
		return (write_error("Ambient light ratio should be in the range from 0.0 to 1.0"));
	colours = ft_split(values[2], ',');
	i = 0;
	while (colours[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of colours for ambient lighting"));
	if (validate_number_array(colours, 1) == 1)
		return (write_error("Syntax error; ambient light colours should be numbers in the range from 0 to 255"));
	mrt->ambient.colour.red = ft_atoi(colours[0]);
	mrt->ambient.colour.green = ft_atoi(colours[1]);
	mrt->ambient.colour.blue = ft_atoi(colours[2]);
	if (mrt->ambient.colour.red > 255 || mrt->ambient.colour.red < 0 || mrt->ambient.colour.green > 255 || mrt->ambient.colour.green < 0 || mrt->ambient.colour.blue > 255 || mrt->ambient.colour.blue < 0)
		return (write_error("The colour values for ambient lighting should be in the range from 0 to 255"));
	free_array(colours);
	return (0);
}

int	check_camera_data(t_minirt *mrt, char **values)
{
	int	i;
	char	**coordinates;
	char	**direction;

	i = 0;
	mrt->camera_count++;
	if (mrt->camera_count > 1)
		return (write_error("Number of cameras exceeds 1"));
	while (values[i])
		i++;
	if (i != 4)
		return (write_error("Invalid number of variables for the camera"));
	coordinates = ft_split(values[1], ',');
	i = 0;
	while (coordinates[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of coordinates for the camera"));
	if (validate_number_array(coordinates, 2) == 1)
		return (write_error("Syntax error; camera coordinates should be decimal numbers"));
	mrt->camera.position.x = ft_atofloat(coordinates[0]);
	mrt->camera.position.y = ft_atofloat(coordinates[1]);
	mrt->camera.position.z = ft_atofloat(coordinates[2]);
	free_array(coordinates);
	direction = ft_split(values[2], ',');
	i = 0;
	while (direction[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of orientation coordinates for the camera"));
	if (validate_number_array(direction, 2) == 1)
		return (write_error("Syntax error; camera coordinates should be decimal numbers"));
	mrt->camera.direction.x = ft_atofloat(direction[0]);
	mrt->camera.direction.y = ft_atofloat(direction[1]);
	mrt->camera.direction.z = ft_atofloat(direction[2]);
	if (mrt->camera.direction.x > 1.0 || mrt->camera.direction.x < -1.0 || mrt->camera.direction.y > 1.0 || mrt->camera.direction.y < -1.0 || mrt->camera.direction.z > 1.0 || mrt->camera.direction.z < -1.0)
		return (write_error("Camera orientation values should be within a range from -1.0 to 1.0"));
	free_array(direction);

	mrt->camera.rotation = vec3_to_quaternion(&mrt->camera.direction);

	mrt->camera.fov = ft_atoi(values[3]);
	if (mrt->camera.fov < 0 || mrt->camera.fov > 180)
		return (write_error("Camera FOV should be within the range of 0 to 180"));
	if (WIN_WIDTH < 1 || WIN_HEIGHT < 1)
		return (write_error("Window dimensions are too small"));
	mrt->camera.aspect_ratio = (float)WIN_WIDTH / (float)WIN_HEIGHT;

	//if the positive z axis is our default forward direction, the normal vector 0,0,1 is looking forward, 1,0,0 is right, 0,1,0 is up. If the starting orientation is the "forward" direction, the "right" vector can be calculated with the cross product of "forward" and "up" 0,1,0
	//the up vector is put as 0,1,-0.1 in order to avoid a zero vector from the cross product if the forward direction is also along the same direction
	t_vec3	up;

	up.x = 0;
	up.y = 1;
	up.z = -0.000001;

	mrt->camera.right = vec3_crossproduct(mrt->camera.direction, up);
	mrt->camera.up = vec3_crossproduct(mrt->camera.right, mrt->camera.direction);
	vec3_normalise(&mrt->camera.up);
	return (0);
}

int	check_light_data(t_minirt *mrt, char **values)
{
	int	i;
	char	**coordinates;
	char	**colours;

	i = 0;
	mrt->light_count++;
	if (mrt->light_count > 1)
		return (write_error("Number of lights exceeds 1"));
	while (values[i])
		i++;
	if (i < 3 || i > 4)
		return(write_error("Invalid number of variables for the light"));
	coordinates = ft_split(values[1], ',');
	i = 0;
	while (coordinates[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of coordinates for the light"));
	if (validate_number_array(coordinates, 2) == 1)
		return (write_error("Syntax error; light coordinates should be decimal numbers"));
	mrt->light.position.x = ft_atofloat(coordinates[0]);
	mrt->light.position.y = ft_atofloat(coordinates[1]);
	mrt->light.position.z = ft_atofloat(coordinates[2]);
	free_array(coordinates);
	if (validate_decimal_string(values[2]) == 1)
		return (write_error("Syntax error; the light brightness ratio should be a decimal number"));
	mrt->light.brightness = ft_atofloat(values[2]);
	if (values[3])
	{
		colours = ft_split(values[3], ',');
		i = 0;
		while (colours[i])
			i++;
		if (i != 3)
			return (write_error("Invalid number of colours for the light"));
		if (validate_number_array(colours, 1) == 1)
			return (write_error("Syntax error; the light colours should be numbers in the range from 0 to 255"));
		mrt->light.colour.red = ft_atoi(colours[0]);
		mrt->light.colour.green = ft_atoi(colours[1]);
		mrt->light.colour.blue = ft_atoi(colours[2]);
		if (mrt->light.colour.red > 255 || mrt->light.colour.red < 0 || mrt->light.colour.green > 255 || mrt->light.colour.green < 0 || mrt->light.colour.blue > 255 || mrt->light.colour.blue < 0)
			return (write_error("The colour values for the light should be in the range from 0 to 255"));
		free_array(colours);
	}
	return (0);
}

int	allocate_new_object(t_minirt *mrt)
{
	t_object	*new_array;
	int		i;

	i = 0;
	if (mrt->object_count == 1)
	{
		mrt->object = ft_calloc(2, sizeof(t_object));
		if (!mrt->object)
			return (write_error("allocation failure"));
	}
	else
	{
		new_array = ft_calloc(mrt->object_count, sizeof(t_object));
		if (!new_array)
			return (write_error("allocation failure"));
		while (i < mrt->object_count)
		{
			new_array[i] = mrt->object[i];
			i++;
		}
		free(mrt->object);
		mrt->object = new_array;
	}
	return (0);
}

int	check_sphere_data(t_minirt *mrt, char **values)
{
	int	i;
	char	**coordinates;
	char	**colours;
	t_object	sphere;

	i = 0;
	mrt->object_count++;
	if (allocate_new_object(mrt) == 1)
		return (1);
	while (values[i])
		i++;
	if (i != 4)
		return(write_error("Invalid number of variables for a sphere"));
	sphere.shape = SPHERE;
	coordinates = ft_split(values[1], ',');
	i = 0;
	while (coordinates[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of coordinates for a sphere"));
	if (validate_number_array(coordinates, 2) == 1)
		return (write_error("Syntax error; sphere coordinates should be decimal numbers"));
	sphere.position.x = ft_atofloat(coordinates[0]);
	sphere.position.y = ft_atofloat(coordinates[1]);
	sphere.position.z = ft_atofloat(coordinates[2]);
	free_array(coordinates);
	if (validate_decimal_string(values[2]) == 1)
		return (write_error("Syntax error; sphere diameter should be a decimal number"));
	sphere.radius = ft_atofloat(values[2]);
	if (sphere.radius != 0)
		sphere.radius = sphere.radius / 2;
	colours = ft_split(values[3], ',');
	i = 0;
	while (colours[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of colours for a sphere"));
	if (validate_number_array(colours, 1) == 1)
		return (write_error("Syntax error; sphere colours should be numbers in the range from 0 to 255"));
	sphere.colour.red = ft_atoi(colours[0]);
	sphere.colour.green = ft_atoi(colours[1]);
	sphere.colour.blue = ft_atoi(colours[2]);
	if (sphere.colour.red > 255 || sphere.colour.red < 0 || sphere.colour.green > 255 || sphere.colour.green < 0 || sphere.colour.blue > 255 || sphere.colour.blue < 0)
		return (write_error("The colour values for the light should be in the range from 0 to 255"));
	free_array(colours);
	mrt->object[mrt->object_count - 1] = sphere;
	return (0);
}

int	check_plane_data(t_minirt *mrt, char **values)
{
	int	i;
	char	**coordinates;
	char	**orientation;
	char	**colours;
	t_object	plane;

	i = 0;
	mrt->object_count++;
	if (allocate_new_object(mrt) == 1)
		return (1);
	while (values[i])
		i++;
	if (i != 4)
		return(write_error("Invalid number of variables for a plane"));
	plane.shape = PLANE;
	coordinates = ft_split(values[1], ',');
	i = 0;
	while (coordinates[i])
		i++;
	if (i != 3)
		return (write_error("Invalid number of coordinates for a plane"));
	if (validate_number_array(coordinates, 2) == 1)
		return (write_error("Syntax error; plane coordinates should be decimal numbers"));
	plane.position.x = ft_atofloat(coordinates[0]);
	plane.position.y = ft_atofloat(coordinates[1]);
	plane.position.z = ft_atofloat(coordinates[2]);
	free_array(coordinates);
	orientation = ft_split(values[2], ',');
	i = 0;
	while (orientation[i])
		i++;
	if (i != 3)
		return (write_error("Plane; invalid number of orientation coordinates"));
	if (validate_number_array(orientation, 2) == 1)
		return (write_error("Syntax error; plane orientation should be decimal numbers"));
	plane.orientation.x = ft_atofloat(orientation[0]);
	plane.orientation.y = ft_atofloat(orientation[1]);
	plane.orientation.z = ft_atofloat(orientation[2]);
	if (plane.orientation.x > 1.0 || plane.orientation.x < -1.0 || plane.orientation.y > 1.0 || plane.orientation.y < -1.0 || plane.orientation.z > 1.0 || plane.orientation.z < -1.0)
		return (write_error("Plane orientation values should be within a range from -1.0 to 1.0"));
	free_array(orientation);

	plane.rotation = vec3_to_quaternion(&plane.orientation);

	colours = ft_split(values[3], ',');
	i = 0;
	while (colours[i])
		i++;
	if (i != 3)
		return (write_error("Plane; invalid number of colours"));
	if (validate_number_array(colours, 1) == 1)
		return (write_error("Syntax error; plane colours should be numbers in the range from 0 to 255"));
	plane.colour.red = ft_atoi(colours[0]);
	plane.colour.green = ft_atoi(colours[1]);
	plane.colour.blue = ft_atoi(colours[2]);
	if (plane.colour.red > 255 || plane.colour.red < 0 || plane.colour.green > 255 || plane.colour.green < 0 || plane.colour.blue > 255 || plane.colour.blue < 0)
		return (write_error("Plane; the colour values should be in the range from 0 to 255"));
	free_array(colours);
	mrt->object[mrt->object_count - 1] = plane;
	return (0);
}

int	check_cylinder_data(t_minirt *mrt, char **values)
{
	int	i;
	char	**coordinates;
	char	**orientation;
	char	**colours;
	t_object	cylinder;

	i = 0;
	mrt->object_count++;
	if (allocate_new_object(mrt) == 1)
		return (1);
	while (values[i])
		i++;
	if (i != 6)
		return(write_error("Cylinder; invalid number of variables"));
	cylinder.shape = CYLINDER;
	coordinates = ft_split(values[1], ',');
	i = 0;
	while (coordinates[i])
		i++;
	if (i != 3)
		return (write_error("Cylinder; invalid number of coordinates"));
	if (validate_number_array(coordinates, 2) == 1)
		return (write_error("Syntax error; cylinder coordinates should be decimal numbers"));
	cylinder.position.x = ft_atofloat(coordinates[0]);
	cylinder.position.y = ft_atofloat(coordinates[1]);
	cylinder.position.z = ft_atofloat(coordinates[2]);
	free_array(coordinates);

	orientation = ft_split(values[2], ',');
	i = 0;
	while (orientation[i])
		i++;
	if (i != 3)
		return (write_error("Cylinder; invalid number of orientation coordinates"));
	if (validate_number_array(orientation, 2) == 1)
		return (write_error("Syntax error; cylinder orientation should be decimal numbers"));
	cylinder.orientation.x = ft_atofloat(orientation[0]);
	cylinder.orientation.y = ft_atofloat(orientation[1]);
	cylinder.orientation.z = ft_atofloat(orientation[2]);
	if (cylinder.orientation.x > 1.0 || cylinder.orientation.x < -1.0 || cylinder.orientation.y > 1.0 || cylinder.orientation.y < -1.0 || cylinder.orientation.z > 1.0 || cylinder.orientation.z < -1.0)
		return (write_error("Cylinder orientation values should be within a range from -1.0 to 1.0"));
	free_array(orientation);

	cylinder.rotation = vec3_to_quaternion(&cylinder.orientation);

	if (validate_decimal_string(values[3]) == 1)
		return (write_error("Syntax error; cylinder diameter should be a decimal number"));
	cylinder.radius = ft_atofloat(values[3]);
	if (cylinder.radius != 0)
		cylinder.radius = cylinder.radius / 2;

	if (validate_decimal_string(values[4]) == 1)
		return (write_error("Syntax error; cylinder height should be a decimal number"));
	cylinder.height = ft_atofloat(values[4]);

	colours = ft_split(values[5], ',');
	i = 0;
	while (colours[i])
		i++;
	if (i != 3)
		return (write_error("Cylinder; invalid number of colours"));
	if (validate_number_array(colours, 1) == 1)
		return (write_error("Syntax error; cylinder colours should be numbers in the range from 0 to 255"));
	cylinder.colour.red = ft_atoi(colours[0]);
	cylinder.colour.green = ft_atoi(colours[1]);
	cylinder.colour.blue = ft_atoi(colours[2]);
	if (cylinder.colour.red > 255 || cylinder.colour.red < 0 || cylinder.colour.green > 255 || cylinder.colour.green < 0 || cylinder.colour.blue > 255 || cylinder.colour.blue < 0)
		return (write_error("Plane; the colour values should be in the range from 0 to 255"));
	free_array(colours);
	mrt->object[mrt->object_count - 1] = cylinder;
	cylinder.cap_t = vec3_add(cylinder.position, vec3_scale(cylinder.orientation, cylinder.height * 0.5));
	cylinder.cap_b = vec3_add(cylinder.position, vec3_scale(cylinder.orientation, -cylinder.height * 0.5));
	return (0);
}

int	check_values(t_minirt *mrt, char **values)
{
	if (!values[0])
		return (1);
	if (ft_strcmp(values[0], "A") == 0)
		return (check_ambient_data(mrt, values));
	if (ft_strcmp(values[0], "C") == 0)
		return (check_camera_data(mrt, values));
	if (ft_strcmp(values[0], "L") == 0)
		return (check_light_data(mrt, values));
	if (ft_strcmp(values[0], "sp") == 0)
		return (check_sphere_data(mrt, values));
	if (ft_strcmp(values[0], "pl") == 0)
		return (check_plane_data(mrt, values));
	if (ft_strcmp(values[0], "cy") == 0)
		return (check_cylinder_data(mrt, values));
	return (0);
}

static int	check_line(t_minirt *mrt, char *line)
{
	int	i;
	int	character_count;
	char	**values;

	i = 0;
	character_count = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			character_count++;
		i++;
	}
	line[i] = '\0';
	if (character_count > 0)
	{
		values = ft_split(line, ' ');
		i = check_values(mrt, values);
		free_array(values);
		if (i == 1)
			return (1);
	}
	return (0);
}

static void	tabs_to_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
/*
//Standalone version for testing. Compile with minirt.h and libft.a
int	main(int argc, char **file)
{
	int	fd;
	char	*line;
	int	i;
	t_minirt	mrt;

	if (argc != 2)
		ft_putstr_fd("Invalid number of arguments", 2);
	fd = open(file[1], O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Couldn't open the .rt file", 2);
	ft_bzero(&mrt, sizeof(t_minirt));
	i = 0;
	while (1)
	{
		line = NULL;
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%d: %s", i, line);
		tabs_to_spaces(line);
		check_line(&mrt, line);
		free(line);
		i++;
	}
	printf("\nA = %d light ratio = %f colours = %d %d %d\n", mrt.ambient_count, mrt.ambient.brightness, mrt.ambient.colour.red, mrt.ambient.colour.green, mrt.ambient.colour.blue);
	printf("C = %d coordinates = %f %f %f orientation = %f %f %f FOV = %d\n", mrt.camera_count, mrt.camera.position.x, mrt.camera.position.y, mrt.camera.position.z, mrt.camera.orientation.x, mrt.camera.orientation.y, mrt.camera.orientation.z, mrt.camera.fov);
	printf("L = %d coordinates = %f %f %f brightness = %f colours = %d %d %d\n", mrt.light_count, mrt.light.position.x, mrt.light.position.y, mrt.light.position.z, mrt.light.brightness, mrt.light.colour.red, mrt.light.colour.green, mrt.light.colour.blue);
	i = 0;
	while (i < mrt.object_count)
	{
		if (mrt.object[i].type == SPHERE)
			printf("sp coordinates = %f %f %f radius = %f colours = %d %d %d\n", mrt.object[i].position.x, mrt.object[i].position.y, mrt.object[i].position.z, mrt.object[i].radius, mrt.object[i].colour.red, mrt.object[i].colour.green, mrt.object[i].colour.blue);
		if (mrt.object[i].type == PLANE)
			printf("pl coordinates = %f %f %f orientation = %f %f %f colours = %d %d %d\n", mrt.object[i].position.x, mrt.object[i].position.y, mrt.object[i].position.z, mrt.object[i].orientation.x, mrt.object[i].orientation.y, mrt.object[i].orientation.z, mrt.object[i].colour.red, mrt.object[i].colour.green, mrt.object[i].colour.blue);
		if (mrt.object[i].type == CYLINDER)
			printf("cy coordinates = %f %f %f orientation = %f %f %f radius = %f height = %f colours = %d %d %d\n", mrt.object[i].position.x, mrt.object[i].position.y, mrt.object[i].position.z, mrt.object[i].orientation.x, mrt.object[i].orientation.y, mrt.object[i].orientation.z, mrt.object[i].radius, mrt.object[i].height, mrt.object[i].colour.red, mrt.object[i].colour.green, mrt.object[i].colour.blue);
		i++;
	}
	free(mrt.object);
	return (0);
}*/

int	read_rt_file(t_minirt *mrt, char *file)
{
	int		fd;
	int		check;
	int		i;
	char	*line;

	i = 0;
	check = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_putstr_fd("Couldn't open the .rt file", 2);
	while (1)
	{
		line = NULL;
		line = get_next_line(fd);
		if (!line)
			break ;
		tabs_to_spaces(line);
		check = check_line(mrt, line);
		free(line);
		if (check == 1)
			return (1);
		i++;
	}
	return (0);
}
