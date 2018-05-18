
#include "rt_h.cl"

float3		get_normale(float3 ray, t_cl_figure figure)
{
	if (figure.type == Sphere)
		return (get_sphere_normale(ray, figure));
	else if (figure.type == InfinitePlane)
		return (get_plane_normale(figure));
	else if (figure.type == InfiniteCylinder)
		return (get_cylinder_normale(ray, figure));
	return ((float3)(0.0f, 0.0f, 0.0f));
}

float		check_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure)
{
	if (figure.type == Sphere)
	{
		printf("Sphere intersection\n");
		return (check_sphere_intersection(ray_origin, ray_vector, figure));
	}
	if (figure.type == InfinitePlane)
	{
		printf("Plane intersection\n");
		return (check_plane_intersection(ray_origin, ray_vector, figure));
	}
	if (figure.type == InfiniteCylinder)
	{
		printf("Cylinder intersection\n");
		return (check_cylinder_intersection(ray_origin, ray_vector, figure));
	}
	return (-1);
}

int			check_intersections(float3 ray_origin, float3 ray_vector, __global t_cl_figure *figures, size_t figures_num)
{
	float	k;
	size_t 	n;

	n = 0;
	while (n < figures_num)
	{
		k = check_intersection(ray_origin, ray_vector, figures[n]);
		if (k < 1 && k >= 1e-11)
			return (1);
		n++;
	}
	return (0);
}
