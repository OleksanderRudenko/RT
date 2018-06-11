/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:27:55 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 20:28:59 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_p_cl_z(cl_float3 *dot_rot, cl_float3 *dot_null, float angle)
{
	cl_float3	dot_buf;

	dot_buf.z = dot_rot->z;
	dot_buf.x = (dot_null->x + ((dot_rot->x - dot_null->x) * cos((angle))) -
		((dot_rot->y - dot_null->y) * sin((angle))));
	dot_buf.y = (dot_null->y + ((dot_rot->y - dot_null->y) * cos((angle))) +
		((dot_rot->x - dot_null->x) * sin((angle))));
	*dot_rot = dot_buf;
}

void	rotate_p_cl_x(cl_float3 *dot_rot, cl_float3 *dot_null, float angle)
{
	cl_float3	dot_buf;

	dot_buf.x = dot_rot->x;
	dot_buf.y = (dot_null->y + ((dot_rot->y - dot_null->y) * cos((angle))) -
		((dot_rot->z - dot_null->z) * sin((angle))));
	dot_buf.z = (dot_null->z + ((dot_rot->z - dot_null->z) * cos((angle))) +
		((dot_rot->y - dot_null->y) * sin((angle))));
	*dot_rot = dot_buf;
}

void	rotate_p_cl_y(cl_float3 *dot_rot, cl_float3 *dot_null, float angle)
{
	cl_float3	dot_buf;

	dot_buf.y = dot_rot->y;
	dot_buf.z = (dot_null->z + ((dot_rot->z - dot_null->z) * cos((angle))) -
		((dot_rot->x - dot_null->x) * sin((angle))));
	dot_buf.x = (dot_null->x + ((dot_rot->x - dot_null->x) * cos((angle))) +
		((dot_rot->z - dot_null->z) * sin((angle))));
	*dot_rot = dot_buf;
}
