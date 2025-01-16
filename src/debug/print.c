#include <stdio.h>
#include "minirt.h"

void	printf_vector(t_vec3 a)
{
	printf("vector:\n");
	printf("  x=%f	 y=%f	z=%f\n", a.x, a.y, a.z);
}


void	print_all_objects(t_minirt *mrt)
{
	int	i = -1;

	while (++i < mrt->object_count)
	{
		if (mrt->object[i].shape == PLANE)
			print_plane(mrt->object[i]);
		else if (mrt->object[i].shape == SPHERE)
			print_sphere(mrt->object[i]);
		else
			print_cylinder(mrt->object[i]);
	}
}

void	print_plane(t_object plane)
{
	printf("plane:\n");
	printf("  shape: %d\n", plane.shape);
	printf("  ID: %d\n", plane.id);
	printf("  Position: %.2f, %.2f, %.2f\n", plane.position.x, plane.position.y, plane.position.z);
	printf("  Orientation: %.2f, %.2f, %.2f\n", \
		plane.orientation.x, plane.orientation.y, plane.orientation.z);
	printf("  Colour:  %d, %d, %d\n", plane.colour.red,
		plane.colour.green, plane.colour.blue);
	printf("  Rotation: %.2f, %.2f, %.2f, %.2f\n", plane.rotation.x, plane.rotation.y,
		plane.rotation.z, plane.rotation.w);
}

void	print_sphere(t_object sphere)
{
	printf("Sphere:\n");
	printf("  Shape: %d\n", sphere.shape);
	printf("  ID: %d\n", sphere.id);
	printf("  Position: %.2f, %.2f, %.2f\n", \
		sphere.position.x, sphere.position.y, sphere.position.z);
	printf("  Radius: %.2f\n", sphere.radius);
	printf("  Colour:  %d, %d, %d\n", sphere.colour.red,
		sphere.colour.green, sphere.colour.blue);
}

void	print_cylinder(t_object cylinder)
{
	printf("cylinder:\n");
	printf("  Shape: %d\n", cylinder.shape);
	printf("  ID: %d\n", cylinder.id);
	printf("  Position: %.2f, %.2f, %.2f\n", \
		cylinder.position.x, cylinder.position.y, cylinder.position.z);
	printf("  Orientation: %.2f, %.2f, %.2f\n", \
		cylinder.orientation.x, cylinder.orientation.y, cylinder.orientation.z);
	printf("  Radius: %.2f\n", cylinder.radius);
	printf("  Height: %.2f\n", cylinder.radius);
	printf("  Colour:  %d, %d, %d\n", cylinder.colour.red,
		cylinder.colour.green, cylinder.colour.blue);
	printf("  Rotation: %.2f, %.2f, %.2f, %.2f\n", cylinder.rotation.x, cylinder.rotation.y,
		cylinder.rotation.z, cylinder.rotation.w);
	printf("  cap_t: %.2f, %.2f, %.2f\n", cylinder.cap_t.x, cylinder.cap_t.y, cylinder.cap_t.z);
	printf("  cap_b: %.2f, %.2f, %.2f\n", cylinder.cap_b.x, cylinder.cap_b.y, cylinder.cap_b.z);
	printf("  cy_hit_normal: %.2f, %.2f, %.2f\n",
		cylinder.cy_hit_normal.x, cylinder.cy_hit_normal.y, cylinder.cy_hit_normal.z);
}

void	print_shape(t_object *shape)
{
	printf("ID: %d\n", shape->id);
	if (shape->shape == SPHERE)
		print_sphere(*shape);
	if (shape->shape == PLANE)
		print_plane(*shape);
	if (shape->shape == CYLINDER)
		print_cylinder(*shape);
}
