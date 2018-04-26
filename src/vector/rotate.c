/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/23 12:32:00 by abutok            #+#    #+#             */
/*   Updated: 2018/02/23 15:28:09 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_x(t_vector *ps, double l)
{
	double ny;
	double nz;

	ny = ps->y * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->y * sin(l);
	ps->y = ny;
	ps->z = nz;
}

void	rotate_y(t_vector *ps, double l)
{
	double nx;
	double nz;

	nx = ps->x * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->z = nz;
}

void	rotate_z(t_vector *ps, double l)
{
	double ny;
	double nx;

	nx = ps->x * cos(l) + ps->y * sin(l);
	ny = ps->y * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->y = ny;
}
