/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fsphere.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 13:19:44 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/10 13:19:51 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			get_sqr_solve(double a, double b, double d)
{
	double x1;
	double x2;

	if (d == 0)
		return (-b / 2 * a);
	x1 = (-b + sqrt(d)) / (2 * a);
	x2 = (-b - sqrt(d)) / (2 * a);
	if (x1 <= 1e-11)
		return (x2);
	if (x2 <= 1e-11)
		return (x1);
	return (x1 <= x2 ? x1 : x2);
}

double			check_sphere_intersection(t_ray *ray, t_sphere *figure)
{
	t_vector	buf;
	double		a;
	double		b;
	double		c;
	double		d;

	a = vscalar_multiple(ray->v, ray->v);
	buf = vsub(ray->o, figure->center);
	b = 2 * (vscalar_multiple(buf, ray->v));
	c = vscalar_multiple(buf, buf) - (figure->radius * figure->radius);
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
		return (-1);
	else
		return (get_sqr_solve(a, b, d));
}

t_vector		get_sphere_normale(t_vector p, t_sphere *f)
{
	return (vnormalize(vsub(p, f->center)));
}

t_figure		*sphere_init(t_vector center, double r, int color,
		double reflection)
{
	t_figure *new_figure;
	t_sphere *sphere;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = Sphere;
	sphere = (t_sphere*)ft_memalloc(sizeof(t_sphere));
	new_figure->figure = sphere;
	sphere->center = center;
	sphere->radius = r;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
