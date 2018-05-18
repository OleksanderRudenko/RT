
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
		return (check_sphere_intersection(ray_origin, ray_vector, figure));
	if (figure.type == InfinitePlane)
		return (check_plane_intersection(ray_origin, ray_vector, figure));
	if (figure.type == InfiniteCylinder)
		return (check_cylinder_intersection(ray_origin, ray_vector, figure));
	return (-1);
}

// char	figure_equ(t_cl_figure figure1, t_cl_figure figure2)
// {
// 	if (figure1 == figure2)
// 		return (1);
// 	return (0);
// }

int			check_intersections(float3 ray_origin, float3 ray_vector, __global t_cl_figure *figures, size_t figures_num, t_cl_figure figure)
{
	float	k;
	size_t 	n;

	n = 0;
	while (n < figures_num)
	{

		if (figures[n].point.x == figure.point.x
				&& figures[n].point.y == figure.point.y
					&& figures[n].point.z == figure.point.z)
		// if(figure_equ(figures[n], figure))
		{
			n++;
			continue;
		}
		k = check_intersection(ray_origin, ray_vector, figures[n]);
		if (k < 1 && k >= 1e-11)
			return (1);
		n++;
	}
	return (0);
}
