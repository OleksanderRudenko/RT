
#include "rt_h.cl"

float			check_elipsoid_intersection(float3 ray_origin, float3 ray_vector, t_cl_figure *elips, float min, float3 *normale)
{
  float   ac[2];
  float   r;
  float   a;
  float   b;
  float   c;
  float   d;
  float3  o_c;


  o_c = ray_origin - elips->position;
  r = elips->rdistance + 2 * elips->radius;
  r *= r;

  // printf("%f, %f, %f- elips->rotation\n", elips->rotation.x, elips->rotation.y, elips->rotation.z);
  // printf("%f, %f, %f- elips->position\n", elips->position.x, elips->position.y, elips->position.z);

  ac[0] = 2 * elips->rdistance * dot_my(ray_vector, elips->rotation);
  ac[1] = r + 2 * elips->rdistance *
    dot_my(o_c, elips->rotation) - elips->rdistance;
  a = 4 * r * dot_my(ray_vector, ray_vector) - ac[0] * ac[0];
  b = 4 * r * dot_my(ray_vector, o_c) - ac[0] * ac[1];
  b += b;
  c = 4 * r * dot_my(o_c, o_c) - ac[1] * ac[1];
  d = b * b - 4 * a * c;
  if (d < 0)
		return (d);
	d = get_sqr_solve(a, b, d, min);
	*normale = get_elipsoid_normale(ray_origin + ray_vector * d, *elips);
	return (d);
  // printf("D > 0\n");
  // return(get_sqr_solve(a, b, d, min));
}


float3		get_elipsoid_normale(float3 p, t_cl_figure elips)
{
  float3  dot_center;
  float3  p_c;
  float3  normale;
  float   a;
  float   b;
  float   buf;

  buf = elips.rdistance / 2;
  dot_center = elips.rotation * buf;
  dot_center = elips.position + dot_center;

  p_c = p - dot_center;
  a = 2 * elips.radius + elips.rdistance;
  b = a * a - elips.rdistance * elips.rdistance;
  buf = (b / (a * a)) * dot_my(p_c, elips.rotation);
  normale = p_c - (elips.rotation * buf);
  return (normale / (len_my(normale)));
}

// t_vector		get_elips_normale(t_vector p, t_elipsoid *elips)
// {
// 	t_vector	dot_center;
// 	t_vector	p_c;
// 	t_vector	normale;
// 	double		a;
// 	double		b;
//
// 	dot_center = vsum(elips->position, vk_multiple(elips->rotation, elips->rdistance / 2));
// 	p_c = vsub(p, dot_center);
// 	a = 2 * elips->radius + elips->rdistance;
// 	b = a * a - elips->rdistance * elips->rdistance;
// 	normale = vsub(p_c, vk_multiple(elips->rotation, ((b / (a * a))) * vscalar_multiple(p_c, elips->rotation)));
// 	return (vnormalize(normale));
// }
//
// double		check_elips_intersection(t_ray *ray, t_elipsoid *elips)
// {
// 	double		a[2];
// 	double		r;
// 	double		disc;
// 	t_vector	o_c;
// 	t_vector	abc;
//
// 	o_c = vsub(ray->o, elips->position);
// 	r = elips->rdistance + 2 * elips->radius;
// 	r *= r;
// 	a[0] = 2 * elips->rdistance * vscalar_multiple(ray->v, elips->rotation);
// 	a[1] = r + 2 * elips->rdistance *
// 		vscalar_multiple(o_c, elips->rotation) - elips->rdistance;
// 	abc.x = 4 * r * vscalar_multiple(ray->v, ray->v) - a[0] * a[0];
// 	abc.y = 4 * r * vscalar_multiple(ray->v, o_c) - a[0] * a[1];
// 	abc.y *= 2;
// 	abc.z = 4 * r * vscalar_multiple(o_c, o_c) - a[1] * a[1];
// 	disc = abc.y * abc.y - 4 * abc.x * abc.z;
// 	if (disc < 0)
// 		return (disc);
// 	disc = get_sqr_solve(abc.x, abc.y, disc);
// 	return (disc);
// }
