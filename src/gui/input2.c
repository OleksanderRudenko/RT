/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:06:28 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/22 15:06:30 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	save_cone(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].vertex.x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].vertex.y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].vertex.z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 4 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 7 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].texture = texture_val() : 0;
	n == 10 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}

void	save_parab(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].position.x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].position.y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].position.z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	n == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 7 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}

void	save_quadr(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), n) : 0;
	n == 1 ? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), n) : 0;
	n == 2 ? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), n) : 0;
	n == 3 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 3) : 0;
	n == 4 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 3) : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 3) : 0;
	n == 6 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 7 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].texture = texture_val() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}

void	save_elips(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].position.x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].position.y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].position.z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	n == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 7 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].rdistance = par_input() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 10 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}
