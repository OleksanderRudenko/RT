/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 13:20:20 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 11:46:32 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_ambient(JSON_Object *light, t_view *view)
{
	t_light *llight;

	llight = light_init(LIGHT_TYPE_AMBIENT, vector_init(0, 0, 0),
										vector_init(0, 0, 0), 0);
	if (json_object_has_value_of_type(light, "intensity", JSONNumber))
		llight->inten = json_object_get_number(light, "intensity");
	else
		ft_putendl_fd("Unknown or invalid ambient light intensity."
						"Default applied",
				STDERR_FILENO);
	add_light(llight, view);
}

void	parse_point(JSON_Object *light, t_view *view)
{
	t_light *llight;

	llight = light_init(LIGHT_TYPE_POINT, vector_init(0, 0, 0),
										vector_init(0, 0, 0), 0);
	if (json_object_has_value_of_type(light, "position", JSONArray))
		llight->o = parse_vector(json_object_get_array(light,
				"position"), llight->o);
	else
		ft_putendl_fd("Unknown spot position. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(light, "intensity", JSONNumber))
		llight->inten = json_object_get_number(light, "intensity");
	else
		ft_putendl_fd("Unknown or invalid spot intensity."
						"Default applied",
				STDERR_FILENO);
	add_light(llight, view);
}

void	parse_directional(JSON_Object *light, t_view *view)
{
	t_light *llight;

	llight = light_init(LIGHT_TYPE_DIRECT, vector_init(0, 0, 0),
										vector_init(0, 0, 0), 0);
	if (json_object_has_value_of_type(light, "position", JSONArray))
		llight->o = parse_vector(json_object_get_array(light,
				"position"), llight->o);
	else
		ft_putendl_fd("Unknown spot position. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(light, "intensity", JSONNumber))
		llight->inten = json_object_get_number(light, "intensity");
	else
		ft_putendl_fd("Unknown or invalid spot intensity."
						"Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(light, "direction", JSONArray))
		llight->d = parse_vector(json_object_get_array(light,
				"direction"), llight->d);
	else
		ft_putendl_fd("Unknown spot position. Default applied", STDERR_FILENO);
	add_light(llight, view);
}
