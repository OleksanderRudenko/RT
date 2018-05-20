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

void 			set_arguments(t_view *v)
{
	float 		cam_o[3];
	float 		cam_v[3];

	init_cam(v, cam_o, cam_v);
	cl_set_arg(v, &v->figures_num, sizeof(size_t), 0);
	cl_set_arg(v, &v->lights_num, sizeof(size_t), 1);
	cl_set_mem_arg(v, v->space->cl_figures,
								(sizeof(t_cl_figure) * v->figures_num), 2);
	cl_set_mem_arg(v, v->space->cl_lights,
								(sizeof(t_cl_light) * v->lights_num), 3);
	cl_set_mem_arg(v, &cam_v, sizeof(float) * 3, 4);
	cl_set_mem_arg(v, &cam_o, sizeof(float) * 3, 5);
	cl_set_arg(v, &v->cl.output_buffer, sizeof(cl_mem), 6);	
}
