
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

float			check_cylinder_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure cylinder, float min, float3 *normale)
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
	d = get_sqr_solve(a, b, d, min);
	*normale = get_cylinder_normale(ray_origin + ray_vector * d, cylinder);
	return (d);

	// return (get_sqr_solve(a, b, d, min));
}

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
