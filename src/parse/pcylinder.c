/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 22:04:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:29:03 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* FOR TESTING */
static void init_params(t_figure *fcylinder)
{
	t_capses *caps1;
	t_capses *caps2;

	((t_icylinder*)fcylinder->figure)->caps1 = (t_capses*)malloc(sizeof(t_capses));
	((t_icylinder*)fcylinder->figure)->caps2 = (t_capses*)malloc(sizeof(t_capses));
	caps1 = ((t_icylinder*)fcylinder->figure)->caps1;
	caps2 = ((t_icylinder*)fcylinder->figure)->caps2;
	caps1->plane = (t_iplane*)malloc(sizeof(t_iplane));
	caps2->plane = (t_iplane*)malloc(sizeof(t_iplane));
	/* setting default */
	caps1->plane->normale = (t_vector){0, 1, 0};
	caps1->plane->point = (t_vector){0, 0, 0};
	caps1->color.color = 0xffffff;
	caps1->enable_caps = 0;
	caps2->plane->normale = (t_vector){0, 1, 0};
	caps2->plane->point = (t_vector){0, 0, 0};
	caps2->color.color = 0xffffff;
	caps2->enable_caps = 0;
}
/* END */

static void parse_cylinder2(JSON_Object *cylinder, t_figure	*fcylinder,
																  t_view *view)
{
	t_capses *caps1;
	t_capses *caps2;

	init_params(fcylinder);
	caps1 = ((t_icylinder*)fcylinder->figure)->caps1;
	caps2 = ((t_icylinder*)fcylinder->figure)->caps2;
	if (json_object_has_value_of_type(cylinder, "cut plane1", JSONObject))
		parse_cut_plane(caps1->plane, caps1, cylinder, "cut plane1");
	if (json_object_has_value_of_type(cylinder, "cut plane2", JSONObject))
		parse_cut_plane(caps2->plane, caps2, cylinder, "cut plane2");
	parse_color_reflection(cylinder, fcylinder);
	add_figure(fcylinder, view);
}

void		parse_cylinder(JSON_Object *cylinder, t_view *view)
{
	t_figure	*fcylinder;

	fcylinder = cylinder_init(ray_init((t_vector){0, 0, 0},
			(t_vector){0, -1, 0}), 1, 0xffffff, 0);
	if (json_object_has_value_of_type(cylinder, "start", JSONArray))
		((t_icylinder*)fcylinder->figure)->start =
				parse_vector(json_object_get_array(cylinder,
				"start"), ((t_icylinder*)fcylinder->figure)->start);
	else
		ft_putendl_fd("Unknown cylinder start. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cylinder, "vector", JSONArray))
		((t_icylinder*)fcylinder->figure)->vector =
				vnormalize(parse_vector(json_object_get_array(cylinder,
						"vector"), ((t_icylinder*)fcylinder->figure)->vector));
	else
		ft_putendl_fd("Unknown cylinder axis vector. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cylinder, "radius", JSONNumber))
		((t_icylinder*)fcylinder->figure)->radius =
				json_object_get_number(cylinder, "radius");
	else
		ft_putendl_fd("Unknown or invalid cylinder radius. Default applied",
				STDERR_FILENO);
	parse_cylinder2(cylinder, fcylinder, view);
}
