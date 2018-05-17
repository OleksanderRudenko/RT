
#include "rt_h.cl"

float3		get_normale(float3 ray, __global t_figure *f)
{
	if (f->type == Sphere)
		return (get_sphere_normale(ray, f->figure));
	else if (f->type == InfinitePlane)
		return (get_plane_normale(f->figure));
	else if (f->type == InfiniteCylinder)
		return (get_cylinder_normale(ray, f->figure));
	else if (f->type == InfiniteCone)
		return (get_cone_normale(ray, f->figure));
	return ((float3)(0.0f, 0.0f, 0.0f));
}

float		check_intersection(float3 ray_origin, float3 ray_vector, __global t_figure *figure)
{
	return (check_sphere_intersection(ray_origin, ray_vector, figure->figure));
	if (figure->type == Sphere)
		return (check_sphere_intersection(ray_origin, ray_vector, figure->figure));
	if (figure->type == InfinitePlane)
		return (check_plane_intersection(ray_origin, ray_vector, figure->figure));
	if (figure->type == InfiniteCylinder)
		return (check_cylinder_intersection(ray_origin, ray_vector, figure->figure));
	if (figure->type == InfiniteCone)
		return (check_cone_intersection(ray_origin, ray_vector, figure->figure));
	return (-1);
}

int			check_intersections(float3 ray_origin, float3 ray_vector, __global t_figure *figures)
{
	__global t_figure	*it;
	float				k;

	it = figures;
	while (it)
	{
		k = check_intersection(ray_origin, ray_vector, it);
		if (k < 1 && k >= 1e-11)
			return (1);
		it = it->next;
	}
	return (0);
}