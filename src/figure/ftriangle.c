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

t_vector count_triangle_normale(t_vector a[3])
{
	t_vector ab;
	t_vector bc;

	if (a[0].x == a[1].x && a[2].x == a[1].x)
		a[0].x += 0.00000001;
	if (a[0].y == a[1].y && a[2].y == a[1].y)
		a[0].y += 0.00000001;
	if (a[0].z == a[1].z && a[2].z == a[1].z)
		a[0].z += 0.00000001;
	ab = vsub(a[0], a[1]);
	bc = vsub(a[1], a[2]);
	return (vnormalize(vmultiple(ab, bc)));
}

t_figure *triangle_init(t_vector point[3], int color, double reflection)
{
	t_figure *new_figure;
	t_triangle *triangle;
	// printf("BEFORE PARCE!!\n");

	new_figure = (t_figure *)malloc(sizeof(t_figure));
	new_figure->type = Triangle;
	triangle = (t_triangle *)malloc(sizeof(t_triangle));
	triangle->points[0] = point[0];
	triangle->points[1] = point[1];
	triangle->points[2] = point[2];
	triangle->normale = count_triangle_normale(triangle->points);
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->figure = triangle;
	new_figure->next = NULL;

	// printf("%f, %f, %f-points0\n", triangle->points[0].x, triangle->points[0].y, triangle->points[0].z);
	// printf("%f, %f, %f-points1\n", triangle->points[1].x, triangle->points[1].y, triangle->points[1].z);
	// printf("%f, %f, %f-points2\n", triangle->points[2].x, triangle->points[2].y, triangle->points[2].z);
	// printf("%f, %f, %f-normale\n", triangle->normale.x, triangle->normale.y, triangle->normale.z);
	//
	// printf("AFTER PARCE!!\n");
	return (new_figure);
}
