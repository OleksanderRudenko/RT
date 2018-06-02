/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:39:31 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 14:39:33 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	opencl_errors(cl_uint result, const char *msg)
{
	if (result != CL_SUCCESS)
	{
		ft_putendl(msg);
		exit(1);
	}
}

void	cl_releasing(t_view *v)
{
	int i;

	i = -1;
	while (++i < 3)
		clReleaseMemObject(v->cl.set_arg[i]);
	clReleaseKernel(v->cl.kernel);
	clReleaseProgram(v->cl.program);
	clReleaseCommandQueue(v->cl.commands);
	clReleaseContext(v->cl.context);
	ft_strdel(&v->cl.kernel_bytes);
}

void 	cl_info(t_view *v)
{
	size_t 	ret_size;

	v->cl.result = clGetDeviceInfo(v->cl.device_ids[0],
		CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint),
		&v->cl.max_work_dim, &ret_size);
	opencl_errors(v->cl.result, "Error while getting info about device");
	v->cl.global_work_size[0] = WIDTH;
	v->cl.global_work_size[1] = HEIGHT;
}

void 	cl_set_arg(t_view *v, void *arg, size_t arg_size, cl_uint id)
{
	v->cl.result = clSetKernelArg(v->cl.kernel, id, arg_size, arg);
	opencl_errors(v->cl.result, "Error while setting kernel argument");
}

void 	cl_set_mem_arg(t_view *v, void *arg, size_t arg_size, cl_uint id)
{
	static int 	i = 0;

	v->cl.set_arg[++i] = clCreateBuffer(v->cl.context,
		CL_MEM_READ_WRITE, arg_size, 0, &v->cl.result);
	opencl_errors(v->cl.result, "Error while initializing argument");
	v->cl.result = clEnqueueWriteBuffer (v->cl.commands, v->cl.set_arg[i],
								CL_TRUE, 0, arg_size, arg, 0, 0, 0);
	opencl_errors(v->cl.result, "Error while creating buffer");
	v->cl.result = clSetKernelArg(v->cl.kernel, id, sizeof(cl_mem),
												&v->cl.set_arg[i]);
	opencl_errors(v->cl.result, "Error while setting kernel argument");
}
