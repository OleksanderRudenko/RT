/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_set_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:45:18 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 12:16:16 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	set_arguments(t_view *v)
{
	cl_float3	cam_o;
	cl_float3	cam_v;

	init_cam(v, &cam_o, &cam_v);
	cl_set_arg(v, &v->figures_num, sizeof(size_t), 0);
	cl_set_arg(v, &v->lights_num, sizeof(size_t), 1);
	cl_set_mem_arg(v, v->space->cl_figures,
								(sizeof(t_cl_figure) * v->figures_num), 2);
	cl_set_mem_arg(v, v->space->cl_lights,
								(sizeof(t_cl_light) * v->lights_num), 3);
	cl_set_arg(v, &cam_v, sizeof(cl_float3), 4);
	cl_set_arg(v, &cam_o, sizeof(cl_float3), 5);
	cl_set_arg(v, &v->space->antialiasing, sizeof(int), 6);
	cl_set_mem_arg(v, v->array, (sizeof(unsigned int) * (1020 * 256 * 5)), 7);
	cl_set_arg(v, &v->cl.output_buffer, sizeof(cl_mem), 8);
	cl_set_arg(v, &v->server_client, sizeof(int), 9);
}
