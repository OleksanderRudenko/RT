
#include "rt_h.cl"

float3	count_triangle_normale(float3 a)
{
    float3    ab;
    float3    bc;

    ab = subtraction(a.x, a.y);
    bc = subtraction(a.x, a.y);
    return (fast_normalize(mult(ab, bc)));
}
