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

void	find_first_dots(double k_x, int i, t_cube *cube)
{
	t_vector	tmp_x;
	t_vector	tmp_y;
	t_vector	tmp_z;

	tmp_x = vk_multiple(get_default_vector('x'), k_x * cube->scale.x);
	tmp_y = vsum(tmp_x, vk_multiple(get_default_vector('y'), cube->scale.y));
	tmp_z = vsum(tmp_y, vk_multiple(get_default_vector('z'), cube->scale.z));
	cube->planes[i].points[0] = tmp_z;
	tmp_z = vsub(tmp_y, vk_multiple(get_default_vector('z'), cube->scale.z));
	cube->planes[i].points[1] = tmp_z;
	tmp_y = vsub(tmp_x, vk_multiple(get_default_vector('y'), cube->scale.y));
	tmp_z = vsum(tmp_y, vk_multiple(get_default_vector('z'), cube->scale.z));
	cube->planes[i].points[3] = tmp_z;
	tmp_z = vsub(tmp_y, vk_multiple(get_default_vector('z'), cube->scale.z));
	cube->planes[i].points[2] = tmp_z;
}

void		rotate_cube(t_cube *cube)
{
	int i;

	i = 0;
	while (i < 8)
	{
		rotate_x(&cube->planes[i / 4].points[i % 4], cube->rotation.x);
		rotate_y(&cube->planes[i / 4].points[i % 4], cube->rotation.y);
		rotate_z(&cube->planes[i / 4].points[i % 4], cube->rotation.z);
		cube->planes[i / 4].points[i % 4] = vsum(cube->planes[i / 4].points[i % 4], cube->position);
		++i;
	}
}

void		add_other_dots(t_cube *cube)
{
	cube->planes[2].points[0] = cube->planes[0].points[0];
	cube->planes[2].points[1] = cube->planes[1].points[0];
	cube->planes[2].points[2] = cube->planes[1].points[1];
	cube->planes[2].points[3] = cube->planes[0].points[1];
	cube->planes[3].points[0] = cube->planes[0].points[3];
	cube->planes[3].points[1] = cube->planes[1].points[3];
	cube->planes[3].points[2] = cube->planes[1].points[2];
	cube->planes[3].points[3] = cube->planes[0].points[2];
	cube->planes[4].points[0] = cube->planes[0].points[0];
	cube->planes[4].points[1] = cube->planes[1].points[0];
	cube->planes[4].points[2] = cube->planes[1].points[3];
	cube->planes[4].points[3] = cube->planes[0].points[3];
	cube->planes[5].points[0] = cube->planes[0].points[1];
	cube->planes[5].points[1] = cube->planes[1].points[1];
	cube->planes[5].points[2] = cube->planes[1].points[2];
	cube->planes[5].points[3] = cube->planes[0].points[2];
}

void		count_planes(t_cube *cube)
{
	int i;

	find_first_dots(-1, 0, cube);
	find_first_dots(1, 1, cube);
	cube->rotation = vk_multiple(cube->rotation, 3.14f / 180);
	rotate_cube(cube);
	add_other_dots(cube);
	i = 0;
	while (i < 6)
	{
			cube->planes[i].normale = count_triangle_normale(cube->planes[i].points);
			++i;
	}
}

t_figure	*cube_init(t_vector vector[3], int color, double reflection)
{
	t_figure	*new_figure;
	t_cube		*cube;

	// printf("AAA\n");
	new_figure = (t_figure*)malloc(sizeof(t_figure));
	cube = (t_cube*)malloc(sizeof(t_cube));
	new_figure->type = Cube;
	new_figure->figure = cube;
	cube->position = vector[0];
	cube->rotation = vector[1];
	cube->scale = vector[2];
	count_planes(cube);
	new_figure->color = color;
	new_figure->reflection = reflection;
	new_figure->next = NULL;
	return (new_figure);
}
