

#include "rt_h.cl"

// char        inside_squad(float3 *c_points, float3 p, float3 normale)
// {
//   float3	v[3];
//   float3	v_p[3];
//
//   v[0] = vnormalize(c_points[0] - c_points[1]);
//   v[1] = vnormalize(c_points[1] - c_points[2]);
//   v[2] = vnormalize(c_points[2] - c_points[3]);
//   v[3] = vnormalize(c_points[3] - c_points[0]);
//
//   v_p[0] = vnormalize(c_points[0] - p);
//   v_p[1] = vnormalize(c_points[1] - p);
//   v_p[2] = vnormalize(c_points[2] - p);
//   v_p[3] = vnormalize(c_points[3] - p);
//
// 	v_p[0] = cross_vec(v[0], v_p[0]);
// 	v_p[1] = cross_vec(v[1], v_p[1]);
//   v_p[2] = cross_vec(v[2], v_p[2]);
// 	v_p[3] = cross_vec(v[3], v_p[3]);
//
//   v[0].x = dot_my(v_p[0], normale);
//   v[1].x = dot_my(v_p[1], normale);
//   v[2].x = dot_my(v_p[2], normale);
//   v[3].x = dot_my(v_p[3], normale);
//
//   if ((v[0].x <= 0 && v[1].x <= 0 && v[2].x <= 0) ||
//       (v[0].x >= 0 && v[1].x >= 0 && v[2].x >= 0))
//     return (1);
//   return (0);
// }
//
char	     inside_squad(float3 *c_points, float3 p)
{
  float3	v[4];
	float3	v_p[4];

	v[0] = c_points[0] - c_points[1];
	v[1] = c_points[1] - c_points[2];
	v[2] = c_points[2] - c_points[3];
	v[3] = c_points[3] - c_points[0];

	v_p[0] = p - c_points[0];
	v_p[1] = p - c_points[1];
	v_p[2] = p - c_points[2];
	v_p[3] = p - c_points[3];

	v[0].x = dot_my(v_p[0], v[0]);
	v[1].x = dot_my(v_p[1], v[1]);
	v[2].x = dot_my(v_p[2], v[2]);
	v[3].x = dot_my(v_p[3], v[3]);

  // printf("%f, %f, %f, %f\n", v[0].x, v[1].x, v[2].x, v[3].x);
	if ((v[0].x < 0 && v[1].x < 0 && v[2].x < 0 && v[3].x < 0) ||
		(v[0].x > 0 && v[1].x > 0 && v[2].x > 0 && v[3].x > 0))
		return (1);
	return (0);
}

float     check_intersection_squad(float3 ray_origin, float3 ray_vector, float3 *c_points, float3 normale)
{
  float r_v;

  r_v = dot_my(normale, (c_points[0] - ray_origin)) / dot_my(normale, ray_vector);
  // printf("%f, %f, %f- NORMALE INSIDE!!\n", normale.x, normale.y, normale.z);
  if (r_v > 0 && inside_squad(c_points, ray_origin + (ray_vector * r_v)))
  // if (r_v > 0 && inside_squad(c_points, ray_origin + (ray_vector * r_v), normale))
    return (r_v);
  return (-1);
}

float			check_cube_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *cube, float min, float3 *normale)
{
  int 		i;
  int     find_i;
	float		rez;
	float		find_dist;

  i = 0;
  find_i = -1;
  find_dist = -1;
  while (i < 6)
  {
    rez = check_intersection_squad(ray_origin, ray_vector, &(cube->c_points[i * 4]), cube->c_normale[i]);
    if ((find_dist < 0 && rez > 0) || (rez < find_dist && rez > 0))
    {
      find_dist = rez;
      find_i = i;
    }
    ++i;
  }
  if (find_dist < 0)
    return (-1);
  cube->normale = cube->c_normale[find_i];
  *normale = cube->c_normale[find_i];
  return (find_dist);
}

float3  				get_cube_normale(float3 p, t_cl_figure cube)
{
  return (cube.normale);
}



// char	inside_squad(t_squard *plane, t_vector p)
// {
// 	t_vector	v[4];
// 	t_vector	v_p[4];
//
// 	v[0] = vsub(plane->points[0], plane->points[1]);
// 	v[1] = vsub(plane->points[1], plane->points[2]);
// 	v[2] = vsub(plane->points[2], plane->points[3]);
// 	v[3] = vsub(plane->points[3], plane->points[0]);
//
// 	v_p[0] = vsub(p, plane->points[0]);
// 	v_p[1] = vsub(p, plane->points[1]);
// 	v_p[2] = vsub(p, plane->points[2]);
// 	v_p[3] = vsub(p, plane->points[3]);
//
// 	v[0].x = vscalar_multiple(v_p[0], v[0]);
// 	v[1].x = vscalar_multiple(v_p[1], v[1]);
// 	v[2].x = vscalar_multiple(v_p[2], v[2]);
// 	v[3].x = vscalar_multiple(v_p[3], v[3]);
//
// 	if ((v[0].x < 0 && v[1].x < 0 && v[2].x < 0 && v[3].x < 0) ||
// 		(v[0].x > 0 && v[1].x > 0 && v[2].x > 0 && v[3].x > 0))
// 		return (1);
// 	return (0);
// }

// double	check_intersection_squad(t_ray *ray, t_squard *squard)
// {
//     double r_v;
//
//     r_v = -1;
//     if (squard->normale.x != 0 || squard->normale.y != 0 || squard->normale.z != 0)
//         r_v = vscalar_multiple(squard->normale, vsub(squard->points[0], ray->o)) /
//               vscalar_multiple(squard->normale, ray->v);
//     if (r_v > 0 && inside_squad(squard, vsum(vk_multiple(ray->v, r_v), ray->o)))
//         return (r_v);
//     return (-1);
// }
//
// double	check_cube_intersection(t_ray *ray, t_cube *cube)
// {
// 	int 		i;
// 	double		rez;
// 	double		find_dist;
//
// 	i = 0;
// 	cube->finded_plane = NULL;
// 	find_dist = -1;
// 	while (i < 6)
// 	{
// 		rez = check_intersection_squad(ray, &cube->planes[i]);
// 		if ((find_dist < 0 && rez > 0) || (rez < find_dist && rez > 0))
// 		{
// 			cube->finded_plane = &cube->planes[i];
// 			find_dist = rez;
// 		}
// 		++i;
// 	}
// 	if (!cube->finded_plane)
// 		return (-1);
// 	return (find_dist);
// }
