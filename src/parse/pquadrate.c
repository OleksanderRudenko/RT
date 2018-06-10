/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pquadrate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 13:14:55 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 11:43:00 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_scale(JSON_Array *scale, double *s)
{
	size_t c;
	size_t i;

	c = json_array_get_count(scale);
	if (c != 2)
	{
		ft_putendl_fd("Wrong scale size. Default applied", STDERR_FILENO);
		return ;
	}
	i = 0;
	while (i < c)
	{
		if (json_value_get_type(json_array_get_value(scale, i)) != JSONNumber)
		{
			ft_putendl_fd("Wrong scale format. Default applied",
					STDERR_FILENO);
			return ;
		}
		i++;
	}
	s[0] = json_array_get_number(scale, 0);
	s[1] = json_array_get_number(scale, 1);
}

static void	parse_quadrate2(JSON_Object *quadrate, t_view *view, t_figure *fig)
{
	if (json_object_has_value_of_type(quadrate, "texture", JSONNumber))
		fig->texture = json_object_get_number(quadrate, "texture");
	parse_color_reflection(quadrate, fig);
	add_figure(fig, view);
}

void		parse_quadrate(JSON_Object *quadrate, t_view *view)
{
	t_figure	*fquad;
	t_vector	rotation;
	t_vector	position;
	double		scale[2];

	scale[0] = 1;
	scale[1] = 1;
	rotation = (t_vector){0, 0, 0};
	position = (t_vector){0, 0, 0};
	if (json_object_has_value_of_type(quadrate, "position", JSONArray))
		position = parse_vector(json_object_get_array(quadrate, "position"),
				(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown quadrate position. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(quadrate, "rotation", JSONArray))
		rotation = parse_vector(json_object_get_array(quadrate, "rotation"),
				(t_vector){0, 0, 0});
	else
		ft_putendl_fd("Unknown quadrate rotation. Default applied",
				STDERR_FILENO);
	if (json_object_has_value_of_type(quadrate, "scale", JSONArray))
		parse_scale(json_object_get_array(quadrate, "scale"), scale);
	fquad = quadrate_init(rotation, position, scale);
	parse_quadrate2(quadrate, view, fquad);
}
