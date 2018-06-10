/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 17:48:12 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 12:00:08 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_parse(JSON_Object *figure, t_view *view, char *type)
{
	if (ft_strequ(type, "sphere"))
		parse_sphere(figure, view);
	else if (ft_strequ(type, "plane"))
		parse_plane(figure, view);
	else if (ft_strequ(type, "cylinder"))
		parse_cylinder(figure, view);
	else if (ft_strequ(type, "cone"))
		parse_cone(figure, view);
	else if (ft_strequ(type, "triangle"))
		parse_triangle(figure, view);
	else if (ft_strequ(type, "elipsoid"))
		parse_elipsoid(figure, view);
	else if (ft_strequ(type, "paraboloid"))
		parse_paraboloid(figure, view);
	else if (ft_strequ(type, "quadrate"))
		parse_quadrate(figure, view);
	else if (ft_strequ(type, "cube"))
		parse_cube(figure, view);
	else
		ft_putendl_fd("Unknown figure found. Skipped", STDERR_FILENO);
}
