
#include "rt_h.cl"

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
