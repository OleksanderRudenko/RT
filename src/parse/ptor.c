/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:14:04 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/15 10:14:05 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_tor(JSON_Object *tor, t_view *view)
{
	t_figure		*ftor;
	const double 	radiuses[2] = {1, 2};

  	ftor = tor_init((t_vector){0, 0, 0}, radiuses, 0xffffff, 0);
	if (json_object_has_value_of_type(tor, "center", JSONArray))
		((t_itor*)ftor->figure)->center = parse_vector(
				json_object_get_array(tor, "center"),
				((t_itor*)ftor->figure)->center);
	else
		ft_putendl_fd("Unknown tor center. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(tor, "radius1", JSONNumber))
		((t_itor*)ftor->figure)->r = json_object_get_number(tor,
				"radius1");
	else
		ft_putendl_fd("Unknown or invalid tor small radius. Default applied",
                STDERR_FILENO);
    if (json_object_has_value_of_type(tor, "radius2", JSONNumber))
        ((t_itor*)ftor->figure)->r_b = json_object_get_number(tor,
                 "radius2");
    else
        ft_putendl_fd("Unknown or invalid tor big radius. Default applied",
                STDERR_FILENO);
    parse_color_reflection(tor, ftor);
	add_figure(ftor, view);

	printf("R1->%f R2->%f center (%f %f %f)\n", ((t_itor*)ftor->figure)->r,
    ((t_itor*)ftor->figure)->r_b, ((t_itor*)ftor->figure)->center.x, ((t_itor*)ftor->figure)->center.y,
    ((t_itor*)ftor->figure)->center.z);
}
