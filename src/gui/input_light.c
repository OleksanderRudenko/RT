/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 10:45:43 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/10 10:45:49 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		xxx_light(int num, t_view *s)
{
	int		type;

	if (s->flag != 1 || s->rr.fl.b == -1 || num == -1)
		return ;
	type = s->space->cl_lights[s->rr.fl.b].type;
	if (type == LIGHT_TYPE_POINT)
	{
		num == 0 ? s->space->cl_lights[s->rr.fl.b].origin.x = par_input() : 0;
		num == 1 ? s->space->cl_lights[s->rr.fl.b].origin.y = par_input() : 0;
		num == 2 ? s->space->cl_lights[s->rr.fl.b].origin.z = par_input() : 0;
		num == 3 ? s->space->cl_lights[s->rr.fl.b].inten = par_input() : 0;
		init_light_prop(s);
		redraw(s);
	}
	else if (type == LIGHT_TYPE_AMBIENT)
	{
		num == 0 ? s->space->cl_lights[s->rr.fl.b].inten = par_input() : 0;
		init_am_light_prop(s);
		redraw(s);
	}
	else if (type == LIGHT_TYPE_DIRECT)
	{
		ligit_type_prop(s, num);
	}
}

void		ligit_type_prop(t_view *s, int num)
{
	num == 0 ? s->space->cl_lights[s->rr.fl.b].direction.x = par_input() : 0;
	num == 1 ? s->space->cl_lights[s->rr.fl.b].direction.y = par_input() : 0;
	num == 2 ? s->space->cl_lights[s->rr.fl.b].direction.z = par_input() : 0;
	num == 3 ? s->space->cl_lights[s->rr.fl.b].inten = par_input() : 0;
	init_am_light_prop(s);
	redraw(s);
}

SDL_Rect	*select_rect_light(t_view *s)
{
	int		type;

	type = s->space->cl_lights[s->rr.fl.b].type;
	if (type == LIGHT_TYPE_POINT)
		return (s->lp.li_pr_rect);
	else if (type == LIGHT_TYPE_AMBIENT)
		return (s->am.aml_pr_rect);
	else if (type == LIGHT_TYPE_DIRECT)
		return (s->dir.dir_pr_rect);
	return (NULL);
}
