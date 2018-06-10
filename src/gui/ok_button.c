/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ok_button.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 15:00:35 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/15 15:00:38 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_read_prop	*read_apply_prop(void)
{
	static t_read_prop	*rd = NULL;
	static char			one = 0;

	if (one)
		return (rd);
	one++;
	rd = (t_read_prop*)malloc(sizeof(t_read_prop) * 9);
	rd[Sphere] = &save_sphere;
	rd[Triangle] = &save_triangle;
	rd[InfiniteCylinder] = &save_cylinder;
	rd[InfinitePlane] = &save_plane;
	rd[Cube] = &save_cube;
	rd[InfiniteCone] = &save_cone;
	rd[Parabaloid] = &save_parab;
	rd[Quadrate] = &save_quadr;
	rd[Elipsoid] = &save_elips;
	return (rd);
}

void		xxx(int num, t_view *s)
{
	t_read_prop			*rd;
	int					type;

	if (num == -1)
		return ;
	type = s->space->cl_figures[s->rr.fl.y].type;
	rd = read_apply_prop();
	rd[type](s, num);
	s->space->cl_figures[(int)s->rr.fl.y].color =
	color_unite(s->sl[0]->clr.red, s->sl[1]->clr.green, s->sl[2]->clr.blue);
	get_init_prop(s);
}
