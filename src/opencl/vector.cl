
#include "rt_h.cl"

// float3	vector_init(float x, float y, float z)
// {
// 	float3	new_vector;

// 	new_vector.x = x;
// 	new_vector.y = y;
// 	new_vector.z = z;
// 	return (new_vector);
// }

// float		vscalar_multiple(t_vector a, t_vector b)
// {
// 	return (a.x * b.x + a.y * b.y + a.z * b.z);
// }

float3		k_multiply(float3 vector, float k)
{
	return ((float3)(vector.x * k, vector.y * k, vector.z * k));
}

// int			is_equal(float3 vector1, float3 vector2)
// {
// 	return (vector1.x == vector2.x &&
// 			vector1.y == vector2.y &&
// 			vector1.z == vector2.z);
// }


float3 	sum(float3 a, float3 b)
{
	return ((float3)(a.x + b.x, a.y + b.y, a.z + b.z));
}

float3	subtraction(float3 a, float3 b)
{
	return ((float3)(a.x - b.x, a.y - b.y, a.z - b.z));
}

//fast_length
// float		vlen(t_vector a)
// {
// 	return (sqrt(vscalar_multiple(a, a)));
// }

//cross
float3	mult(float3 a, float3 b)
{
    return ((float3){a.x * b.x, a.y * b.y, a.z * b.z});
}

//fast_normalize
// t_vector	vnormalize(t_vector a)
// {
// 	float	len;

// 	len = vlen(a);
// 	return ((t_vector){a.x / len,
// 			a.y / len,
// 			a.z / len});
// }
