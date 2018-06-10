/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:51:33 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 20:37:24 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_CL_H
# define OPEN_CL_H

typedef struct			s_cl_light
{
	int					type;
	float				inten;
	cl_float3			origin;
	cl_float3			direction;
}						t_cl_light;

typedef struct			s_cl_figure
{
	int					type;
	int					color;
	int					mirror;
	int					texture;
	float				reflection;
	cl_float3			start;
	cl_float3			vector;
	cl_float3			normale;
	cl_float3			point;
	cl_float3			center;
	cl_float3			position;
	cl_float3			rotation;
	cl_float3			vertex;
	cl_float3			t_points[3];
	cl_float3			q_points[4];
	cl_float3			c_points[24];
	cl_float3			c_normale[6];
	cl_float3			scale;
	float				caps1;
	float				caps2;
	int					color_c1;
	int					color_c2;
	int					color_f;
	float				radius;
	float				rdistance;
	float				radius_s;
	float				radius_b;
	float				refract;
}						t_cl_figure;

typedef struct			s_opencl
{
	cl_int				result;
	cl_platform_id		*platforms;
	cl_uint				num_platforms;
	cl_device_id		*device_ids;
	cl_uint				num_devices;
	cl_uint				max_work_dim;
	cl_context			context;
	cl_command_queue	commands;
	cl_program			program;
	cl_kernel			kernel;
	size_t				buffers_size;
	cl_mem				args[2];
	cl_mem				output_buffer;
	size_t				global_work_size[2];
}						t_opencl;

void					rotate_figures(t_cl_figure *figure,
										float angle, int id);
void					change_pos(t_cl_figure *figure,
										float new_value, int id);
void					new_normal_triangle(t_cl_figure *figure);

#endif
