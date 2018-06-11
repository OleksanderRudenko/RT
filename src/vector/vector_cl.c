/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_cl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:53:39 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 20:29:46 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	vector_cl_init(float x, float y, float z)
{
	cl_float3	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

cl_float3	mult_vec_cl(cl_float3 v, float k)
{
	v.x *= k;
	v.y *= k;
	v.z *= k;
	return (v);
}

cl_float3	sub_vec_cl(cl_float3 v1, cl_float3 v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	v1.z -= v2.z;
	return (v1);
}

cl_float3	sum_vec_cl(cl_float3 v1, cl_float3 v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	v1.z += v2.z;
	return (v1);
}

cl_float3	choose_vec(int id)
{
	if (id == 0)
		return (vector_cl_init(1, 0, 0));
	else if (id == 1)
		return (vector_cl_init(0, 1, 0));
	else if (id == 2)
		return (vector_cl_init(0, 0, 1));
	return (vector_cl_init(0, 0, 0));
}
