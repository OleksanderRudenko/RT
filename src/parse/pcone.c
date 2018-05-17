/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 23:35:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 16:29:03 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_cone2(JSON_Object *cone, t_figure	*fcone, t_view *view)
{
	t_capses *caps1;
	t_capses *caps2;

	caps1 = ((t_icone*)fcone->figure)->caps1;
	caps2 = ((t_icone*)fcone->figure)->caps2;
	if (json_object_has_value_of_type(cone, "radius", JSONNumber))
		((t_icone*)fcone->figure)->radius = json_object_get_number(cone, "radius");
	else
		ft_putendl_fd("Unknown or invalid cone radius. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(cone, "cut plane1", JSONObject))
		parse_cut_plane(caps1->plane, caps1, cone, "cut plane1");
	if (json_object_has_value_of_type(cone, "cut plane2", JSONObject))
		parse_cut_plane(caps2->plane, caps2, cone, "cut plane2");
	parse_color_reflection(cone, fcone);
	add_figure(fcone, view);

	printf("\nCone:\n");
	printf("\ncaps1:\n");
	t_iplane *plane = caps1->plane;
	printf("normale (%f %f %f) point (%f %f %f) color->%#x\n", plane->normale.x, plane->normale.y, plane->normale.z,
		plane->point.x, plane->point.y, plane->point.z, ((t_icone*)fcone->figure)->caps1->color.color);
	printf("\ncaps2:\n");
	plane = caps2->plane;
	printf("normale (%f %f %f) point (%f %f %f) color->%#x\n\n", plane->normale.x, plane->normale.y, plane->normale.z,
		plane->point.x, plane->point.y, plane->point.z, ((t_icone*)fcone->figure)->caps2->color.color);
	// printf("color->%#x reflection->%f\n", fcone->color, fcone->reflection);
}

void		parse_cone(JSON_Object *cone, t_view *view)
{
	t_figure	*fcone;

	fcone = cone_init(ray_init((t_vector){0, 0, 0},
			(t_vector){0, -1, 0}), 1, 0xffffff, 0);
	((t_icone*)fcone->figure)->caps1 = (t_capses*)malloc(sizeof(t_capses));
	((t_icone*)fcone->figure)->caps1->plane = (t_iplane*)plane_init((t_vector){0, 1, 0},
			(t_vector){0, 0, 0}, 0xffffff, 0);
	((t_icone*)fcone->figure)->caps2 = (t_capses*)malloc(sizeof(t_capses));
	((t_icone*)fcone->figure)->caps2->plane = (t_iplane*)plane_init((t_vector){0, 1, 0},
					(t_vector){0, 0, 0}, 0xffffff, 0);

	if (json_object_has_value_of_type(cone, "start", JSONArray))
		((t_icone*)fcone->figure)->vertex =
				parse_vector(json_object_get_array(cone,
				"start"), ((t_icone*)fcone->figure)->vertex);
	else
		ft_putendl_fd("Unknown cone start. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(cone, "vector", JSONArray))
		((t_icone*)fcone->figure)->vector =
				vnormalize(parse_vector(json_object_get_array(
				cone, "vector"), ((t_icone*)fcone->figure)->vector));
	else
		ft_putendl_fd("Unknown cone axis vector. Default applied",
				STDERR_FILENO);
	parse_cone2(cone, fcone, view);

	// printf("start (%f %f %f) vector (%f %f %f) radius->%f\n", ((t_icone*)fcone->figure)->vertex.x,
	// ((t_icone*)fcone->figure)->vertex.y, ((t_icone*)fcone->figure)->vertex.z,
	// ((t_icone*)fcone->figure)->vector.x, ((t_icone*)fcone->figure)->vector.y,
	// ((t_icone*)fcone->figure)->vector.z, ((t_icone*)fcone->figure)->radius);
	// printf("\ncaps1:\n");
	// t_iplane *plane = ((t_icone*)fcone->figure)->caps1->plane;
	// printf("normale (%f %f %f) point (%f %f %f) color->%#x\n", plane->normale.x, plane->normale.y, plane->normale.z,
	// 	plane->point.x, plane->point.y, plane->point.z, ((t_icone*)fcone->figure)->caps1->color.color);
	// printf("color->%#x reflection->%f\n", fcone->color, fcone->reflection);
	// printf("\ncaps2:\n");
	// plane = ((t_icone*)fcone->figure)->caps2->plane;
	// printf("normale (%f %f %f) point (%f %f %f) color->%#x\n", plane->normale.x, plane->normale.y, plane->normale.z,
	// 	plane->point.x, plane->point.y, plane->point.z, ((t_icone*)fcone->figure)->caps2->color.color);
	// printf("color->%#x reflection->%f\n", fcone->color, fcone->reflection);
}
