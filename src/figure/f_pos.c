/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_pos.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:08:18 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/10 14:59:58 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	new_normal_triangle(t_cl_figure *figure)
{
	t_vector	dots[3];
	t_vector	normale;
	int			i;

	i = 0;
	while (i < 3)
	{
		dots[i].x = figure->t_points[i].x;
		dots[i].y = figure->t_points[i].y;
		dots[i].z = figure->t_points[i].z;
	}
	normale = count_triangle_normale(dots);
	figure->normale = copy_vector(normale);
}

void	change_pos_cube(t_cl_figure *figure, cl_float3 new_value)
{
	int			i;

	i = 0;
	while (i < 24)
	{
		figure->c_points[i] = sum_vec_cl(new_value, figure->c_points[i]);
		i++;
	}
	figure->position = sum_vec_cl(new_value, figure->position);
}

void	change_pos_sq(t_cl_figure *figure, cl_float3 new_value)
{
	int			i;

	i = 0;
	while (i < 4)
	{
		figure->q_points[i] = sum_vec_cl(new_value, figure->q_points[i]);
		i++;
	}
	figure->position = sum_vec_cl(new_value, figure->position);
}

void	change_pos(t_cl_figure *figure, float new_value, int id)
{
	cl_float3 this_def;

	this_def = mult_vec_cl(choose_vec(id), new_value);
	if (figure->type == Cube)
		change_pos_cube(figure, this_def);
	else if (figure->type == Quadrate)
		change_pos_sq(figure, this_def);
}
