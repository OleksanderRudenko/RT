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

void		object_default_init(t_view *s)
{
	s->l_obj.def_rect = make_rect(10, 0, 250, 90);
	s->l_obj.def_tex = get_tex("img/sel.png", s->rr.rend[2]);
}

void		print_default_text(t_view *s)
{
	SDL_RenderClear(s->rr.rend[2]);
	SDL_RenderCopy(s->rr.rend[2], s->l_obj.def_tex, NULL, &s->l_obj.def_rect);
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void		what_to_print(t_view *s)
{
	if (s->rr.fl.y == -1 && s->rr.fl.b == -1)
	{
		print_default_text(s);
		s->rr.fl.a = -1;
	}
	if (s->rr.fl.y != -1 && s->flag == 0)
		detect_type_of_figure(s);
	if (s->rr.fl.b != -1 && s->flag == 1)
	{
		if (s->space->cl_lights[(s->rr.fl.b)].type == LIGHT_TYPE_POINT)
		{
			init_light_prop(s);
			print_light_prop(s);
		}
		if (s->space->cl_lights[(s->rr.fl.b)].type == LIGHT_TYPE_AMBIENT)
		{
			init_am_light_prop(s);
			print_am_light_prop(s);
		}
		if (s->space->cl_lights[(s->rr.fl.b)].type == LIGHT_TYPE_DIRECT)
		{
			init_dir_light_prop(s);
			print_dir_light_prop(s);
		}
	}
}

void		detect_type_of_figure(t_view *s)
{
	static int	rep = -1;

	rep == s->rr.fl.y ? 0 : get_init_prop(s);
	get_properties(s);
	rep = s->rr.fl.y;
}

t_figure	*detect_figure(t_view *s)
{
	t_figure	*fig;
	int			i;

	fig = s->space->figures;
	if (fig == NULL)
		return (NULL);
	i = -1;
	while (++i < s->rr.fl.y)
		fig = fig->next;
	return (fig);
}
