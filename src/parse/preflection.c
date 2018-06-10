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

void		parse_color_reflection(JSON_Object *fobject, t_figure *figure)
{
	if (json_object_has_value_of_type(fobject, "color", JSONString) &&
			check_hex(json_object_get_string(fobject, "color")))
		figure->color = ft_hexatoi(json_object_get_string(fobject, "color"));
	else
		ft_putendl_fd("Unknown or invalid color. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(fobject, "reflection", JSONNumber))
		figure->reflection = json_object_get_number(fobject, "reflection");
	else
		ft_putendl_fd("Unknown or invalid reflection. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(fobject, "refraction", JSONNumber))
	{
		if (!json_object_has_value_of_type(fobject, "reflection", JSONNumber))
			figure->refraction =
						json_object_get_number(fobject, "refraction");
	}
	if (json_object_has_value_of_type(fobject, "mirror", JSONNumber))
		figure->mirror = json_object_get_number(fobject, "mirror");
	if (figure->mirror != 1)
		figure->mirror = 0;
}
