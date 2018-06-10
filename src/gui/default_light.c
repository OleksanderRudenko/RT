/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:02:35 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/07 15:02:37 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		default_helper_lights(t_view *view, t_light *light)
{
	size_t	i;

	i = 0;
	while (i < view->lights_num)
	{
		view->space->cl_ligtmp[i] = view->space->cl_lights[i];
		i++;
	}
	clean_light(view);
	add_light(light, view);
	if (view->space->cl_lights)
	{
		free(view->space->cl_lights);
	}
	view->space->cl_lights = copy_light(view);
	i = 0;
	while (i < (view->lights_num - 1))
	{
		view->space->cl_lights[i] = view->space->cl_ligtmp[i];
		i++;
	}
	free(view->space->cl_ligtmp);
	view->space->cl_ligtmp = copy_light(view);
	light_list_init(view);
	opencl_init2(view);
}

void		default_am_light(t_view *view)
{
	t_light *new_light;

	new_light = (t_light*)ft_memalloc(sizeof(t_light));
	new_light->type = LIGHT_TYPE_AMBIENT;
	new_light->inten = 0.01;
	new_light->next = NULL;
	default_helper_lights(view, new_light);
}

void		default_point_light(t_view *view)
{
	t_light *new_light;

	new_light = (t_light*)ft_memalloc(sizeof(t_light));
	new_light->type = LIGHT_TYPE_POINT;
	new_light->o = (t_vector){0.0, -10, 1};
	new_light->inten = 0.05;
	new_light->next = NULL;
	default_helper_lights(view, new_light);
}

void		default_dir_light(t_view *view)
{
	t_light *new_light;

	new_light = (t_light*)ft_memalloc(sizeof(t_light));
	new_light->type = LIGHT_TYPE_DIRECT;
	new_light->d = (t_vector){0.0, -10, 1};
	new_light->inten = 0.05;
	new_light->next = NULL;
	default_helper_lights(view, new_light);
}
