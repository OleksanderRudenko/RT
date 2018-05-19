/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_set_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:45:18 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 14:45:20 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void 	set_dimension(t_view *v)
{
	unsigned int width;
	unsigned int height;

	width = (unsigned int)WIDTH;
	height = (unsigned int)HEIGHT;
	cl_set_arg(v, &width, sizeof(unsigned int), 0);
	cl_set_arg(v, &height, sizeof(unsigned int), 1);
}

void 			set_arguments(t_view *v)
{
	t_cl_light 	*lights;
	t_cl_figure *figures;
	float 		cam_o[3];
	float 		cam_v[3];

	lights = copy_light(v);
	figures = copy_figures(v);
	set_dimension(v);
	init_cam(v, cam_o, cam_v);
	cl_set_arg(v, &v->figures_num, sizeof(size_t), 2);
	cl_set_arg(v, &v->lights_num, sizeof(size_t), 3);
	cl_set_mem_arg(v, figures, (sizeof(t_cl_figure) * v->figures_num), 4);
	cl_set_mem_arg(v, lights, (sizeof(t_cl_light) * v->lights_num), 5);
	cl_set_mem_arg(v, &cam_v, sizeof(float) * 3, 6);
	cl_set_mem_arg(v, &cam_o, sizeof(float) * 3, 7);
	cl_set_arg(v, &v->cl.output_buffer, sizeof(cl_mem), 8);
}
