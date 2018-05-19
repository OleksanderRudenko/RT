/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pquadrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:14:55 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/18 13:14:56 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/* FOR TESTING */
t_figure 	*init_figure(t_vector vector[5])
{
	t_figure *quadr;
	t_squard *q;

	quadr = (t_figure*)malloc(sizeof(t_figure));
	q = (t_squard*)malloc(sizeof(t_squard));
	q->points[0] = vector[0];
	q->points[1] = vector[1];
	q->points[2] = vector[2];
	q->points[3] = vector[3];
	q->normale = vector[4];
	quadr->figure = q;
	return (quadr);
}

int		check_quadr_points(t_vector vector[5])
{
	int a;

	if ((a = vis_equal(vector[0],vector[1]) || vis_equal(vector[2],vector[1]) ||
		vis_equal(vector[0],vector[2]) || vis_equal(vector[2],vector[3]) ||
		vis_equal(vector[0],vector[3]) || vis_equal(vector[3],vector[1])))
		ft_putendl_fd("Quadrate cannot have equal points. Figure skipped",
				STDERR_FILENO);
	return (a);
}

void parse_quadrate(JSON_Object *quadrate, t_view *view)
{
	JSON_Array 	*points;
	t_figure 	*fquad;
	t_vector 	vector[5];
	size_t 		n;

	fquad = NULL;
	if (json_object_has_value_of_type(quadrate, "normale", JSONArray))
		vector[4] = parse_vector(json_object_get_array(quadrate, "normale"),
											(t_vector){0, 0, 0});
	if (json_object_has_value_of_type(quadrate, "points", JSONArray))
	{
		if ((points = json_object_get_array(quadrate, "points")) == NULL &&
			check_array(points, JSONArray, 4))
			ft_putendl_fd("Quadrate has invalid points. Figure skipped",
					STDERR_FILENO);
		n = -1;
		while (++n < 4)
			vector[n] = parse_vector(json_array_get_array(points, n),
					(t_vector){0, 0, 0});
		if (check_quadr_points(vector))
			return ;
		fquad = init_figure(vector);
	}
	parse_color_reflection(quadrate, fquad);
	add_figure(fquad, view);
}
