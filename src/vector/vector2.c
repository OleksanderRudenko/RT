/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:21:01 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 20:31:32 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vmultiple(t_vector a, t_vector b)
{
	t_vector rez;

	rez.x = (a.z * b.y) - (a.y * b.z);
	rez.y = (a.x * b.z) - (a.z * b.x);
	rez.z = (a.y * b.x) - (a.x * b.y);
	return (rez);
}

t_vector	vsum(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x,
			a.y + b.y,
			a.z + b.z});
}

t_vector	vsub(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x,
			a.y - b.y,
			a.z - b.z});
}

double		vlen(t_vector a)
{
	return (sqrt(vscalar_multiple(a, a)));
}

t_vector	vnormalize(t_vector a)
{
	double	len;

	len = vlen(a);
	return ((t_vector){a.x / len,
			a.y / len,
			a.z / len});
}
