
#include "rt_h.cl"

float			check_plane_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure plane, float min, float3 *normale)
{
	float r_v;

	r_v = -1;
	if (plane.normale.x != 0 || plane.normale.y != 0 || plane.normale.z != 0)
		r_v = dot_my(plane.normale, subtraction(plane.point, ray_origin)) / dot_my(plane.normale, ray_vector);
	min = 0;
	*normale = plane.normale;
	return (r_v);
}

float3		get_plane_normale(t_cl_figure plane)
{
	return (plane.normale);
}
