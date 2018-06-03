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

void	cl_releasing(t_view *v)
{
	printf("Releasing...\n");
	clReleaseMemObject(v->cl.output_buffer);
	clReleaseKernel(v->cl.kernel);
	clReleaseProgram(v->cl.program);
	clReleaseCommandQueue(v->cl.commands);
	clReleaseContext(v->cl.context);
}

void 	cl_set_arg(t_view *v, void *arg, size_t arg_size, cl_uint id)
{
	v->cl.result = clSetKernelArg(v->cl.kernel, id, arg_size, arg);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while setting kernel argument");
}

void 	cl_set_mem_arg(t_view *v, void *arg, size_t arg_size, cl_uint id)
{
	cl_mem set_arg;

	set_arg = clCreateBuffer(v->cl.context, CL_MEM_WRITE_ONLY, arg_size,
														NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while initializing argument");
	v->cl.result = clEnqueueWriteBuffer (v->cl.commands, set_arg, CL_TRUE, 0,
		arg_size, arg, 0, NULL, NULL);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating buffer");
	v->cl.result = clSetKernelArg(v->cl.kernel, id, sizeof(cl_mem), &set_arg);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while setting kernel argument");
}
