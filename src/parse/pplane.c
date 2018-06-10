/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 21:55:00 by knovytsk          #+#    #+#             */
/*   Updated: 2018/04/18 16:47:58 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_plane(JSON_Object *plane, t_view *view)
{
	t_figure	*fplane;

	fplane = plane_init((t_vector){0, 1, 0}, (t_vector){0, 0, 0}, 0xffffff, 0);
	if (json_object_has_value_of_type(plane, "normale", JSONArray))
		((t_iplane*)fplane->figure)->normale = parse_vector(
				json_object_get_array(plane, "normale"),
				((t_iplane*)fplane->figure)->normale);
	else
		ft_putendl_fd("Unknown plane normale. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(plane, "point", JSONArray))
		((t_iplane*)fplane->figure)->point = parse_vector(
				json_object_get_array(plane, "point"),
				((t_iplane*)fplane->figure)->point);
	else
		ft_putendl_fd("Unknown plane point. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(plane, "texture", JSONNumber))
		fplane->texture = json_object_get_number(plane, "texture");
	parse_color_reflection(plane, fplane);
	add_figure(fplane, view);
}
