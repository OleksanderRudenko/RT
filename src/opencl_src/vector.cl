
#include "rt_h.cl"

float q_rsqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( long * ) &y;                       // evil floating point bit level hacking
	i  = 0x5f3759df - ( i >> 1 );               // what the fuck?
	y  = * ( float *) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 1st iteration
	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed
	// y  = y * ( threehalfs - ( x2 * y * y ) );   // 3nd iteration, this can be removed
	y = (y < 0) ? (-1 / y) : (1 / y);
	return (y);
}

float			dot_my(float3 v1, float3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float		pow_my(float d, char del)
{
	if (del == 2)
		return (d * d);
	return (d);
}

float		len_my(float3 v)
{
	float scal;

	scal = dot_my(v, v);
	return (q_rsqrt(scal < 0 ? -scal : scal));
}

float3		k_multiply(float3 vector, float k)
{
	return ((float3)(vector.x * k, vector.y * k, vector.z * k));
}

int			is_equal(float3 vector1, float3 vector2)
{
	return (vector1.x == vector2.x &&
			vector1.y == vector2.y &&
			vector1.z == vector2.z);
}

float3 	sum(float3 a, float3 b)
{
	return ((float3)(a.x + b.x, a.y + b.y, a.z + b.z));
}

float3	subtraction(float3 a, float3 b)
{
	return ((float3)(a.x - b.x, a.y - b.y, a.z - b.z));
}

float3	mult(float3 a, float3 b)
{
    return ((float3){a.x * b.x, a.y * b.y, a.z * b.z});
}

float3  cross_vec(float3 a, float3 b)
{
  float3 rez;

  rez.x = (a.z * b.y) - (a.y * b.z);
  rez.y = (a.x * b.z) - (a.z * b.x);
  rez.z = (a.y * b.x) - (a.x * b.y);
  return (rez);
}

float3	vnormalize(float3 v)
{
	float	len;

	len = len_my(v);
	return (v / len);
}
