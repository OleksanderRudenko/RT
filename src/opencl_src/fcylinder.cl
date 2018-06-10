
#include "rt_h.cl"

// static float			dot_my(float3 v1, float3 v2)
// {
// 	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
// }
//
// static	float		pow_my(float d, char del)
// {
// 	if (del == 2)
// 		return (d * d);
// 	return (d);
// }

float			get_sqr_solve_buf(float a, float b, float h, float min, float *dist)
{
	float x1;
	float x2;
	// float h1;

	// if (h == 0)
		// return (-b / 2.0f * a);
	h = q_rsqrt(h);
	x1 = (-b + h) / (2.0f * a);
	x2 = (-b - h) / (2.0f * a);
	if (x1 < min)
	{
		dist[0] = x2;
		dist[1] = x1;
	}
	else if (x2 < min)
	{
		dist[0] = x1;
		dist[1] = x2;
	}
	else
	{
		if (x1 < x2)
		{
			dist[0] = x1;
			dist[1] = x2;
		}
		else
		{
			dist[0] = x2;
			dist[1] = x1;
		}
	}
	return (dist[0]);
}

float			check_cylinder_intersection1(float3 ray_origin, float3 ray_vector, t_cl_figure cylinder, float min, float3 *normale, float *dist)
{
	float 	a;
	float 	b;
	float	c;
	float 	d;
	float3 	sub;

	sub = ray_origin - cylinder.start;
	// sub = subtraction(ray_origin, cylinder.start);
	a = dot_my(ray_vector, ray_vector) - pow_my(dot_my(ray_vector, cylinder.vector), 2);
	b = 2 * (dot_my(ray_vector, sub) - dot_my(ray_vector, cylinder.vector) * dot_my(sub, cylinder.vector));
	c = dot_my(sub, sub) - pow_my(dot_my(sub, cylinder.vector), 2) - pow_my(cylinder.radius, 2);
	d = pow_my(b, 2.0f) - 4.0f * a * c;
	if (d < 0)
		return (d);
	d = get_sqr_solve_buf(a, b, d, min, dist);
	*normale = get_cylinder_normale(ray_origin + ray_vector * d, cylinder);
	return (d);
	// return (get_sqr_solve(a, b, d, min));
}

char			inside(float x, float min, float max)
{
	return ((x <= max && x >= min) || (x <= min && x >= max));
}

float			my_abs(float x)
{
	return ((x < 0) ? -x : x);
}

float			check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure cylinder, float min, float3 *normale)
{
	float dist[2];

	float3	dot_cyl[2];
	float		m[2];

	float dist_planes[2];
	float3	dot_planes_center[2];
	float3	dot_planes[2];
	float	dist_to_center_planes[2];

	if (check_cylinder_intersection1(ray_origin, ray_vector, cylinder, min, normale, dist) < min)
		return (-1);

	dot_planes_center[0] = cylinder.start + (cylinder.caps1 * cylinder.vector);
	dot_planes_center[1] = cylinder.start + (cylinder.caps2 * cylinder.vector);

	dist_planes[0] = dot_my(cylinder.vector, (dot_planes_center[0] - ray_origin)) / dot_my(cylinder.vector, ray_vector);
	dist_planes[1] = dot_my(cylinder.vector, (dot_planes_center[1] - ray_origin)) / dot_my(cylinder.vector, ray_vector);

	dot_planes[0] = ray_origin + (ray_vector * dist_planes[0]);
	dot_planes[1] = ray_origin + (ray_vector * dist_planes[1]);

	dist_to_center_planes[0] = len_my(dot_planes_center[0] - dot_planes[0]);
	dist_to_center_planes[1] = len_my(dot_planes_center[1] - dot_planes[1]);


	if (dist_to_center_planes[0] < cylinder.radius && dist_to_center_planes[1] < cylinder.radius)
	{
		// *normale = cylinder.vector;
		*normale = *normale * -1;
		if (dist_planes[0] > min && dist_planes[1] < min)
		{
			*normale = cylinder.vector;
			return (dist_planes[0]);
		}
		if (dist_planes[1] > min && dist_planes[0] < min)
		{
			*normale = cylinder.vector;
			return (dist_planes[1]);
		}
		if (dist_planes[0] < dist_planes[1])
		{
			*normale = cylinder.vector;
			return (dist_planes[0]);
		}
		*normale = cylinder.vector;
		return (dist_planes[1]);
	}

	dot_cyl[0] = ray_origin + (ray_vector * dist[0]);
	dot_cyl[1] = ray_origin + (ray_vector * dist[1]);

	m[0] = dot_my(dot_cyl[0] - cylinder.start, cylinder.vector);
	m[1] = dot_my(dot_cyl[1] - cylinder.start, cylinder.vector);

	if (!inside(m[0], cylinder.caps1, cylinder.caps2) && !inside(m[1], cylinder.caps1, cylinder.caps2))
		return (-1);
		// return (dist[0]);

	if (inside(m[0], cylinder.caps1, cylinder.caps2))
		return (dist[0]);

	if (inside(m[1], cylinder.caps1, cylinder.caps2))
	{
		*normale = *normale * -1;
		if (dist_planes[0] > min && dist_planes[1] < min)
		{
			*normale = cylinder.vector;
			return (dist_planes[0]);
		}
		if (dist_planes[1] > min && dist_planes[0] < min)
		{
			*normale = cylinder.vector;
			return (dist_planes[1]);
		}
		if (dist_planes[0] < dist_planes[1])
		{
			*normale = cylinder.vector;
			return (dist_planes[0]);
		}
		*normale = cylinder.vector;
		return (dist_planes[1]);
	}
	return (-1);
}

// float			check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure cylinder, float min, float3 *normale)
// {
// 	float 	a;
// 	float 	b;
// 	float	c;
// 	float 	d;
// 	float3 	sub;
//
// 	sub = ray_origin - cylinder.start;
// 	// sub = subtraction(ray_origin, cylinder.start);
// 	a = dot_my(ray_vector, ray_vector) - pow_my(dot_my(ray_vector, cylinder.vector), 2);
// 	b = 2 * (dot_my(ray_vector, sub) - dot_my(ray_vector, cylinder.vector) * dot_my(sub, cylinder.vector));
// 	c = dot_my(sub, sub) - pow_my(dot_my(sub, cylinder.vector), 2) - pow_my(cylinder.radius, 2);
// 	d = pow_my(b, 2.0f) - 4.0f * a * c;
// 	if (d < 0)
// 		return (d);
// 	d = get_sqr_solve(a, b, d, min);
// 	*normale = get_cylinder_normale(ray_origin + ray_vector * d, cylinder);
// 	return (d);
// 	// return (get_sqr_solve(a, b, d, min));
// }

float3		get_cylinder_normale(float3 p, t_cl_figure cylinder)
{
	float		m;
	float3		res;

	m = dot_my(p - cylinder.start, cylinder.vector);
	// m = dot_my(subtraction(p, cylinder.start), cylinder.vector);
	res = sum(cylinder.start, k_multiply(cylinder.vector, m));
	res = fast_normalize(p - res);
	return (res);
}
//
// t_vector3	find_normal_cyl(t_obj *obj, t_vector3 p)
// {
// 	double		m;
// 	t_vector3	normal;
// 	t_vector3	pc;
// 	t_vector3	a;
//
// 	pc = minus_vectors(p, obj->pos);
// 	m = skal_vectors(pc, obj->rot);
// 	a = mnoj_vector(obj->rot, m);
// 	a = add_vector(a, obj->pos);
// 	normal = minus_vectors(a, p);
// 	return (mnoj_vector(normal, 1 / len_vector(normal)));
// }
