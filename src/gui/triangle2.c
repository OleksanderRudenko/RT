/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 18:13:08 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/10 18:13:10 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	triangle_init_prop2(t_view *s)
{
	s->tri.tri_prop[5] = tf(s,
		s->space->cl_figures[s->rr.fl.y].t_points[1].z, 2, 32);
	s->tri.tri_prop[6] = tf(s,
		s->space->cl_figures[s->rr.fl.y].t_points[2].x, 2, 32);
	s->tri.tri_prop[7] = tf(s,
		s->space->cl_figures[s->rr.fl.y].t_points[2].y, 2, 32);
	s->tri.tri_prop[8] = tf(s,
		s->space->cl_figures[s->rr.fl.y].t_points[2].z, 2, 32);
	s->tri.tri_prop[9] = tf(s,
		s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->tri.tri_prop[10] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	s->tri.tri_prop[11] = tf(s,
		s->space->cl_figures[s->rr.fl.y].refract, 2, 32);
}

void	triangle_prop3(t_view *s)
{
	s->tri.tri_rect[10] = make_rect(10, 700, 60, 32);
	s->tri.tri_tex[10] = create_text(s, "Mirror", 2, 32);
	s->tri.tri_pr_rect[10] = make_rect(120, 700, 60, 32);
	s->tri.tri_prop[10] = tf(s, 0, 2, 32);
	s->tri.tri_rect[11] = make_rect(10, 750, 90, 32);
	s->tri.tri_tex[11] = create_text(s, "Refraction", 2, 32);
	s->tri.tri_pr_rect[11] = make_rect(120, 750, 60, 32);
	s->tri.tri_prop[11] = tf(s, 0, 2, 32);
}
