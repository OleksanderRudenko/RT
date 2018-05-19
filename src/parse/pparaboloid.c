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
static t_figure* init_figure(t_figure* fparaboloid, t_vector v1, t_vector v2)
{
	fparaboloid = (t_figure*)malloc(sizeof(t_figure));
	fparaboloid->figure = (t_parabaloid*)malloc(sizeof(t_parabaloid));
	((t_parabaloid*)fparaboloid->figure)->position = v1;
	((t_parabaloid*)fparaboloid->figure)->rotation = v2;
	((t_parabaloid*)fparaboloid->figure)->caps = NULL;
	return (fparaboloid);
}
/* END */

static void	parse_paraboloid2(JSON_Object *paraboloid, t_figure *fparaboloid,
																t_view *view)
{
	if (json_object_has_value_of_type(paraboloid, "radius", JSONNumber))
		((t_parabaloid*)fparaboloid->figure)->radius =
								json_object_get_number(paraboloid, "radius");
	else
		ft_putendl_fd("Unknown or invalid paraboloid radius. Default applied",
					STDERR_FILENO);
	if (json_object_has_value_of_type(paraboloid, "cut plane", JSONObject))
	{
		((t_parabaloid*)fparaboloid->figure)->caps = init_cut_plane();
		parse_cut_plane(((t_parabaloid*)fparaboloid->figure)->caps->plane,
		((t_parabaloid*)fparaboloid->figure)->caps, paraboloid, "cut plane");
	}
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
	fparaboloid = init_figure(fparaboloid, vector[0], vector[1]);
	parse_paraboloid2(paraboloid, fparaboloid, view);
}
