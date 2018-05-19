
#include "rt_h.cl"

float			check_plane_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure plane)
{
	float r_v;

	r_v = -1;
	if (plane.normale.x != 0 || plane.normale.y != 0 || plane.normale.z != 0)
		r_v = dot(plane.normale, subtraction(plane.point, ray_origin)) / dot(plane.normale, ray_vector);
	return (r_v);
}

float3		get_plane_normale(t_cl_figure plane)
{
	return (plane.normale);
}
