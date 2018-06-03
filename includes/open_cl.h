/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_cl.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:51:33 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 14:51:35 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_CL_H
# define OPEN_CL_H

// #ifdef cl_khr_byte_addressable_store
// 	#pragma OPENCL EXTENSION cl_khr_byte_addressable_store : enable
// #endif
// #ifdef cl_khr_fp64
// 	#pragma OPENCL EXTENSION cl_khr_fp64 : enable
// #elif defined(cl_amd_fp64)
// 	#pragma OPENCL EXTENSION cl_amd_fp64 : enable
// #endif

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
	float				reflection;

	cl_float3			start;
	cl_float3			vector;
	cl_float3			normale;
	cl_float3			point;
	cl_float3			center;
	cl_float3  			position;
	cl_float3  			rotation;
	cl_float3  			vertex;
	/*triangle*/
	cl_float3			t_points[3];
	/*quadrate*/
	cl_float3			q_points[4];
	/*cube*/
	cl_float3			c_points[24];
	cl_float3 			c_normale[6];
	cl_float3			scale;

	/*capses*/
	float 			caps1;
	float 			caps2;
	int 				color_c1;
	int 				color_c2;
	int 				color_f;

	float				radius;
	float				rdistance;
	float				radius_s;
	float				radius_b;
}						t_cl_figure;

typedef struct			s_opencl
{
	cl_int 				result;
	cl_platform_id     *platforms;          //List of platforms IDs
	cl_uint             num_platforms;		//The actual number of returned platform IDs
	cl_device_id       *device_ids;         //List of device IDs
	cl_uint             num_devices;        //The actual number of returned device IDs returned
	cl_uint 			max_work_dim;
	size_t 				*max_work_items_size;
	cl_context 			context;
	cl_command_queue 	commands;
	cl_program 			program;
	cl_kernel 			kernel;
	size_t 				values_number;
	size_t 				buffers_size;
	cl_mem 				output_buffer;
	size_t    			*global_work_size;  	//Number of values for each dimension we use
	size_t    			local_work_size;    //Size of a work-group in each dimension
	cl_event  			kernel_exec_event;
	cl_event    		read_results_event;
}						t_opencl;

#endif
