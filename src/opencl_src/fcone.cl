
#include "rt_h.cl"


void			swaps_arr(float *inter_dists)
{
	float buf;

	buf = inter_dists[0];
	inter_dists[0] = inter_dists[1];
	inter_dists[1] = buf;
}


float			check_cone_intersection1(float3 ray_origin, float3 ray_vector, t_cl_figure cone, float *inter_dists, float min)
{
	float a;
	float b;
	float c;
	float d;
	float3 or_ver;

	// cone.normale = (float3){0, 0, 0};

	or_ver = ray_origin - cone.vertex;
	a = dot_my(ray_vector, ray_vector) - ((1 + pow_my(cone.radius, 2)) *
			(pow_my(dot_my(ray_vector, cone.vector), 2)));
	b = 2 * (dot_my(ray_vector, or_ver) - ((1 + pow_my(cone.radius, 2)) *
			dot_my(ray_vector, cone.vector) * dot_my(or_ver, cone.vector)));
	c = dot_my(or_ver, or_ver) - ((1 + pow_my(cone.radius, 2)) *
			(pow_my(dot_my(or_ver, cone.vector), 2)));
	d = pow_my(b, 2) - 4 * a * c;
	if (d < 0)
		return (d);
	d = q_rsqrt(d);
	inter_dists[0] = (-b + d ) / (2.0f * a);
	inter_dists[1] = (-b - d ) / (2.0f * a);
	if (inter_dists[0] < min && inter_dists[1] < min)
		return (-1);
	if (inter_dists[1] >= min)
	{
		if (inter_dists[0] < min || inter_dists[0] > inter_dists[1])
			swaps_arr(inter_dists);
	}
	return (1);
	// return (get_sqr_solve(a, b, d));
}

//
float			check_cone_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *cone, float min, float3 *normale)
{
	float	m[2];
	float inter_dists_cone[2];
	float	inter_dists_plane[2];
	float	dists_to_center[2];
	float	radiuses[2];
	float3	cone_dot[2];
	float3	dot_planes[2];

	cone->normale = (float3){0, 0, 0};

	// cone->color = cone->color_f;

	if (check_cone_intersection1(ray_origin, ray_vector, *cone, inter_dists_cone, min) < 0)
		return (-1);
		*normale = get_cone_normale(ray_origin + ray_vector * inter_dists_cone[0], *cone);
		return (inter_dists_cone[0]);
		cone->t_points[0] = cone->vector * cone->caps1 + cone->vertex;
		cone->t_points[1] = cone->vector * cone->caps2 + cone->vertex;

		inter_dists_plane[0] = dot_my(cone->vector, (cone->t_points[0] - ray_origin)) / dot_my(cone->vector, ray_vector);
		inter_dists_plane[1] = dot_my(cone->vector, (cone->t_points[1] - ray_origin)) / dot_my(cone->vector, ray_vector);




		if (inter_dists_cone[0] > inter_dists_plane[0] && inter_dists_cone[0] > inter_dists_plane[1])
		{
			if (inter_dists_cone[1] > inter_dists_plane[0] && inter_dists_cone[1] > inter_dists_plane[1])
			{
				return (-1);
			}
			if (inter_dists_cone[1] < inter_dists_plane[0] && inter_dists_cone[1] < inter_dists_plane[1])
			{
				return (-1);
			}
			// return (inter_dists_cone[0]);
		}

		if (inter_dists_cone[0] < inter_dists_plane[0] && inter_dists_cone[0] < inter_dists_plane[1])
		{
			if (inter_dists_cone[1] < inter_dists_plane[0] && inter_dists_cone[1] < inter_dists_plane[1])
			{
				return (-1);
			}
			if (inter_dists_cone[1] > inter_dists_plane[0] && inter_dists_cone[1] > inter_dists_plane[1])
				return (-1);
			return (inter_dists_cone[0]);
		}

		if (inter_dists_plane[0] < inter_dists_plane[1])
		{
				float radius = cone->caps1 * (cone->radius * cone->radius);
				radius = 1;
				radius = (radius < 0) ? (-radius) : (radius);
				float3 dot_plane = ray_origin + ray_vector * inter_dists_plane[0];
				float dist = fast_length(dot_plane - cone->t_points[0]);
				if (dist < radius)
				{
					cone->normale = cone->vector;
					cone->color = cone->color_c1;
					return(inter_dists_plane[0]);
				}
				// return (inter_dists_cone[0]);
		}

		if (inter_dists_plane[0] > inter_dists_plane[1])
		{
			float radius = cone->caps2 * (cone->radius * cone->radius);
			radius = 1;
			radius = (radius < 0) ? (-radius) : (radius);
			float3 dot_plane = ray_origin + ray_vector * inter_dists_plane[1];
			float dist = fast_length(dot_plane - cone->t_points[1]);
			if (dist < radius)
			{
				cone->normale = cone->vector;
				cone->color = cone->color_c2;
				return(inter_dists_plane[1]);
			}
			// return (inter_dists_cone[1]);
				// cone->normale = cone->vector;
				// cone->color = cone->color_c2;
				// return(inter_dists_plane[1]);
		}

		return (inter_dists_cone[0]);































	cone->color = cone->color_f;
	cone->normale = (float3){0, 0, 0};
	cone_dot[0] = ray_origin + inter_dists_cone[0] * ray_vector;
	cone_dot[1] = ray_origin + inter_dists_cone[1] * ray_vector;
	m[0] = dot_my(cone_dot[0] - cone->vertex, cone->vector);
	if ((m[0] >= cone->caps1 && m[0] <= cone->caps2) ||
			(m[0] <= cone->caps1 && m[0] >= cone->caps2))
	{
		cone->color = cone->color_f;
		return (inter_dists_cone[0]);
	}
	return (-1);

	// return (-1);

	m[1] = dot_my(cone_dot[1] - cone->vertex, cone->vector);

	if ((m[1] >= cone->caps1 && m[1] >= cone->caps2) ||
			(m[1] <= cone->caps1 && m[1] <= cone->caps2))
				// return (inter_dists_cone[1]);
		return (-1);

		cone->color = cone->color_f;
		// return (inter_dists_cone[1]);

	// if ((m[1] >= cone->caps1 && m[1] <= cone->caps2) ||
	// 		(m[1] <= cone->caps1 && m[1] >= cone->caps2))
	// {
	// 	cone->color = cone->color_f;
	// 	return (inter_dists_cone[1]);
	// }

	cone->t_points[0] = cone->vector * cone->caps1 + cone->vertex;
	cone->t_points[1] = cone->vector * cone->caps2 + cone->vertex;

	inter_dists_plane[0] = dot_my(cone->vector, (cone->t_points[0] - ray_origin)) / dot_my(cone->vector, ray_vector);
	inter_dists_plane[1] = dot_my(cone->vector, (cone->t_points[1] - ray_origin)) / dot_my(cone->vector, ray_vector);

	if (inter_dists_plane[0] < 0 && inter_dists_plane[1] < 0)
		return (-1);

	dot_planes[0] = ray_origin + inter_dists_plane[0] * ray_vector;
	dot_planes[1] = ray_origin + inter_dists_plane[1] * ray_vector;

	dists_to_center[0] = len_my(dot_planes[0] - cone->t_points[0]);
	dists_to_center[1] = len_my(dot_planes[1] - cone->t_points[1]);


	// radiuses[0] = cone->caps1 * (cone->radius);
	// radiuses[1] = cone->caps2 * (cone->radius);


	radiuses[0] = cone->caps1 * (1 + cone->radius * cone->radius);
	radiuses[1] = cone->caps2 * (1 + cone->radius * cone->radius);

	// radiuses[0] *= radiuses[0];
	// radiuses[1] *= radiuses[1];


	radiuses[0] = radiuses[0] < 0 ? -radiuses[0] : radiuses[0];
	radiuses[1] = radiuses[1] < 0 ? -radiuses[1] : radiuses[1];

	// printf("%f-RAIUS1\n", radiuses[0]);
	// printf("%f-RAIUS2\n", radiuses[1]);


	if (dists_to_center[0] > radiuses[0])
		inter_dists_plane[0] = -1;

	if (dists_to_center[1] > radiuses[1])
		inter_dists_plane[1] = -1;

	if (inter_dists_plane[0] < 0 && inter_dists_plane[1] < 0)
	{
			cone->color = 0xffff00;
			cone->normale = cone->vector;
      //
			return (inter_dists_cone[1]);

			return (-1);
	}


	if (inter_dists_plane[0] < 0 && inter_dists_plane[1] > 0)
	{
		cone->normale = cone->vector;
		cone->color = cone->color_c2;
		return (inter_dists_plane[1]);
	}

	if (inter_dists_plane[0] > 0 && inter_dists_plane[1] < 0)
	{
		cone->normale = cone->vector;
		cone->color = cone->color_c1;
		return (inter_dists_plane[0]);
	}

	if (inter_dists_plane[0] < inter_dists_cone[1])
	{
		cone->normale = cone->vector;
		cone->color = cone->color_c1;
		return (inter_dists_plane[0]);
	}

	if (inter_dists_plane[1] < inter_dists_cone[1])
	{
		cone->normale = cone->vector;
		cone->color = cone->color_c2;
		return (inter_dists_plane[1]);
	}
	return (inter_dists_cone[1]);

	return (-1);

}



float			check_cone_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *cone)
{
	float a;
	float b;
	float c;
	float d;
	float3 or_ver;
	float inter_dists[2];
	float	plane_dists[2];
	float3	planes_dot[2];
	float	dist_to_center[2];
	float	radiuses_for_dist[2];


	return (check_cone_intersection(ray_origin, ray_vector, cone, 0, 0));
	// cone->color = cone->color_f;
	cone->normale = (float3){0, 0, 0};
	// cone->normale.x = 0;
	// cone->normale.y = 0;
	// cone->normale.z = 0;

	if (check_cone_intersection1(ray_origin, ray_vector, *cone, inter_dists, 0) < 0)
		return (-1);
		return (inter_dists[0]);
//DELETE!!
	cone->t_points[0] = cone->vector * cone->caps1 + cone->vertex;
	cone->t_points[1] = cone->vector * cone->caps2 + cone->vertex;

	planes_dot[0] = ray_origin + inter_dists[0] * ray_vector;
	planes_dot[1] = ray_origin + inter_dists[1] * ray_vector;

	// d = dot_my(cone->vector, ray_vector);
	// if (d == 0)
	// {
		a = dot_my(planes_dot[0] - cone->vertex, cone->vector);
		if ((a >= cone->caps1 && a <= cone->caps2) ||
					(a <= cone->caps1 && a >= cone->caps2))
					{
						// cone->normale = (float3){0, 0, 0};

						cone->color = cone->color_f;
						return (inter_dists[0]);
					}
					// if (d == 0)
					// 	return (-1);
		a = dot_my(planes_dot[1] - cone->vertex, cone->vector);
		if ((a >= cone->caps1 && a <= cone->caps2) ||
					(a <= cone->caps1 && a >= cone->caps2))
		{
						/*
								INVIS_CAPS
							cone->color = cone->color_f;
							return (inter_dists[1]);
						*/

						d = dot_my(cone->vector, ray_vector);

			plane_dists[0] = dot_my(cone->vector, (cone->t_points[0] - ray_origin)) / d;
			plane_dists[1] = dot_my(cone->vector, (cone->t_points[1] - ray_origin)) / d;

			// plane_dists[0] = len_my(cone->t_points[0] - planes_dot[0]);
			// plane_dists[1] = len_my(cone->t_points[1] - planes_dot[1]);
			// cone->normale = cone->vector;
      //
			// if (plane_dists[0] < plane_dists[1])
			// {
			// 		cone->color = cone->color_c1;
			// 		return (dot_my(cone->vector, (cone->t_points[0] - ray_origin) / d));
			// }
			// cone->color = cone->color_c2;
			// return (dot_my(cone->vector, (cone->t_points[1] - ray_origin) / d));

			if (plane_dists[0] < 0 && plane_dists[1] < 0)
				return (-1);
      //
			cone->normale = cone->vector;
			if (plane_dists[0] > 0 && plane_dists[1] < 0)
			{
				// cone->normale = cone->vector;

				cone->color = cone->color_c1;
				return (plane_dists[0]);
			}

			if (plane_dists[0] < 0 && plane_dists[1] > 0)
			{
				// cone->normale = cone->vector;

				cone->color = cone->color_c2;
				return (plane_dists[1]);
			}

			if (plane_dists[0] < plane_dists[1])
			{
				// cone->normale = cone->vector;

				cone->color = cone->color_c1;
				return (plane_dists[0]);
			}
			cone->color = cone->color_c2;
			// cone->normale = cone->vector;

			return (plane_dists[1]);
			// return ((plane_dists[0] < plane_dists[1]) ? (plane_dists[0]) : plane_dists[1]);
		}

		return (-1);
			// d = dot_my(p - cylinder.start, cylinder.vector);

	// }















	// plane_dists[0] = dot_my(cone->vector, (cone->t_points[0] - ray_origin) / d);
	// plane_dists[1] = dot_my(cone->vector, (cone->t_points[1] - ray_origin) / d);
  //
  //
	// if (plane_dists[0] < 0 && plane_dists[1] < 0)
	// 	return (-1);
  //
	// a = dot_my(planes_dot[0] - cone->vertex, cone->vector);
	// if ((a > cone->caps1 && a < cone->caps2) ||
	// 			(a < cone->caps1 && a > cone->caps2))
	// 			return (inter_dists[0]);
	// a = dot_my(planes_dot[1] - cone->vertex, cone->vector);
  //
	// planes_dot[0] = ray_origin + plane_dists[0] * ray_vector;
	// planes_dot[1] = ray_origin + plane_dists[1] * ray_vector;
  //
	// // radiuses_for_dist[0] = dot_my(planes_dot[0] - cone->vertex, cone->vector);
	// // radiuses_for_dist[1] = dot_my(planes_dot[1] - cone->vertex, cone->vector);
  //
  //
  //
	// dist_to_center[0] = len_my(planes_dot[0] - cone->t_points[0]);
	// dist_to_center[1] = len_my(planes_dot[1] - cone->t_points[1]);
  //
	// radiuses_for_dist[0] = cone->caps1 * cone->radius;
	// radiuses_for_dist[1] = cone->caps2 * cone->radius;
  //
	// if (dist_to_center[0] > radiuses_for_dist[0] && dist_to_center[1] > radiuses_for_dist[1])
	// 	return (inter_dists[0]);
	// if (dist_to_center[0] > radiuses_for_dist[0] && dist_to_center[1] < radiuses_for_dist[1])
	// 	d = plane_dists[1];
	// else if (dist_to_center[0] < radiuses_for_dist[0] && dist_to_center[1] > radiuses_for_dist[1])
	// 	d = plane_dists[0];
	// else
	// {
	// 	if (plane_dists[0] < 0)
	// 		d = plane_dists[1];
	// 	else if (plane_dists[1] < 0)
	// 		d = plane_dists[0];
	// 	else
	// 		d = (plane_dists[0] < plane_dists[1]) ? (plane_dists[0]) : (plane_dists[1]);
	// }
	// if (inter_dists[0] < d)
	// 	return (inter_dists[0]);
	// if (inter_dists[0] > d)
	// 	return (-1);
	// cone->normale = cone->vector;
	// return (d);
	// // if (dist_to_center[0] < )
	// // !!!!!!!!!!!!!!!!!!!!!!!!!!!
	// return (inter_dists[0]);




	// or_ver = ray_origin - cone->vertex;
	// a = dot_my(ray_vector, ray_vector) - ((1 + pow_my(cone->radius, 2)) *
	// 		(pow_my(dot_my(ray_vector, cone->vector), 2)));
	// b = 2 * (dot_my(ray_vector, or_ver) - ((1 + pow_my(cone.radius, 2)) *
	// 		dot_my(ray_vector, cone.vector) * dot_my(or_ver, cone.vector)));
	// c = dot_my(or_ver, or_ver) - ((1 + pow_my(cone.radius, 2)) *
	// 		(pow_my(dot_my(or_ver, cone.vector), 2)));
	// d = pow_my(b, 2) - 4 * a * c;
	// if (d < 0)
	// 	return (d);
	// return (get_sqr_solve(a, b, d));
}
//
// float			check_cone_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *cone)
// {
// 	float a;
// 	float b;
// 	float c;
// 	float d;
// 	float3 or_ver;
//
// 	cone->normale = (float3){0, 0, 0};
// 	cone->color = cone->color_f;
//
// 	or_ver = ray_origin - cone->vertex;
// 	a = dot_my(ray_vector, ray_vector) - ((1 + pow_my(cone->radius, 2)) *
// 			(pow_my(dot_my(ray_vector, cone->vector), 2)));
// 	b = 2 * (dot_my(ray_vector, or_ver) - ((1 + pow_my(cone->radius, 2)) *
// 			dot_my(ray_vector, cone->vector) * dot_my(or_ver, cone->vector)));
// 	c = dot_my(or_ver, or_ver) - ((1 + pow_my(cone->radius, 2)) *
// 			(pow_my(dot_my(or_ver, cone->vector), 2)));
// 	d = pow_my(b, 2) - 4 * a * c;
// 	if (d < 0)
// 		return (d);
// 	return (get_sqr_solve(a, b, d));
// }

float3		get_cone_normale(float3 p, t_cl_figure cone)
{
	float		m;
	float3	res;

	if (cone.normale.x == 0 && cone.normale.y == 0 && cone.normale.z == 0)
	{
		m = pow_my(len_my(subtraction(p, cone.vertex)), 2) / dot_my(subtraction(p,
		// m = pow_my(fast_length(subtraction(p, cone.vertex)), 2) / dot_my(subtraction(p,
				cone.vertex), cone.vector);
		res = sum(cone.vertex, k_multiply(cone.vector, m));
		res = fast_normalize(subtraction(p, res));
		return (res);
	}
	return (cone.normale);
}
