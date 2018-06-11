/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_figure.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 12:09:05 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 21:16:14 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_func	*g_rot_arr[3] =
{
	rotate_p_cl_x,
	rotate_p_cl_y,
	rotate_p_cl_z
};

static	cl_float3	null_vec_cl(void)
{
	cl_float3	null_vec;

	null_vec.x = 0;
	null_vec.y = 0;
	null_vec.z = 0;
	return (null_vec);
}

void				calc_rot_sq(t_cl_figure *figure,
	float angle, t_func *rot_func)
{
	cl_float3	null_vec;

	null_vec = null_vec_cl();
	rot_func(&(figure->q_points[0]), &(figure->position), angle);
	rot_func(&(figure->q_points[1]), &(figure->position), angle);
	rot_func(&(figure->q_points[2]), &(figure->position), angle);
	rot_func(&(figure->q_points[3]), &(figure->position), angle);
	rot_func(&(figure->normale), &null_vec, angle);
}

void				calc_rot_cube(t_cl_figure *figure,
	float angle, t_func *rot_func)
{
	int			i;
	cl_float3	null_vec;

	null_vec = null_vec_cl();
	i = 0;
	while (i < 6)
	{
		rot_func(&(figure->c_points[i * 4]), &(figure->position), angle);
		rot_func(&(figure->c_points[i * 4 + 1]), &(figure->position), angle);
		rot_func(&(figure->c_points[i * 4 + 2]), &(figure->position), angle);
		rot_func(&(figure->c_points[i * 4 + 3]), &(figure->position), angle);
		rot_func(&(figure->c_normale[i]), &null_vec, angle);
		i++;
	}
}

void				rots(t_cl_figure *figure, float angle, t_func *rot_func)
{
	cl_float3 null_vec;

	null_vec = null_vec_cl();
	if (figure->type == InfiniteCone ||
			figure->type == InfiniteCylinder ||
				figure->type == InfiniteCone)
		rot_func(&(figure->vector), &null_vec, angle);
	else if (figure->type == Elipsoid || figure->type == Parabaloid)
		rot_func(&(figure->rotation), &null_vec, angle);
	else if (figure->type == InfinitePlane)
		rot_func(&(figure->normale), &null_vec, angle);
	else if (figure->type == Cube)
		calc_rot_cube(figure, angle, rot_func);
	else if (figure->type == Quadrate)
		calc_rot_sq(figure, angle, rot_func);
}

void				rotate_figures(t_cl_figure *figure, float angle, int id)
{
	if (id == 0 || id == 1 || id == 2)
	{
		rots(figure, angle * 3.14 / 180, g_rot_arr[id]);
	}
	else
	{
		ft_putstr("ERROR: file rotate_figures.c; id = ");
		ft_putnbr(id);
		ft_putchar('\n');
	}
}
