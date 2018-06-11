/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 10:19:00 by abutok            #+#    #+#             */
/*   Updated: 2018/06/11 20:30:36 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vector_init(double x, double y, double z)
{
	t_vector	new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

double		vscalar_multiple(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	vk_multiple(t_vector vector, double k)
{
	return ((t_vector){vector.x * k, vector.y * k, vector.z * k});
}

int			vis_equal(t_vector vector1, t_vector vector2)
{
	return (vector1.x == vector2.x &&
			vector1.y == vector2.y &&
			vector1.z == vector2.z);
}

t_vector	get_default_vector(char ch)
{
	if (ch == 'z')
		return ((t_vector){0, 0, 1});
	if (ch == 'y')
		return ((t_vector){0, 1, 0});
	if (ch == 'x')
		return ((t_vector){1, 0, 0});
	return ((t_vector){0, 0, 0});
}
