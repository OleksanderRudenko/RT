
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
	else if (figure.type == InfiniteCone)
		ret = get_cone_normale(ray, figure);
	else if (figure.type == Elipsoid)
		ret = get_elipsoid_normale(ray, figure);
	else if (figure.type == Parabaloid)
		ret = get_paraboloid_normale(ray, figure);
	else if (figure.type == Triangle)
		ret = get_triangle_normale(ray, figure);
	else if (figure.type == Cube)
		ret = get_cube_normale(ray, figure);
	else if (figure.type == Quadrate)
		return (get_squad_normale(ray, figure));
	return (ret);
}

float		check_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *figure, float min, float3 *normale)
{
	// figure.type = InfiniteCone;
	float ret = -1;
	if (figure->type == Sphere)
		ret = check_sphere_intersection(ray_origin, ray_vector, *figure, min, normale);
	else if (figure->type == InfinitePlane)
		ret = check_plane_intersection(ray_origin, ray_vector, *figure, min, normale);
	else if (figure->type == InfiniteCylinder)
		ret = check_cylinder_intersection(ray_origin, ray_vector, *figure, min, normale);
	else if (figure->type == InfiniteCone)
		ret = check_cone_intersection(ray_origin, ray_vector, figure, min, normale);
	else if (figure->type == Elipsoid)
		ret = check_elipsoid_intersection(ray_origin, ray_vector, figure, min, normale);
	else if (figure->type == Parabaloid)
		ret = check_paraboloid_intersections(ray_origin, ray_vector, figure, min, normale);
	else if (figure->type == Triangle)
		ret = check_triangle_intersection(ray_origin, ray_vector, figure, min, normale);
	else if (figure->type == Cube)
		ret = check_cube_intersections(ray_origin, ray_vector, figure, min, normale);
	else if (figure->type == Quadrate)
		ret = check_sq_intersections(ray_origin, ray_vector, figure, min, normale);
	return (ret);
}

int			figure_equal(t_cl_figure figure1, t_cl_figure figure2)
{
	if (figure1.type == figure2.type)
	{
		if ((is_equal(figure1.center, figure2.center) ||
			is_equal(figure1.position, figure2.position)))
			return (1);
	}
	return (0);
}

int			check_intersections(float3 ray_origin, float3 ray_vector, __global t_cl_figure *figures, size_t figures_num, t_cl_figure figure)
{
	float		k;
	size_t 	n;
	float 	min;
	float3	normale;

	min = 0.01;
	n = 0;
	// return (0);
	while (n < figures_num)
	{
		k = check_intersection(ray_origin, ray_vector, (t_cl_figure*)&figures[n], min, &normale);
		// if(figure_equal(figures[n], figure) && k < 1 && k >= min)
		// {
		// 	n++;
		// 	continue;
		// }
		if (k < 1 && k > min)
			return (1);
		n++;
	}
	return (0);
}
