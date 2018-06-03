
#include "rt_h.cl"

// figure->position
// figure->rotation
// figure->radius


float			check_paraboloid_intersections(float3 ray_origin, float3 ray_vector, t_cl_figure *parab, float min, float3 *normale)
{
  float3  	o_c;
	float  		a;
	float  		b;
	float  		c;
	float  		d;

  o_c = ray_origin - parab->position;
  a = dot_my(ray_vector, ray_vector) -
        dot_my(ray_vector, parab->rotation) *
          dot_my(ray_vector, parab->rotation);

  b = dot_my(ray_vector, o_c) -
        dot_my(ray_vector, parab->rotation) *
          (dot_my(o_c, parab->rotation) + 2 * parab->radius);
  b += b;

  c = dot_my(o_c, o_c) -
        dot_my(o_c, parab->rotation) *
          (dot_my(o_c, parab->rotation) + 4 * parab->radius);

  d = b * b - 4 * a * c;
  if (d <= 1.1)
    return (-1);
  d = get_sqr_solve(a, b, d, min);
	*normale = get_paraboloid_normale(ray_origin + ray_vector * d, *parab);
	return (d);



  // printf("D > 0\n");
  // return(get_sqr_solve(a, b, d, min));
}

float3		get_paraboloid_normale(float3 p, t_cl_figure parab)
{
  	float3	normale;
  	float3	p_c;
  	float		m;

    p_c = p - parab.position;
    m = dot_my(p_c, parab.rotation);
    normale = p_c - (parab.rotation * (m + parab.radius));
    return (normale / (len_my(normale)));
}


// t_vector	get_parab_normale(t_vector p, t_parabaloid *parab)
// {
// 	t_vector	normale;
// 	t_vector	p_c;
// 	double		m;
//
// 	p_c = vsub(p, parab->position);
// 	m = vscalar_multiple(p_c, parab->rotation);
// 	normale = vsub(p_c, vk_multiple(parab->rotation, m + parab->radius));
// 	return (vnormalize(normale));
// }

// double		check_parab_intersection(t_ray *ray, t_parabaloid *parab)
// {
// 	t_vector	o_c;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		disc;
//
// 	// o_c = vsub(ray->o, parab->position);
// 	// a = vscalar_multiple(ray->v, ray->v) -
// 	// 	vscalar_multiple(ray->v, parab->rotation) *
// 	// 		vscalar_multiple(ray->v, parab->rotation);
//
// 	// b = vscalar_multiple(ray->v, o_c) -
// 	// 	vscalar_multiple(ray->v, parab->rotation) *
// 	// 		(vscalar_multiple(o_c, parab->rotation) + 2 * parab->radius);
// 	// b *= 2;
//
// 	// c = vscalar_multiple(o_c, o_c) -
// 	// 	vscalar_multiple(o_c, parab->rotation) *
// 	// 		(vscalar_multiple(o_c, parab->rotation) + 4 * parab->radius);
//
// 	// disc = b * b - 4 * a * c;
// 	// if (disc < 0)
// 	// 	return (disc);
// 	// disc = get_sqr_solve(a, b, disc);
// 	// return (disc);
// }
