/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 21:31:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/18 21:31:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			check_array(JSON_Array *array, JSON_Value_Type type, size_t len)
{
	size_t	i;

	i = json_array_get_count(array);
	if (i != len)
		return (0);
	while (i > 0 && json_value_get_type(json_array_get_value(array, i - 1)) ==
			type)
		i--;
	if (i == 0)
		return (1);
	return (0);
}

int			check_triangle_points(t_vector vector[3])
{
	int a;

	if ((a = vis_equal(vector[0],vector[1]) || vis_equal(vector[2],vector[1]) ||
			vis_equal(vector[0],vector[2])))
		ft_putendl_fd("Triangle cannot have equal points. Figure skipped",
				STDERR_FILENO);
	return (a);
}

void		parse_triangle(JSON_Object *triangle, t_view *view)
{
	JSON_Array	*points;
	t_figure	*figure;
	t_vector	v[3];
	size_t		i;

	if ((points = json_object_get_array(triangle, "points")) == NULL &&
			check_array(points, JSONArray, 3))
		ft_putendl_fd("Triangle have no points array or this array is broken. "
				"Figure skipped",
				STDERR_FILENO);
	i = 3;
	while (i > 0)
	{
		v[i - 1] = parse_vector(json_array_get_array(points, i - 1),
				(t_vector){0, 0, 0});
		i--;
	}
	if (check_triangle_points(v))
		return ;
	figure = triangle_init(ray_init(v[0],v[1]), v[2], 0xffffff, 0);
	parse_color_reflection(triangle, figure);
	add_figure(figure, view);
}
