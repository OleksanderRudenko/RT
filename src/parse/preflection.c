/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preflection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:46:44 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/08 12:46:45 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_color_reflection(JSON_Object *sphere, t_figure *figure)
{
	if (json_object_has_value_of_type(sphere, "color", JSONString) &&
			check_hex(json_object_get_string(sphere, "color")))
		figure->color = ft_hexatoi(json_object_get_string(sphere,
				"color"));
	else
		ft_putendl_fd("Unknown or invalid color. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(sphere, "reflection", JSONNumber))
		figure->reflection = json_object_get_number(sphere, "reflection");
	else
		ft_putendl_fd("Unknown or invalid reflection. Default applied",
				STDERR_FILENO);
}
