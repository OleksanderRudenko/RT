/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 15:06:20 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/22 15:06:24 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	save_sphere(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].center.x = par_input(s) : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].center.y = par_input(s) : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].center.z = par_input(s) : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input(s) : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input(s) : 0;
}

void	save_triangle(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].normale.x = par_input(s) : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].normale.y = par_input(s) : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].normale.z = par_input(s) : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input(s) : 0;
}

void	save_cylinder(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].start.x = par_input(s) : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].start.y = par_input(s) : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].start.z = par_input(s) : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input(s) : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input(s) : 0;
	num == 5 ? s->space->cl_figures[s->rr.fl.y].vector.x = par_input(s) : 0;
	num == 6 ? s->space->cl_figures[s->rr.fl.y].vector.y = par_input(s) : 0;
	num == 7 ? s->space->cl_figures[s->rr.fl.y].vector.z = par_input(s) : 0;

	// num == 5? rotate_figure(&s->space->cl_figures[s->rr.fl.y], par_input(s), num - 5) : 0;

}

void	save_plane(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].normale.x = par_input(s) : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].normale.y = par_input(s) : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].normale.z = par_input(s) : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input(s) : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].point.x = par_input(s) : 0;
	num == 5 ? s->space->cl_figures[s->rr.fl.y].point.y = par_input(s) : 0;
	num == 6 ? s->space->cl_figures[s->rr.fl.y].point.z = par_input(s) : 0;
}