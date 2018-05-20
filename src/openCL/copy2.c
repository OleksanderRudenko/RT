/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 19:57:40 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 19:57:41 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 		copy_triangle(t_cl_figure *figure, t_figure *tmp)
{
	int i;

	i = -1;
	while (++i < 3)
		figure->t_points[i] =
						copy_vector(((t_triangle*)tmp->figure)->points[i]);
	figure->normale = copy_vector(((t_triangle*)tmp->figure)->normale);
}

void 		copy_quadrate(t_cl_figure *figure, t_figure *tmp)
{
	int i;

	i = -1;
	while (++i < 4)
		figure->q_points[i] =
						copy_vector(((t_squard*)tmp->figure)->points[i]);
	figure->normale = copy_vector(((t_squard*)tmp->figure)->normale);
}

void 		copy_elipsoid(t_cl_figure *figure, t_figure *tmp)
{
	figure->position = copy_vector(((t_elipsoid*)tmp->figure)->position);
	figure->rotation = copy_vector(((t_elipsoid*)tmp->figure)->rotation);
	figure->radius = ((t_elipsoid*)tmp->figure)->radius;
	figure->rdistance = ((t_elipsoid*)tmp->figure)->rdistance;
}

void 		copy_paraboloid(t_cl_figure *figure, t_figure *tmp)
{
	figure->position = copy_vector(((t_parabaloid*)tmp->figure)->position);
	figure->rotation = copy_vector(((t_parabaloid*)tmp->figure)->rotation);
	figure->radius = ((t_parabaloid*)tmp->figure)->radius;
}

void 		copy_tor(t_cl_figure *figure, t_figure *tmp)
{
	figure->radius_s = ((t_itor*)tmp->figure)->r;
	figure->radius_b = ((t_itor*)tmp->figure)->r_b;
	figure->center = copy_vector(((t_itor*)tmp->figure)->center);
}
