/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:41:00 by knovytsk          #+#    #+#             */
/*   Updated: 2018/04/18 16:48:20 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_sphere(JSON_Object *sphere, t_view *view)
{
	t_figure	*fsphere;

	fsphere = sphere_init((t_vector){0, 0, 0}, 1, 0xffffff, 0);
	if (json_object_has_value_of_type(sphere, "center", JSONArray))
		((t_sphere*)fsphere->figure)->center = parse_vector(
				json_object_get_array(sphere, "center"),
				((t_sphere*)fsphere->figure)->center);
	else
		ft_putendl_fd("Unknown sphere center. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(sphere, "radius", JSONNumber))
		((t_sphere*)fsphere->figure)->radius = json_object_get_number(sphere,
				"radius");
	else
		ft_putendl_fd("Unknown or invalid sphere radius. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(sphere, "texture", JSONNumber))
		fsphere->texture = json_object_get_number(sphere, "texture");
	parse_color_reflection(sphere, fsphere);
	add_figure(fsphere, view);
}
