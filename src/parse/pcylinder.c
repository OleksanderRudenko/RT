/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 22:04:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:29:03 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_cylinder(JSON_Object *cylinder, t_view *view)
{
	t_figure	*fcylinder;

	fcylinder = cylinder_init(ray_init((t_vector){0, 0, 0},
			(t_vector){0, -1, 0}), 1, 0xffffff, 0);
	if (json_object_has_value_of_type(cylinder, "start", JSONArray))
		((t_icylinder*)fcylinder->figure)->start =
				parse_vector(json_object_get_array(cylinder,
				"start"), ((t_icylinder*)fcylinder->figure)->start);
	else
		ft_putendl_fd("Unknown cylinder start. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cylinder, "vector", JSONArray))
		((t_icylinder*)fcylinder->figure)->vector =
				vnormalize(parse_vector(json_object_get_array(cylinder,
						"vector"), ((t_icylinder*)fcylinder->figure)->vector));
	else
		ft_putendl_fd("Unknown cylinder axis vector. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cylinder, "radius", JSONNumber))
		((t_icylinder*)fcylinder->figure)->radius =
				json_object_get_number(cylinder, "radius");
	else
		ft_putendl_fd("Unknown or invalid cylinder radius. Default applied",
				STDERR_FILENO);
	parse_color_reflection(cylinder, fcylinder);
	add_figure(fcylinder, view);
}
