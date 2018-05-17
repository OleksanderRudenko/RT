
#include "rt_h.cl"

float			check_cone_intersection(float3 ray_origin, float3 ray_vector, t_icone *cone)
{
	float 	a;
	float 	b;
	float 	c;
	float 	d;
	float3 	sub;

	sub = subtraction(ray_origin, cone->vertex);
	a = dot(ray_vector, ray_vector) - ((1.0f + pow(cone->radius, 2.0f)) *
										(pow(dot(ray_vector, cone->vector), 2.0f)));
	b = 2 * (dot(ray_vector, sub) - ((1.0f + pow(cone->radius, 2.0f)) *
									dot(ray_vector, cone->vector) * dot(sub, cone->vector)));
	c = dot(sub, sub) - ((1.0f + pow(cone->radius, 2.0f)) * (pow(dot(sub, cone->vector), 2.0f)));
	d = pow(b, 2.0f) - 4.0f * a * c;
	return (get_sqr_solve(a, b, d));
}

float3		get_cone_normale(float3 p, t_icone *cone)
{
	float		m;
	float3		res;
	float3 		sub;

	sub = subtraction(p, cone->vertex);
	m = pow(fast_length(sub), 2) / dot(sub, cone->vector);
	res = sum(cone->vertex, k_multiply(cone->vector, m));
	res = fast_normalize(subtraction(p, res));
	return (res);
}
