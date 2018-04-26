/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 15:16:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/16 15:16:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	vmultiple(t_vector a, t_vector b)
{
    return ((t_vector){a.x * b.x, a.y * b.y, a.z * b.z});
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
