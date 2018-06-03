
#include "rt_h.cl"

float3  				get_squad_normale(float3 p, t_cl_figure q)
{
  return (q.normale);
}

float					check_sq_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *q, float min, float3 *normale)
{
  *normale = q->normale;
  return (check_intersection_squad(ray_origin, ray_vector, q->q_points, q->normale));
}
