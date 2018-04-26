/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 15:40:00 by abutok            #+#    #+#             */
/*   Updated: 2018/03/22 20:15:45 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_light(t_light *light, t_view *view)
{
	t_light *light1;

	if (view->space->lights == NULL)
	{
		view->space->lights = light;
		return ;
	}
	light1 = view->space->lights;
	while (light1->next != NULL)
		light1 = light1->next;
	light1->next = light;
}

void		add_figure(t_figure *figure, t_view *view)
{
	t_figure *figure1;

	if (view->space->figures == NULL)
	{
		view->space->figures = figure;
		return ;
	}
	figure1 = view->space->figures;
	while (figure1->next != NULL)
		figure1 = figure1->next;
	figure1->next = figure;
}

t_vector	get_intersection(t_ray *ray, double k)
{
	return (vsum(vk_multiple(ray->v, k), ray->o));
}

void		space_init(char *filename, t_view *view)
{
	view->space = (t_space*)malloc(sizeof(t_space));
	view->space->cam = NULL;
	view->space->figures = NULL;
	view->space->lights = NULL;
	parse_scene(filename, view);
	if (view->space->cam == NULL)
		view->space->cam = ray_init((t_vector){0, 0, -10},
				(t_vector){0, 0, 0});
}

void		cam_rotate(t_ray *ray, t_vector vector)
{
	vector = vk_multiple(vector, M_PI / 180);
	if (vector.x != 0)
		rotate_x(&ray->v, vector.x);
	if (vector.y != 0)
		rotate_y(&ray->v, vector.y);
	if (vector.z != 0)
		rotate_z(&ray->v, vector.z);
}
