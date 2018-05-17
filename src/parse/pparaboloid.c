/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pparaboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:48:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/16 17:48:13 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_figure* 		init_para(t_figure* fparaboloid, t_vector v1, t_vector v2)
{
	fparaboloid = (t_figure*)malloc(sizeof(t_figure));
	fparaboloid->figure = (t_parabaloid*)malloc(sizeof(t_parabaloid));
	((t_parabaloid*)fparaboloid->figure)->position = v1;
	((t_parabaloid*)fparaboloid->figure)->rotation = v2;
	((t_parabaloid*)fparaboloid->figure)->caps = (t_capses*)malloc(sizeof(t_capses));
	((t_parabaloid*)fparaboloid->figure)->caps->plane = (t_iplane*)plane_init((t_vector){0, 1, 0},
	(t_vector){0, 0, 0}, 0xffffff, 0);
	return (fparaboloid);
}

void		parse_paraboloid2(JSON_Object *paraboloid, t_figure 	*fparaboloid, t_view *view)
{
	if (json_object_has_value_of_type(paraboloid, "radius", JSONNumber))
	((t_parabaloid*)fparaboloid->figure)->radius = json_object_get_number(paraboloid,
			"radius");
	else
		ft_putendl_fd("Unknown or invalid paraboloid radius. Default applied",
					STDERR_FILENO);
	if (json_object_has_value_of_type(paraboloid, "cut plane", JSONObject))
		parse_cut_plane(((t_parabaloid*)fparaboloid->figure)->caps->plane,
					((t_parabaloid*)fparaboloid->figure)->caps, paraboloid, "cut plane");
	parse_color_reflection(paraboloid, fparaboloid);
	add_figure(fparaboloid, view);
}

void		parse_paraboloid(JSON_Object *paraboloid, t_view *view)
{
		t_figure 	*fparaboloid = NULL;
		t_vector	vector[2];

		if (json_object_has_value_of_type(paraboloid, "position", JSONArray))
	    vector[0] = parse_vector(json_object_get_array(paraboloid, "position"),
					(t_vector){0, 0, 0});
	  	else
	     	ft_putendl_fd("Unknown elipsoid position parameter. Default applied",
	      	STDERR_FILENO);
		if (json_object_has_value_of_type(paraboloid, "rotation", JSONArray))
			vector[1] = parse_vector(json_object_get_array(paraboloid, "rotation"),
				  (t_vector){0, 0, 0});
		else
			ft_putendl_fd("Unknown elipsoid rotation parameter. Default applied",
				  STDERR_FILENO);
		fparaboloid = init_para(fparaboloid, vector[0], vector[1]);
		parse_paraboloid2(paraboloid, fparaboloid, view);

		printf("\nParaboloid:\n");
		printf("position (%f %f %f) rotation (%f %f %f) radius->%f\n", ((t_parabaloid*)fparaboloid->figure)->position.x,
		((t_parabaloid*)fparaboloid->figure)->position.y, ((t_parabaloid*)fparaboloid->figure)->position.z,
		((t_parabaloid*)fparaboloid->figure)->rotation.x, ((t_parabaloid*)fparaboloid->figure)->rotation.y,
		((t_parabaloid*)fparaboloid->figure)->rotation.z, ((t_parabaloid*)fparaboloid->figure)->radius);
		t_iplane *plane = ((t_parabaloid*)fparaboloid->figure)->caps->plane;
		printf("normale (%f %f %f) point (%f %f %f) color->%#x\n\n", plane->normale.x, plane->normale.y, plane->normale.z,
			plane->point.x, plane->point.y, plane->point.z, ((t_parabaloid*)fparaboloid->figure)->caps->color.color);
		// printf("color->%#x reflection->%f\n", fparaboloid->color, fparaboloid->reflection);
}
