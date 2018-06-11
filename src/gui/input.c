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

void	save_sphere(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].center.x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].center.y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].center.z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	n == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 5 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 6 ? s->space->cl_figures[s->rr.fl.y].texture = texture_val() : 0;
	n == 7 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}

void	save_triangle(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].t_points[0].x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].t_points[0].y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].t_points[0].z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].t_points[1].x = par_input() : 0;
	n == 4 ? s->space->cl_figures[s->rr.fl.y].t_points[1].y = par_input() : 0;
	n == 5 ? s->space->cl_figures[s->rr.fl.y].t_points[1].z = par_input() : 0;
	n == 6 ? s->space->cl_figures[s->rr.fl.y].t_points[2].x = par_input() : 0;
	n == 7 ? s->space->cl_figures[s->rr.fl.y].t_points[2].y = par_input() : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].t_points[2].z = par_input() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 10 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	redraw(s);
}

void	save_cylinder(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].start.x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].start.y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].start.z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	n == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 7 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 5) : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].texture = texture_val() : 0;
	n == 10 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}

void	save_plane(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? s->space->cl_figures[s->rr.fl.y].point.x = par_input() : 0;
	n == 1 ? s->space->cl_figures[s->rr.fl.y].point.y = par_input() : 0;
	n == 2 ? s->space->cl_figures[s->rr.fl.y].point.z = par_input() : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 4 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 7 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].texture = texture_val() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}

void	save_cube(t_view *s, int n)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	n == 0 ? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), n) : 0;
	n == 1 ? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), n) : 0;
	n == 2 ? change_pos(&s->space->cl_figures[s->rr.fl.y], par_input(), n) : 0;
	n == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
	n == 4 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 5 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 6 ? rotate_figures(&s->space->cl_figures[s->rr.fl.y],
		par_input(), n - 4) : 0;
	n == 7 ? s->space->cl_figures[s->rr.fl.y].scale.x = par_input() : 0;
	n == 8 ? s->space->cl_figures[s->rr.fl.y].scale.y = par_input() : 0;
	n == 9 ? s->space->cl_figures[s->rr.fl.y].scale.z = par_input() : 0;
	n == 10 ? s->space->cl_figures[s->rr.fl.y].mirror = mirror_val() : 0;
	n == 11 ? s->space->cl_figures[s->rr.fl.y].texture = texture_val() : 0;
	n == 12 ? s->space->cl_figures[s->rr.fl.y].refract = refract_val() : 0;
	redraw(s);
}
