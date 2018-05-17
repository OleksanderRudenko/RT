/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptor.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 10:14:04 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/15 10:14:05 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_figure		*tor_init(t_vector center, const double radiuses[2], int color,
    double reflection)
{
t_figure	*new_figure;
t_itor		*tor;

new_figure = (t_figure*)malloc(sizeof(t_figure));
new_figure->type = Tor;
tor = (t_itor*)malloc(sizeof(t_itor));
new_figure->figure = tor;
tor->radius = radiuses[0];
tor->radius_b = radiuses[1];
new_figure->color = color;
new_figure->reflection = reflection;
tor->center = center;
// tor->vector = vnormalize(axis->v);
// free(axis);
new_figure->next = NULL;
return (new_figure);
}

void		parse_tor(JSON_Object *tor, t_view *view)
{
	t_figure	*ftor = NULL;

    //init
    // ftor = tor_init((t_vector){0, 0, 0}, &((double){0, 1}), 0xffffff, 0);
	if (json_object_has_value_of_type(tor, "center", JSONArray))
		((t_itor*)ftor->figure)->center = parse_vector(
				json_object_get_array(tor, "center"),
				((t_itor*)ftor->figure)->center);
	else
		ft_putendl_fd("Unknown tor center. Default applied", STDERR_FILENO);
	if (json_object_has_value_of_type(tor, "radius1", JSONNumber))
		((t_itor*)ftor->figure)->radius = json_object_get_number(tor,
				"radius1");
	else
		ft_putendl_fd("Unknown or invalid tor small radius. Default applied",
                STDERR_FILENO);
    if (json_object_has_value_of_type(tor, "radius2", JSONNumber))
        ((t_itor*)ftor->figure)->radius_b = json_object_get_number(tor,
                 "radius2");
    else
        ft_putendl_fd("Unknown or invalid tor big radius. Default applied",
                STDERR_FILENO);
    parse_color_reflection(tor, ftor);
    // printf("R1->%f R2->%f center (%f %f %f)\n", ((t_itor*)ftor->figure)->radius,
    // ((t_itor*)ftor->figure)->radius_b, ((t_itor*)ftor->figure)->center.x, ((t_itor*)ftor->figure)->center.y,
    // ((t_itor*)ftor->figure)->center.z);
	add_figure(ftor, view);
}
