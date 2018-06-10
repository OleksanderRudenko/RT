/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcube.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/21 10:47:00 by knovytsk          #+#    #+#             */
/*   Updated: 2018/04/21 10:47:00 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_cube2(JSON_Object *cube, t_view *view, t_figure *figure)
{
	if (json_object_has_value_of_type(cube, "texture", JSONNumber))
		figure->texture = json_object_get_number(cube, "texture");
	parse_color_reflection(cube, figure);
	add_figure(figure, view);
}

void		parse_cube(JSON_Object *cube, t_view *view)
{
	t_figure	*figure;
	t_vector	vector[3];

	if (json_object_has_value_of_type(cube, "position", JSONArray))
		vector[0] = parse_vector(json_object_get_array(cube, "position"),
				(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown cube position parameter. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cube, "rotation", JSONArray))
		vector[1] = parse_vector(json_object_get_array(cube, "rotation"),
				(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown cube rotation parameter. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cube, "scale", JSONArray))
		vector[2] = parse_vector(json_object_get_array(cube, "scale"),
						(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown cube scale parameter. Default applied",
						STDERR_FILENO);
	figure = cube_init(vector, 0xffffff, 0);
	parse_cube2(cube, view, figure);
}
