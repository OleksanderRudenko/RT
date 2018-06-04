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

void	save_cone(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].vertex.x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].vertex.y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].vertex.z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;

  num == 4? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
  num == 5? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
  num == 6? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 4) : 0;
	// num == 4 ? s->space->cl_figures[s->rr.fl.y].vector.x = par_input() : 0;
	// num == 5 ? s->space->cl_figures[s->rr.fl.y].vector.y = par_input() : 0;
	// num == 6 ? s->space->cl_figures[s->rr.fl.y].vector.z = par_input() : 0;
	num == 7 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
}

void	save_parab(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].position.x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].position.y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].position.z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
  num == 5? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
  num == 6? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
  num == 7? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
	// num == 5 ? s->space->cl_figures[s->rr.fl.y].rotation.x = par_input() : 0;
	// num == 6 ? s->space->cl_figures[s->rr.fl.y].rotation.y = par_input() : 0;
	// num == 7 ? s->space->cl_figures[s->rr.fl.y].rotation.z = par_input() : 0;
}

void	save_quadr(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	// num == 0 ? s->space->cl_figures[s->rr.fl.y].normale.x = par_input() : 0;
	// num == 1 ? s->space->cl_figures[s->rr.fl.y].normale.y = par_input() : 0;
	// num == 2 ? s->space->cl_figures[s->rr.fl.y].normale.z = par_input() : 0;
  num == 0? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num) : 0;
  num == 1? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num) : 0;
  num == 2? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num) : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;
}

void	save_elips(t_view *s, int num)
{
	if (s->flag != 0 || s->rr.fl.y == -1)
		return ;
	num == 0 ? s->space->cl_figures[s->rr.fl.y].position.x = par_input() : 0;
	num == 1 ? s->space->cl_figures[s->rr.fl.y].position.y = par_input() : 0;
	num == 2 ? s->space->cl_figures[s->rr.fl.y].position.z = par_input() : 0;
	num == 3 ? s->space->cl_figures[s->rr.fl.y].radius = par_input() : 0;
	num == 4 ? s->space->cl_figures[s->rr.fl.y].reflection = par_input() : 0;

  num == 5? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
  num == 6? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
  num == 7? rotate_figures(&s->space->cl_figures[s->rr.fl.y], par_input(), num - 5) : 0;
	// num == 5 ? s->space->cl_figures[s->rr.fl.y].rotation.x = par_input() : 0;
	// num == 6 ? s->space->cl_figures[s->rr.fl.y].rotation.y = par_input() : 0;
	// num == 7 ? s->space->cl_figures[s->rr.fl.y].rotation.z = par_input() : 0;
	num == 8 ? s->space->cl_figures[s->rr.fl.y].rdistance = par_input() : 0;
}
