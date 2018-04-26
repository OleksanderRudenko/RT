/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 18:41:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:48:20 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	parse_vector(JSON_Array *vector, t_vector def)
{
	size_t i;
	size_t c;

	c = json_array_get_count(vector);
	if (c != 3)
	{
		ft_putendl_fd("Wrong vector size. Default applied", STDERR_FILENO);
		return (def);
	}
	i = 0;
	while (i < c)
	{
		if (json_value_get_type(json_array_get_value(vector, i)) != JSONNumber)
		{
			ft_putendl_fd("Wrong vector format. Default applied",
					STDERR_FILENO);
			return (def);
		}
		i++;
	}
	return (vector_init(json_array_get_number(vector, 0),
			json_array_get_number(vector, 1),
			json_array_get_number(vector, 2)));
}

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
	parse_color_reflection(sphere, fsphere);
	add_figure(fsphere, view);
}
