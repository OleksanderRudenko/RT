/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 23:35:00 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 11:59:38 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_cone2(JSON_Object *cone, t_figure *fcone, t_view *view)
{
	if (json_object_has_value_of_type(cone, "cut plane1", JSONNumber))
		((t_icone*)fcone->figure)->c_distances[0] =
						json_object_get_number(cone, "cut plane1");
	if (json_object_has_value_of_type(cone, "cut plane1", JSONNumber))
		((t_icone*)fcone->figure)->c_distances[1] =
						json_object_get_number(cone, "cut plane2");
	if (json_object_has_value_of_type(cone, "texture", JSONNumber))
		fcone->texture = json_object_get_number(cone, "texture");
	parse_color_reflection(cone, fcone);
	add_figure(fcone, view);
}

void		parse_cone(JSON_Object *cone, t_view *view)
{
	t_figure	*fcone;

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
