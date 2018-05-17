
#include "rt_h.cl"

float			check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_icylinder *cylinder)
{
	float 	a;
	float 	b;
	float	c;
	float 	d;
	float3 	sub;

	sub = subtraction(ray_origin, cylinder->start);
	a = dot(ray_vector, ray_vector) - pow(dot(ray_vector, cylinder->vector), 2);
	b = 2 * (dot(ray_vector, sub) - dot(ray_vector, cylinder->vector) * dot(sub, cylinder->vector));
	c = dot(sub, sub) - pow(dot(sub, cylinder->vector), 2) - pow(cylinder->radius, 2);
	d = pow(b, 2.0f) - 4.0f * a * c;
	return (get_sqr_solve(a, b, d));
}

float3		get_cylinder_normale(float3 p, t_icylinder *cylinder)
{
	float		m;
	float3		res;

	m = dot(subtraction(p, cylinder->start), cylinder->vector);
	res = sum(cylinder->start, k_multiply(cylinder->vector, m));
	res = fast_normalize(subtraction(p, res));
	return (res);
}
