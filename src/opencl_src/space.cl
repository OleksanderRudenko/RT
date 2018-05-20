
#include "rt_h.cl"

void	rotate_x(float3 ps, float l)
{
	float ny;
	float nz;

	ny = ps.y * native_cos(l) + ps.z * native_sin(l);
	nz = ps.z * native_cos(l) - ps.y * native_sin(l);
	ps.y = ny;
	ps.z = nz;
}

void	rotate_y(float3 ps, float l)
{
	float nx;
	float nz;

	nx = ps.x * native_cos(l) + ps.z * native_sin(l);
	nz = ps.z * native_cos(l) - ps.x * native_sin(l);
	ps.x = nx;
	ps.z = nz;
}

void	rotate_z(float3 ps, float l)
{
	float ny;
	float nx;

	nx = ps.x * native_cos(l) + ps.y * native_sin(l);
	ny = ps.y * native_cos(l) - ps.x * native_sin(l);
	ps.x = nx;
	ps.y = ny;
}

void	cam_rotate(float3 ray_origin, float3 vector)
{
	vector = k_multiply(vector, M_PI / 180);
	if (vector.x != 0)
		rotate_x(ray_origin, vector.x);
	if (vector.y != 0)
		rotate_y(ray_origin, vector.y);
	if (vector.z != 0)
		rotate_z(ray_origin, vector.z);
}

float3	get_intersection(float3 ray_origin, float3 ray_vector, float k)
{
	return (sum(k_multiply(ray_vector, k), ray_origin));
}
