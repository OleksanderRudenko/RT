/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pparaboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:48:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/11 20:56:38 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_paraboloid2(JSON_Object *paraboloid,
	t_figure *fparaboloid, t_view *view)
{
	if (json_object_has_value_of_type(paraboloid, "radius", JSONNumber))
		((t_parabaloid*)fparaboloid->figure)->radius =
								json_object_get_number(paraboloid, "radius");
	else
		ft_putendl_fd("Unknown or invalid paraboloid radius. Default applied",
					STDERR_FILENO);
	if (json_object_has_value_of_type(paraboloid, "cut plane1", JSONNumber))
		((t_parabaloid*)fparaboloid->figure)->c_distances[0] =
							json_object_get_number(paraboloid, "cut plane1");
	parse_color_reflection(paraboloid, fparaboloid);
	add_figure(fparaboloid, view);
}

void		parse_paraboloid(JSON_Object *paraboloid, t_view *view)
{
	t_figure	*fparaboloid;
	t_vector	vector[2];

	fparaboloid = NULL;
	if (json_object_has_value_of_type(paraboloid, "position", JSONArray))
		vector[0] = parse_vector(json_object_get_array(paraboloid, "position"),
					(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown elipsoid position parameter. Default applied",
					STDERR_FILENO);
	if (json_object_has_value_of_type(paraboloid, "rotation", JSONArray))
		vector[1] = parse_vector(json_object_get_array(paraboloid, "rotation"),
					(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown elipsoid rotation parameter. Default applied",
					STDERR_FILENO);
	fparaboloid = init_parab(fparaboloid, vector[0], vector[1]);
	parse_paraboloid2(paraboloid, fparaboloid, view);
}
