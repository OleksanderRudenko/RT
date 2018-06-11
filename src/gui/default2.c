/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:47:55 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/06 11:47:57 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	default_elipsoid_init(t_view *view)
{
	t_figure		*new_figure;
	t_elipsoid		*elips;

	new_figure = (t_figure *)ft_memalloc(sizeof(t_figure));
	new_figure->type = Elipsoid;
	elips = (t_elipsoid *)ft_memalloc(sizeof(t_elipsoid));
	new_figure->figure = elips;
	elips->position = (t_vector){0.0, 0.0, 3.0};
	elips->rotation = vnormalize((t_vector){1.0, 0.0, 0.0});
	elips->radius = 0.5;
	elips->rdistance = 2.0;
	new_figure->color = 0xff;
	new_figure->reflection = 20;
	new_figure->refract = -1;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void	default_paraboloid_init(t_view *view)
{
	t_figure		*new_figure;
	t_parabaloid	*elips;

	new_figure = (t_figure *)ft_memalloc(sizeof(t_figure));
	new_figure->type = Parabaloid;
	elips = (t_parabaloid *)ft_memalloc(sizeof(t_parabaloid));
	new_figure->figure = elips;
	elips->position = (t_vector){0.0, 0.0, 3.0};
	elips->rotation = vnormalize((t_vector){1.0, 0.0, 0.0});
	elips->radius = 0.5;
	new_figure->color = 0xff;
	new_figure->reflection = 20;
	new_figure->refract = -1;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void	default_cube_init(t_view *view)
{
	t_figure		*new_figure;
	t_cube			*cube;

	new_figure = (t_figure *)ft_memalloc(sizeof(t_figure));
	cube = (t_cube *)ft_memalloc(sizeof(t_cube));
	new_figure->type = Cube;
	new_figure->figure = cube;
	cube->position = (t_vector){0.0, 0.0, 0.0};
	cube->rotation = (t_vector){0.0, 0.0, 0.0};
	cube->scale = (t_vector){1.0, 1.0, 1.0};
	count_planes(cube);
	new_figure->color = 0xff;
	new_figure->refract = -1;
	new_figure->reflection = 10;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void	default_quadrate_init(t_view *view)
{
	t_figure		*quadr;
	t_squard		*q;

	quadr = (t_figure *)ft_memalloc(sizeof(t_figure));
	q = (t_squard *)ft_memalloc(sizeof(t_squard));
	q->rotation = (t_vector){0.0, 90.0, 0.0};
	q->position = (t_vector){0.0, 0.0, 0.0};
	q->scale[0] = 1;
	q->scale[1] = 1;
	q = calc_quadrate_params(q);
	quadr->figure = q;
	quadr->color = 0xff;
	quadr->reflection = 50;
	quadr->refract = -1;
	quadr->type = Quadrate;
	quadr->next = NULL;
	default_helper_figures(view, quadr);
}

void	default_triangle_init(t_view *view)
{
	t_figure		*new_figure;
	t_triangle		*triangle;

	new_figure = (t_figure *)ft_memalloc(sizeof(t_figure));
	new_figure->type = Triangle;
	triangle = (t_triangle *)ft_memalloc(sizeof(t_triangle));
	triangle->points[0] = (t_vector){1.0, 0.0, 0.0};
	triangle->points[1] = (t_vector){-1.0, 1.0, 0.0};
	triangle->points[2] = (t_vector){-1.0, 0.0, 0.0};
	triangle->normale = count_triangle_normale(triangle->points);
	new_figure->color = 0xff0000;
	new_figure->reflection = 35;
	new_figure->refract = -1;
	new_figure->figure = triangle;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}
