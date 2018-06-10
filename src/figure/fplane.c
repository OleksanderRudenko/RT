/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fplane.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 10:54:58 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/10 13:17:54 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			check_plane_intersection(t_ray *ray, t_iplane *plane)
{
	double r_v;

	r_v = -1;
	if (plane->normale.x != 0 || plane->normale.y != 0 || plane->normale.z != 0)
		r_v = vscalar_multiple(plane->normale, vsub(plane->point, ray->o)) /
				vscalar_multiple(plane->normale, ray->v);
	return (r_v);
}

t_vector		get_plane_normale(t_iplane *plane)
{
	return (plane->normale);
}

t_figure		*plane_init(t_vector normale, t_vector point, int color,
		double reflection)
{
	t_figure *new_figure;
	t_iplane *plane;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = InfinitePlane;
	plane = (t_iplane*)ft_memalloc(sizeof(t_iplane));
	new_figure->figure = plane;
	plane->normale = vnormalize(normale);
	plane->point = point;
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
