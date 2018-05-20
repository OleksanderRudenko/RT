/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 19:57:34 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 19:57:36 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void 		copy_plane(t_cl_figure *figure, t_figure *tmp)
{
	figure->normale = copy_vector(((t_iplane*)tmp->figure)->normale);
	figure->point = copy_vector(((t_iplane*)tmp->figure)->point);
}

void 		copy_sphere(t_cl_figure *figure, t_figure *tmp)
{
	figure->center = copy_vector(((t_sphere*)tmp->figure)->center);
	figure->radius = ((t_sphere*)tmp->figure)->radius;
}

void 		copy_cylinder(t_cl_figure *figure, t_figure *tmp)
{
	figure->start = copy_vector(((t_icylinder*)tmp->figure)->start);
	figure->vector = copy_vector(((t_icylinder*)tmp->figure)->vector);
	figure->radius = ((t_icylinder*)tmp->figure)->radius;
}

void 		copy_cone(t_cl_figure *figure, t_figure *tmp)
{
	figure->vertex = copy_vector(((t_icone*)tmp->figure)->vertex);
	figure->vector = copy_vector(((t_icone*)tmp->figure)->vector);
	figure->radius = ((t_icone*)tmp->figure)->radius;
}

void 		copy_cube(t_cl_figure *figure, t_figure *tmp)
{
	int 		j;
	int 		i;

	j = -1;
	i = 0;
	while (++j < 24)
	{
		figure->c_points[j] =
			copy_vector(((t_cube*)tmp->figure)->planes[j / 4].points[i++]);
		i = (i == 4) ? (i = 0) : i;
	}
	i = -1;
	while (++i < 4)
		figure->c_normale[i] =
			copy_vector(((t_cube*)tmp->figure)->planes[i].normale);
	figure->position = copy_vector(((t_cube*)tmp->figure)->position);
	figure->rotation = copy_vector(((t_cube*)tmp->figure)->rotation);
	figure->scale = copy_vector(((t_cube*)tmp->figure)->scale);
}
