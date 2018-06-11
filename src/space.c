/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataranov <ataranov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 20:21:01 by ataranov          #+#    #+#             */
/*   Updated: 2018/06/11 20:28:43 by ataranov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		add_light(t_light *light, t_view *view)
{
	t_light *light1;

	view->lights_num++;
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

	view->figures_num++;
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

void		space_init(const char *filename, t_view *view)
{
	view->space = (t_space*)malloc(sizeof(t_space));
	view->space->cam = NULL;
	view->space->figures = NULL;
	view->space->lights = NULL;
	view->figures_num = 0;
	view->lights_num = 0;
	parse_scene(filename, view);
	if (view->space->cam == NULL)
		view->space->cam = ray_init((t_vector){0, 0, -10},
				(t_vector){0, 0, 0});
	view->space->cl_figures = copy_figures(view);
	view->space->cl_lights = copy_light(view);
	view->space->cl_figtmp = copy_figures(view);
	view->space->cl_ligtmp = copy_light(view);
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
