#include "minirt.h"

/*
	testing for ray_intersect_cylinder function
*/
int	main(void)
{
	t_camera	ray;
	t_object cylinder;
	t_object plane;

    ray = {
        .position = {0.0f, 0.0f, 0.0f},      // Ray starts at origin
        .direction = {1.0f, 0.0f, 0.0f},    // Direction along the x-axis
        .brightness = 1.0f                  // Maximum brightness
    };

    // Initialize t_object (cylinder)
    cylinder = {
        .shape = CYLINDER,                  // Assuming CYLINDER is a defined shape type
        .position = {0.0f, 0.0f, 0.0f},     // Cylinder at origin
        .orientation = {0.0f, 1.0f, 0.0f},  // Upward orientation
        .colour = {0, 255, 0},              // Green colour
        .radius = 1.0f,                     // Radius of 1 unit
        .height = 5.0f                      // Height of 5 units
    };

    // Initialize t_object (plane)
    plane = {
        .shape = PLANE,                     // Assuming PLANE is a defined shape type
        .position = {0.0f, -1.0f, 0.0f},    // Plane below the origin
        .orientation = {0.0f, 1.0f, 0.0f},  // Normal pointing up
        .colour = {128, 128, 128},          // Gray colour
        .radius = 0.0f,                     // Not applicable for a plane
        .height = 0.0f                      // Not applicable for a plane
    };
}
