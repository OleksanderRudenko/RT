/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 13:46:07 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 13:46:08 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pr	*get_print(void)
{
	t_pr	*luck;

	luck = (t_pr*)malloc(sizeof(t_pr) * 10);
	luck[Sphere] = &print_sph_prop;
	luck[InfiniteCylinder] = &print_ic_prop;
	luck[InfinitePlane] = &print_pl_prop;
	luck[Triangle] = &print_triangle_prop;
	luck[InfiniteCone] = &print_cone_prop;
	luck[Cube] = &print_cube_prop;
	luck[Quadrate] = &print_quadraate_prop;
	luck[Elipsoid] = &print_elips_prop;
	luck[Parabaloid] = &print_parab_prop;
	// luck[Tor] = &; ????????????
	return (luck);
}

void	get_properties(t_view *s)
{
	t_pr *func;
	int type;
	
	type = s->space->cl_figures[s->rr.fl.y].type;
	func = get_print();
	func[type](s);
}

t_init	*get_init(void)
{
	t_init	*init;

	init = (t_init*)malloc(sizeof(t_init) * 10);
	init[Sphere] = &init_prop;
	init[InfiniteCylinder] = &init_ic_prop;
	init[InfinitePlane] = &init_plane_prop;
	init[Triangle] = &triangle_init_prop;
	init[InfiniteCone] = &init_cone_prop;
	init[Cube] = &init_cube_prop;
	init[Quadrate] = &init_quadraate_prop;
	init[Elipsoid] = &init_elips_prop;
	init[Parabaloid] = &init_parab_prop;
	return (init);
}

void	get_init_prop(t_view *s)
{
	t_init	*init;
	int		type;

	type = s->space->cl_figures[s->rr.fl.y].type;
	init = get_init();
	init[type](s);
}
