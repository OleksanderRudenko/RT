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
	num == 0 ? s->space->cl_figures[s->rr.fl.y].center.x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].center.y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].center.z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	num == 5 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
}

void	save_triangle(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].t_points[0].x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].t_points[0].y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].t_points[0].z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].t_points[1].x = par_input() : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].t_points[1].y = par_input() : 0;
	num == 5 ? s->space->cl_figures[s->rr.fl.y].t_points[1].z = par_input() : 0;
	num == 6 ? s->space->cl_figures[s->rr.fl.y].t_points[2].x = par_input() : 0;
	num == 7 ? s->space->cl_figures[s->rr.fl.y].t_points[2].y = par_input() : 0;
	num == 8 ? s->space->cl_figures[s->rr.fl.y].t_points[2].z = par_input() : 0;
	num == 9 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	num == 10 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	// NORMALE CALC
}

void	save_cylinder(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].start.x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].start.y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].start.z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	num == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
	num == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
	num == 7 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
	num == 8 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;

}

void	save_plane(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].normale.x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].normale.y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].normale.z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	num == 4 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	num == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	num == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	num == 7 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
}

void	save_cube(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;

	num == 0? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), num) : 0;
	num == 1? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), num) : 0;
	num == 2? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), num) : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	num == 4 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	num == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	num == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	num == 7 ? s->space->cl_figures[s->rr.fl.y].scale.x = par_input() : 0;
	num == 8 ? s->space->cl_figures[s->rr.fl.y].scale.y = par_input() : 0;
	num == 9 ? s->space->cl_figures[s->rr.fl.y].scale.z = par_input() : 0;
	num == 10 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
}
