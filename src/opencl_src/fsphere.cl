
#include "rt_h.cl"

float			get_sqr_solve(float a, float b, float h, float min)
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
		return (x2);
	if (x2 < min)
		return (x1);
	return (x1 <= x2 ? x1 : x2);
}

float			check_sphere_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure, float min, float3 *normale)
{
	float3		buf;
	float		a;
	float		b;
	float		c;
	float		h;

	a = ray_vector.x * ray_vector.x + ray_vector.y * ray_vector.y + ray_vector.z * ray_vector.z;
	buf = ray_origin - figure.center;
	b = buf.x * ray_vector.x + buf.y * ray_vector.y + buf.z * ray_vector.z;
	b += b;
	c = buf.x * buf.x + buf.y * buf.y + buf.z * buf.z;
	c -= figure.radius * figure.radius;
	h = b * b - (4.0f * a * c);
	if (h < 0.0f)
		return (-1.0f);
	h = get_sqr_solve(a, b, h, min);
	*normale = get_sphere_normale(ray_origin + ray_vector * h, figure);
	return (h);
	// return (get_sqr_solve(a, b, h, min));
}

float3		get_sphere_normale(float3 p, t_cl_figure f)
{
	return (fast_normalize(p - f.center));
}
