/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/01 11:03:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:15:36 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			check_cylinder_intersection(t_ray *ray, t_icylinder *cylinder)
{
	double a;
	double b;
	double c;
	double d;

	a = vscalar_multiple(ray->v, ray->v) -
			pow(vscalar_multiple(ray->v, cylinder->vector), 2);
	b = (vscalar_multiple(ray->v, vsub(ray->o, cylinder->start)) -
			vscalar_multiple(ray->v, cylinder->vector) *
			vscalar_multiple(vsub(ray->o, cylinder->start), cylinder->vector))
			* 2;
	c = vscalar_multiple(vsub(ray->o, cylinder->start),
		vsub(ray->o, cylinder->start)) -
		pow(vscalar_multiple(vsub(ray->o, cylinder->start), cylinder->vector),
				2) -
		pow(cylinder->radius, 2);
	d = pow(b, 2) - 4 * a * c;
	return (get_sqr_solve(a, b, d));
}

t_vector		get_cylinder_normale(t_vector p, t_icylinder *cylinder)
{
	double		m;
	t_vector	res;

	m = vscalar_multiple(vsub(p, cylinder->start), cylinder->vector);
	res = vsum(cylinder->start, vk_multiple(cylinder->vector, m));
	res = vnormalize(vsub(p, res));
	return (res);
}

t_figure		*cylinder_init(t_ray *axis, double radius, int color,
		double reflection)
{
	t_figure	*new_figure;
	t_icylinder	*cylinder;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = InfiniteCylinder;
	cylinder = (t_icylinder*)malloc(sizeof(t_icylinder));
	new_figure->figure = cylinder;
	cylinder->start = axis->o;
	cylinder->vector = vnormalize(axis->v);
	cylinder->radius = radius;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	free(axis);
	return (new_figure);
}
