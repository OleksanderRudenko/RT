
#include "rt_h.cl"

float			get_sqr_solve(float a, float b, float h)
{
	float x1;
	float x2;

	if (h == 0)
		return (-b / 2.0f * a);
	x1 = (-b + sqrt(h)) / (2.0f * a);
	x2 = (-b - sqrt(h)) / (2.0f * a);
	if (x1 <= 1e-11)
		return (x2);
	if (x2 <= 1e-11)
		return (x1);
	return (x1 <= x2 ? x1 : x2);
}

float			check_sphere_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure figure)
{
	float3		buf;
	float		a;
	float		b;
	float		c;
	float		h;

	a = dot(ray_vector, ray_vector);
	buf = subtraction(ray_origin, figure.center);
	b = 2.0f * (dot(buf, ray_vector));
	c = dot(buf, buf) - (figure.radius * figure.radius);
	h = pow(b, 2) - (4.0f * a * c);
	if (h < 0.0f)
		return (-1.0f);
	else
		return (get_sqr_solve(a, b, h));
	return (0.0f);
}

float3		get_sphere_normale(float3 p, t_cl_figure f)
{
	return (fast_normalize(subtraction(p, f.center)));
}
