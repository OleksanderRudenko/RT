/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/11 12:50:44 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char *get_kernel(void)
{
  const char  *kernel = "\n" \
  "#include \"rt_h.cl\"\n#include \"color.cl\"\n" \
  "#include \"do_rt.cl\"\n#include \"figure.cl\"\n" \
  "#include \"space.cl\"\n#include \"vector.cl\"\n" \
  "#include \"fcylinder.cl\"\n" \
  "#include \"fplane.cl\"\n#include \"fsphere.cl\"\n" \
  "#include \"kernel.cl\"\n";
  return (ft_strdup(kernel));
}

void		opencl_init2(t_view *v)
{
    set_arguments(v);
	v->cl.result = clEnqueueNDRangeKernel(v->cl.commands, v->cl.kernel,
				2, 0, v->cl.global_work_size, 0, 0, 0, 0);
	opencl_errors(v->cl.result, "Error while executing kernel");
	v->cl.result = clEnqueueReadBuffer(v->cl.commands, v->cl.set_arg[0],
		CL_TRUE, 0, v->cl.buffer_size, v->buff, 0, 0, 0);
	opencl_errors(v->cl.result, "Error while getting results");
}

void		opencl_init(t_view *v)
{
	v->cl.kernel_bytes = get_kernel();
	v->cl.buffer_size = sizeof(unsigned int) * (WIDTH * HEIGHT);
	v->cl.result = clGetPlatformIDs(1, v->cl.platforms, &v->cl.num_platforms);
	opencl_errors(v->cl.result, "Error while getting available platforms");
	v->cl.result = clGetDeviceIDs(v->cl.platforms[0], CL_DEVICE_TYPE_ALL,
								1, v->cl.device_ids, &v->cl.num_devices);
	opencl_errors(v->cl.result, "Error while getting available devices");
	cl_info(v);
	v->cl.context = clCreateContext(0, 1, v->cl.device_ids, 0, 0, &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the OpenCL context");
	v->cl.commands = clCreateCommandQueue(v->cl.context, v->cl.device_ids[0],
														0, &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the command queue");
	v->cl.program = clCreateProgramWithSource(v->cl.context, 1,
					(const char**)&v->cl.kernel_bytes, NULL, &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the program");
	v->cl.result = clBuildProgram(v->cl.program, 0, 0,
	"-I src/opencl_src -cl-fast-relaxed-math -cl-finite-math-only", 0, 0);
	opencl_errors(v->cl.result, "Error while compiling the program");
	v->cl.kernel = clCreateKernel(v->cl.program, "kernel_rt", &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the kernel");
	v->cl.set_arg[0] = clCreateBuffer(v->cl.context, CL_MEM_READ_WRITE,
										v->cl.buffer_size, 0, &v->cl.result);
	opencl_errors(v->cl.result, "Error while initializing output data");
	opencl_init2(v);
}
