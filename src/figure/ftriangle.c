/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 22:28:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 22:28:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	count_triangle_normale(t_vector a[3])
{
    t_vector    ab;
    t_vector    bc;

    ab = vsub(a[0], a[1]);
    bc = vsub(a[1], a[2]);
    return (vnormalize(vmultiple(ab, bc)));
}

t_figure	*triangle_init(t_ray *ray, t_vector third_point, int color,
		double reflection)
{
	t_figure	*new_figure;
	t_triangle	*triangle;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = Triangle;
	triangle = (t_triangle*)malloc(sizeof(t_triangle));
	triangle->points[0] = ray->o;
	triangle->points[1] = ray->v;
	triangle->points[2] = third_point;
	triangle->normale = count_triangle_normale(triangle->points);
	free(ray);
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}