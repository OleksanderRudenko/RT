/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pcut_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 18:53:08 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/16 18:53:09 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_capses 	*init_cut_plane(void)
{
	t_capses *caps;

	caps = (t_capses*)malloc(sizeof(t_capses));
	caps->plane = (t_iplane*)malloc(sizeof(t_iplane));
	caps->plane->normale = (t_vector){0, 1, 0};
	caps->plane->point = (t_vector){0, 0, 0};
	caps->color.color = 0xffffff;
	caps->enable_caps = 0;
	return (caps);
}

void 	parse_cut_plane(t_iplane *fplane, t_capses *caps, JSON_Object *obj,
														const char *name)
{
	JSON_Object	*plane;

	plane = json_object_dotget_object(obj, name);
	if (json_object_has_value_of_type(plane, "normale", JSONArray))
		fplane->normale = parse_vector(json_object_get_array(plane, "normale"),
						fplane->normale);
	else
		ft_putendl_fd("Unknown cut plane normale. Default applied",
						STDERR_FILENO);
	if (json_object_has_value_of_type(plane, "point", JSONArray))
		fplane->point = parse_vector(json_object_get_array(plane, "point"),
						fplane->point);
	else
		ft_putendl_fd("Unknown cut plane point. Default applied",
						STDERR_FILENO);
	if (json_object_has_value_of_type(plane, "color", JSONString) &&
			check_hex(json_object_get_string(plane, "color")))
		caps->color.color = ft_hexatoi(json_object_get_string(plane, "color"));
	else
		ft_putendl_fd("Unknown or invalid color. Default applied",
				STDERR_FILENO);
	caps->enable_caps = 1;
}
