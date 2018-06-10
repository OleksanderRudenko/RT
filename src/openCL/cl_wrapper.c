/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_wrapper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:39:31 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 12:16:56 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cl_arg_releasing(t_view *v)
{
	int i;

	i = -1;
	while (++i < 2)
		clReleaseMemObject(v->cl.args[i]);
	clReleaseMemObject(v->cl.output_buffer);
}

void	cl_releasing(t_view *v)
{
	cl_arg_releasing(v);
	clReleaseKernel(v->cl.kernel);
	clReleaseProgram(v->cl.program);
	clReleaseCommandQueue(v->cl.commands);
	clReleaseContext(v->cl.context);
}

void	cl_set_arg(t_view *v, void *arg, size_t arg_size, cl_uint id)
{
	v->cl.result = clSetKernelArg(v->cl.kernel, id, arg_size, arg);
	opencl_errors(v->cl.result, "Error while setting kernel argument");
}

void	cl_set_mem_arg(t_view *v, void *arg, size_t arg_size, cl_uint id)
{
	v->cl.args[id - 2] = clCreateBuffer(v->cl.context, CL_MEM_READ_WRITE,
								arg_size, NULL, &v->cl.result);
	opencl_errors(v->cl.result, "Error while initializing argument");
	v->cl.result = clEnqueueWriteBuffer(v->cl.commands,
		v->cl.args[id - 2], CL_TRUE, 0, arg_size, arg, 0, NULL, NULL);
	opencl_errors(v->cl.result, "Error while creating buffer");
	v->cl.result = clSetKernelArg(v->cl.kernel, id,
								sizeof(cl_mem), &v->cl.args[id - 2]);
	opencl_errors(v->cl.result, "Error while setting kernel argument");
}
