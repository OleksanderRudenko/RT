/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fcube.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.unit.ua>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 19:15:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/19 19:15:00 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// void		count_planes(t_cube *cube);

t_figure	*cube_init(t_vector vector[3], int color, double reflection)
{
	t_figure	*new_figure;
	t_cube		*cube;

	new_figure = (t_figure*)malloc(sizeof(t_figure));
	cube = (t_cube*)malloc(sizeof(t_cube));
	new_figure->type = Cube;
	new_figure->figure = cube;
	cube->position = vector[0];
	cube->rotation = vector[1];
	cube->scale = vector[2];
	// count_planes(cube);
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
