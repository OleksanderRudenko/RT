/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:28:05 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 20:31:42 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_cl_x(cl_float3 *ps, float l)
{
	float ny;
	float nz;

	ny = ps->y * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->y * sin(l);
	ps->y = ny;
	ps->z = nz;
}

void	rotate_cl_y(cl_float3 *ps, float l)
{
	float nx;
	float nz;

	nx = ps->x * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->z = nz;
}

void	rotate_cl_z(cl_float3 *ps, float l)
{
	float ny;
	float nx;

	nx = ps->x * cos(l) + ps->y * sin(l);
	ny = ps->y * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->y = ny;
}
