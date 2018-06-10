/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pelipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:19:56 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 11:57:18 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_radius_and_distance(JSON_Object *elipsoid, t_figure *felips)
{
	if (json_object_has_value_of_type(elipsoid, "radius", JSONNumber))
		((t_elipsoid*)felips->figure)->radius = json_object_get_number(elipsoid,
			"radius");
	else
		ft_putendl_fd("Unknown or invalid elipsoid radius. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(elipsoid, "rdistance", JSONNumber))
		((t_elipsoid*)felips->figure)->rdistance =
			json_object_get_number(elipsoid, "rdistance");
	else
		ft_putendl_fd("Unknown or invalid elipsoid radiuses distance."
				"Default applied", STDERR_FILENO);
	if (((t_elipsoid*)felips->figure)->rdistance < 0)
		ft_putendl_fd("Radiuses distance is invalid. Default applied",
				STDERR_FILENO);
}

void		parse_elipsoid(JSON_Object *elipsoid, t_view *view)
{
	t_figure	*felipsoid;
	t_vector	vector[2];

	if (json_object_has_value_of_type(elipsoid, "position", JSONArray))
		vector[0] = parse_vector(json_object_get_array(elipsoid, "position"),
				(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown elipsoid position parameter. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(elipsoid, "rotation", JSONArray))
		vector[1] = parse_vector(json_object_get_array(elipsoid, "rotation"),
				(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown elipsoid rotation parameter. Default applied",
				STDERR_FILENO);
	felipsoid = elipsoid_init(vector[0], vector[1], 0xffffff, 0);
	check_radius_and_distance(elipsoid, felipsoid);
	parse_color_reflection(elipsoid, felipsoid);
	add_figure(felipsoid, view);
}
