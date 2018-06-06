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
	t_figure *new_figure;
	t_elipsoid *elips;

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
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void	default_paraboloid_init(t_view *view)
{
	t_figure *new_figure;
	t_parabaloid *elips;

	new_figure = (t_figure *)ft_memalloc(sizeof(t_figure));
	new_figure->type = Parabaloid;
	elips = (t_parabaloid *)ft_memalloc(sizeof(t_parabaloid));
	new_figure->figure = elips;
	elips->position = (t_vector){0.0, 0.0, 3.0};
	elips->rotation = vnormalize((t_vector){1.0, 0.0, 0.0});
	elips->radius = 0.5;
	new_figure->color = 0xff;
	new_figure->reflection = 20;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}
