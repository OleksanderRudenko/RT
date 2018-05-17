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

/* FOR TESTING */
static t_figure* init_params(t_figure* fparaboloid, t_vector v1, t_vector v2)
{
	t_capses *caps;

	fparaboloid = (t_figure*)malloc(sizeof(t_figure));
	fparaboloid->figure = (t_parabaloid*)malloc(sizeof(t_parabaloid));
	((t_parabaloid*)fparaboloid->figure)->caps = (t_capses*)malloc(sizeof(t_capses));
	caps = ((t_parabaloid*)fparaboloid->figure)->caps;
	((t_parabaloid*)fparaboloid->figure)->position = v1;
	((t_parabaloid*)fparaboloid->figure)->rotation = v2;
	caps->plane = (t_iplane*)malloc(sizeof(t_iplane));
	/* setting default */
	caps->plane->normale = (t_vector){0, 1, 0};
	caps->plane->point = (t_vector){0, 0, 0};
	caps->color.color = 0xffffff;
	caps->enable_caps = 0;
	return (fparaboloid);
}
/* END */

static void	parse_paraboloid2(JSON_Object *paraboloid,
											t_figure *fparaboloid, t_view *view)
{
	t_capses *caps;
	double 	 radius;

	caps = ((t_parabaloid*)fparaboloid->figure)->caps;
	if (json_object_has_value_of_type(paraboloid, "radius", JSONNumber))
	{
		radius = json_object_get_number(paraboloid, "radius");
		((t_parabaloid*)fparaboloid->figure)->radius = radius;
	}
	else
		ft_putendl_fd("Unknown or invalid paraboloid radius. Default applied",
					STDERR_FILENO);
	if (json_object_has_value_of_type(paraboloid, "cut plane", JSONObject))
		parse_cut_plane(caps->plane, caps, paraboloid, "cut plane");
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
	/* init paraboloid */
	fparaboloid = init_params(fparaboloid, vector[0], vector[1]);
	parse_paraboloid2(paraboloid, fparaboloid, view);
}
