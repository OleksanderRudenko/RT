/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_by_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 15:55:26 by ataranov          #+#    #+#             */
/*   Updated: 2018/05/05 16:04:57 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	rotate_p_x(t_vector *ps, t_vector *nul_dot, double l)
{
	double ny;
	double nz;

	ny = ps->y * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->y * sin(l);
	ps->y = ny;
	ps->z = nz;
}

void	rotate_p_y(t_vector *ps, t_vector *nul_dot, double l)
{
	double nx;
	double nz;

	nx = ps->x * cos(l) + ps->z * sin(l);
	nz = ps->z * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->z = nz;
}

void	rotate_p_z(t_vector *ps, t_vector *nul_dot, double l)
{
	double ny;
	double nx;

	nx = ps->x * cos(l) + ps->y * sin(l);
	ny = ps->y * cos(l) - ps->x * sin(l);
	ps->x = nx;
	ps->y = ny;
}
