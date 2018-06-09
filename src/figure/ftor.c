/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 16:25:29 by vvinogra          #+#    #+#             */
/*   Updated: 2018/06/09 01:41:16 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double			find_true_root(double *arr)
{
	int		i;
	double	ret;

	i = 0;
	while (i < 4)
	{
		if (arr[i] == arr[i])
			ret = arr[i];
	}
	i = 0;
	while (i < 4)
	{
		if (arr[i] == arr[i] && arr[i] > 0 && arr[i] < ret)
			ret = arr[i];
	}
	free(arr);
	return (ret);
}

double			check_tor_intersection(t_ray *ray, t_itor *tor)
{
	double		vars[5];
	double		*ret;
	t_vector	buf;

	buf = vsub(ray->o, tor->center);
	vars[0] = pow(vscalar_multiple(ray->v, ray->v), 2);
	vars[1] = 2 * vscalar_multiple(ray->v, ray->v)
		* 2 * vscalar_multiple(ray->v, buf);
	vars[2] = 2 * vscalar_multiple(ray->v, ray->v) * (vscalar_multiple(buf, buf)
		+ pow(tor->r_b, 2) - pow(tor->r, 2)) +
			pow(2 * vscalar_multiple(ray->v, buf), 2) - 4 * pow(tor->r_b, 2) *
				(ray->v.x * ray->v.x + ray->v.y * ray->v.y);
	vars[3] = 2 * 2 * vscalar_multiple(ray->v, buf) *
	(vscalar_multiple(buf, buf) + pow(tor->r_b, 2) - pow(tor->r, 2)) -
			8 * pow(tor->r_b, 2) * (ray->v.x * buf.x + ray->v.y * buf.y);
	vars[4] = pow(vscalar_multiple(buf, buf) +
		(tor->r_b * tor->r_b - tor->r * tor->r), 2) - 4 * pow(tor->r_b, 2) *
			(buf.x * buf.x + buf.y * buf.y);
	ret = quadric_solver(&vars);
	return (find_true_root(ret));
}

t_figure		*tor_init(t_vector center, const double radiuses[2], int color,
		double reflection)
{
	t_figure	*new_figure;
	t_itor		*tor;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	new_figure->type = Tor;
	tor = (t_itor*)malloc(sizeof(t_itor));
	new_figure->figure = tor;
	tor->r = radiuses[0];
	tor->r_b = radiuses[1];
	new_figure->color = color;
	new_figure->reflection = reflection;
	tor->center = center;
	// tor->vector = vnormalize(axis->v);
	// free(axis);
	new_figure->next = NULL;
	return (new_figure);
}
