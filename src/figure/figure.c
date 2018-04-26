/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   figure.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 11:58:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:20:16 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include "rt.h"

t_ray		*ray_init(t_vector origin, t_vector vector)
{
	t_ray *ray;

	ray = (t_ray*)malloc(sizeof(t_ray));
	ray->o = origin;
	ray->v = vector;
	return (ray);
}

t_vector	get_normale(t_vector ray, t_figure *f)
{
	if (f->type == Sphere)
		return (get_sphere_normale(ray, f->figure));
	else if (f->type == InfinitePlane)
		return (get_plane_normale(f->figure));
	else if (f->type == InfiniteCylinder)
		return (get_cylinder_normale(ray, f->figure));
	else if (f->type == InfiniteCone)
		return (get_cone_normale(ray, f->figure));
	return ((t_vector){0, 0, 0});
}

double		check_intersection(t_ray *ray, t_figure *figure)
{
	if (figure->type == Sphere)
		return (check_sphere_intersection(ray, figure->figure));
	else if (figure->type == InfinitePlane)
		return (check_plane_intersection(ray, figure->figure));
	else if (figure->type == InfiniteCylinder)
		return (check_cylinder_intersection(ray, figure->figure));
	else if (figure->type == InfiniteCone)
		return (check_cone_intersection(ray, figure->figure));
	return (-1);
}

int			check_intersections(t_ray *ray, t_figure *figures)
{
	t_figure	*it;
	double		k;

	it = figures;
	while (it != NULL)
	{
		k = check_intersection(ray, it);
		if (k < 1 && k >= 1e-11)
			return (1);
		it = it->next;
	}
	return (0);
}
