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

t_figure	*triangle_init(t_vector point[3], int color, double reflection)
{
	t_figure	*new_figure;
	t_triangle	*triangle;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = Triangle;
	triangle = (t_triangle*)malloc(sizeof(t_triangle));
	triangle->points[0] = point[0];
	triangle->points[1] = point[1];
	triangle->points[2] = point[2];
	triangle->normale = count_triangle_normale(triangle->points);
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->figure = triangle;
	new_figure->next = NULL;
	return (new_figure);
}
