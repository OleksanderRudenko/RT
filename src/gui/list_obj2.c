/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_obj2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:37:19 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/02 12:37:21 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
// #define NUM_SPH_PROP 3

void			object_default_init(t_view *s)
{
	s->l_obj.def_rect = make_rect(20, 10, 250, 40);
	s->l_obj.def_tex = create_text(s, "Please, select figure", 2, 20);
}

void			print_default_text(t_view *s)
{
	if (s->rr.fl.y == -1)
	{
		SDL_RenderClear(s->rr.rend[2]);
		SDL_RenderCopy(s->rr.rend[2], s->l_obj.def_tex, NULL, &s->l_obj.def_rect);
		SDL_RenderPresent(s->rr.rend[2]);
	}
}

void			what_to_print(t_view *s)
{
	s->rr.fl.y == -1 ? print_default_text(s) : detect_type_of_figure(s);
}

void	detect_type_of_figure(t_view *s)
{
	t_figure	*fig;
	static int	rep = 0;

	fig = detect_figure(s);
	if (fig->type == Sphere)
	{
		rep == s->rr.fl.y ? 0 : init_sphere_prop(s, fig->figure, fig);
		print_prop(s);
	}
	// if (fig->type == InfiniteCylinder)
	// {
	// 	rep == s->rr.fl.y ? 0 : init_incyl_prop(s, fig->figure, fig);
	// 	print_incyl_prop(s);
	// }
	rep = s->rr.fl.y;
}

