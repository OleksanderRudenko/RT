/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preflection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:46:44 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/11 16:31:50 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#define NO_REFRACTION -1

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
		figure->refract = json_object_get_number(fobject, "refraction");
		if (figure->refract < 0)
			figure->refract = -1;
		if (figure->refract > 200)
			figure->refract = 200;
	}
	else
		figure->refract = NO_REFRACTION;
	if (json_object_has_value_of_type(fobject, "mirror", JSONNumber))
		figure->mirror = json_object_get_number(fobject, "mirror");
	if (figure->mirror != 1)
		figure->mirror = 0;
}
