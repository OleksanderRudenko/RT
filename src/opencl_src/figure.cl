
#include "rt_h.cl"

float3		get_normale(float3 ray, t_cl_figure figure)
{
	float3 ret = (float3)(0.0f, 0.0f, 0.0f);
	if (figure.type == Sphere)
		ret = get_sphere_normale(ray, figure);
	else if (figure.type == InfinitePlane)
		ret = get_plane_normale(figure);
	else if (figure.type == InfiniteCylinder)
		ret = get_cylinder_normale(ray, figure);
	return (ret);
}

float		check_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure)
{
	float ret = -1;
	if (figure.type == Sphere)
		ret = check_sphere_intersection(ray_origin, ray_vector, figure);
	else if (figure.type == InfinitePlane)
		ret = check_plane_intersection(ray_origin, ray_vector, figure);
	else if (figure.type == InfiniteCylinder)
		ret = check_cylinder_intersection(ray_origin, ray_vector, figure);
	return (ret);
}

int			figure_equal(t_cl_figure figure1, t_cl_figure figure2)
{
	if (figure1.type == figure2.type)
	{
		if (is_equal(figure1.center, figure2.center) ||
			is_equal(figure1.position, figure2.position))
			return (1);
	}
	return (0);
}

int			check_intersections(float3 ray_origin, float3 ray_vector, __constant t_cl_figure *figures, size_t figures_num, t_cl_figure figure)
{
	float	k;
	size_t 	n;

	n = 0;
	while (n < figures_num)
	{
		if(figure_equal(figures[n], figure))
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
