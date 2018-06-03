
#include "rt_h.cl"

static char        inside_triangle(t_cl_figure *triangle, float3 p)
{
  float3	v[3];
  float3	v_p[3];

  v[0] = vnormalize(triangle->t_points[0] - triangle->t_points[1]);
  v[1] = vnormalize(triangle->t_points[1] - triangle->t_points[2]);
  v[2] = vnormalize(triangle->t_points[2] - triangle->t_points[0]);

  v_p[0] = vnormalize(triangle->t_points[0] - p);
  v_p[1] = vnormalize(triangle->t_points[1] - p);
  v_p[2] = vnormalize(triangle->t_points[2] - p);

	v_p[0] = cross_vec(v[0], v_p[0]);
	v_p[1] = cross_vec(v[1], v_p[1]);
	v_p[2] = cross_vec(v[2], v_p[2]);

  v[0].x = dot_my(v_p[0], triangle->normale);
  v[1].x = dot_my(v_p[1], triangle->normale);
  v[2].x = dot_my(v_p[2], triangle->normale);

  if ((v[0].x <= 0 && v[1].x <= 0 && v[2].x <= 0) ||
      (v[0].x >= 0 && v[1].x >= 0 && v[2].x >= 0))
    return (1);
  return (0);
}

float			check_triangle_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *triangle, float min, float3 *normale)
{
  float r_v;

  r_v = dot_my(triangle->normale, triangle->t_points[0] - ray_origin) /
        dot_my(triangle->normale, ray_vector);
  *normale = triangle->normale;
  if (r_v > 0 && inside_triangle(triangle, ray_origin + (ray_vector * r_v)))
    return (r_v);
  return (-1);
}

float3  get_triangle_normale(float3 p, t_cl_figure triangle)
{
  return (triangle.normale);
}
