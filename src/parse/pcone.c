/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 23:35:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:29:03 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_cone2(JSON_Object *cone, t_figure	*fcone, t_view *view)
{
	if (json_object_has_value_of_type(cone, "cut plane1", JSONObject))
	{
		((t_icone*)fcone->figure)->caps1 = init_cut_plane();
		parse_cut_plane(((t_icone*)fcone->figure)->caps1->plane,
		((t_icone*)fcone->figure)->caps1, cone, "cut plane1");
	}
	if (json_object_has_value_of_type(cone, "cut plane2", JSONObject))
	{
		((t_icone*)fcone->figure)->caps2 = init_cut_plane();
		parse_cut_plane(((t_icone*)fcone->figure)->caps2->plane,
		((t_icone*)fcone->figure)->caps2, cone, "cut plane2");
	}
	parse_color_reflection(cone, fcone);
	add_figure(fcone, view);
}

void		parse_cone(JSON_Object *cone, t_view *view)
{
	t_figure	*fcone;

	printf("\n* CONE *\n");
	fcone = cone_init(ray_init((t_vector){0, 0, 0},
			(t_vector){0, -1, 0}), 1, 0xffffff, 0);
	if (json_object_has_value_of_type(cone, "start", JSONArray))
		((t_icone*)fcone->figure)->vertex =
				parse_vector(json_object_get_array(cone,
				"start"), ((t_icone*)fcone->figure)->vertex);
	else
		ft_putendl_fd("Unknown cone start. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cone, "vector", JSONArray))
		((t_icone*)fcone->figure)->vector =
				vnormalize(parse_vector(json_object_get_array(
				cone, "vector"), ((t_icone*)fcone->figure)->vector));
	else
		ft_putendl_fd("Unknown cone axis vector. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cone, "radius", JSONNumber))
		((t_icone*)fcone->figure)->radius = json_object_get_number(cone,
																"radius");
	else
		ft_putendl_fd("Unknown or invalid cone radius. Default applied",
				STDERR_FILENO);
	parse_cone2(cone, fcone, view);
}
