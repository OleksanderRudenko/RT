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

void		opencl_errors(const char *msg)
{
	ft_putendl(msg);
	exit(1);
}

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

/* MAX WORK DIM : 3 */
/* MAX COMPUTE UNITS: 12 */
/* MAX WORK ITEMS: 256 */
/* MAX WORK GROUP SIZE: 256 */
/* CL_EXEC_KERNEL – The OpenCL device can execute OpenCL kernels. */
/* DEVICE NAME: AMD Radeon R9 M380 Compute Engine */

void 	get_execution_time(t_view *v)
{
	cl_ulong	time_start;
	cl_ulong	time_end;

	clGetEventProfilingInfo(v->cl.read_results_event, CL_PROFILING_COMMAND_START,
										sizeof(time_start), &time_start, NULL);
	clGetEventProfilingInfo(v->cl.read_results_event, CL_PROFILING_COMMAND_END,
											sizeof(time_end), &time_end, NULL);
	printf("time->%f sec\n", (float)(time_end - time_start) * 1e-9);
}

void	opencl_init2(t_view *v)
{
    set_arguments(v);
	if ((v->cl.result = clEnqueueNDRangeKernel(v->cl.commands, v->cl.kernel, 2, NULL, v->cl.global_work_size,
				NULL, 0, NULL, &v->cl.kernel_exec_event)) != CL_SUCCESS)
		opencl_errors("Error while executing kernel");
	uint   time = SDL_GetTicks();

	if ((clEnqueueReadBuffer(v->cl.commands, v->cl.output_buffer, CL_TRUE, 0, v->cl.buffers_size,
						v->buff, 0, NULL, NULL)) != CL_SUCCESS)
		opencl_errors("Error while getting results");

	printf("%.3f\n", (SDL_GetTicks() - time) / 1000.0F);
	// get_execution_time(v);
}

void	opencl_init(t_view *v)
{
	char*		kernel_bytes;
	size_t 		ret_size;

	kernel_bytes = get_kernel();
	// printf("Getting available platforms...\n");
	v->cl.platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id));
	if ((v->cl.result = clGetPlatformIDs(1, v->cl.platforms, &v->cl.num_platforms)) != CL_SUCCESS)
		opencl_errors("Error while getting available platforms");

	// printf("Getting available GPU devices...\n");
	v->cl.device_ids = (cl_device_id*)malloc(sizeof(cl_device_id));
	if ((v->cl.result = clGetDeviceIDs(v->cl.platforms[0], CL_DEVICE_TYPE_ALL, 1, v->cl.device_ids, &v->cl.num_devices)) != CL_SUCCESS)
		opencl_errors("Error while getting available devices");

	v->cl.result = clGetDeviceInfo(v->cl.device_ids[0],
		CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &v->cl.max_work_dim, &ret_size);
	v->cl.global_work_size[0] = WIDTH;
	v->cl.global_work_size[1] = HEIGHT;
	// printf("Creation of the OpenCL context...\n");
	v->cl.context = clCreateContext(NULL, 1, v->cl.device_ids, NULL, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the OpenCL context");

	// printf("Creation of the command queue...\n");
	v->cl.commands = clCreateCommandQueue(v->cl.context, v->cl.device_ids[0], CL_QUEUE_PROFILING_ENABLE, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the command queue");

	// printf("Creation of the program...\n");
	v->cl.program = clCreateProgramWithSource(v->cl.context, 1, (const char**)&kernel_bytes, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the program");

	// printf("Compilation of the program...\n\n");
	if ((v->cl.result = clBuildProgram(v->cl.program, 0, NULL,
	"-I src/opencl_src -cl-fast-relaxed-math -cl-finite-math-only", NULL, NULL)) != CL_SUCCESS)
		opencl_errors("Error while compiling the program");

	// printf("Creation of the kernel...\n");
	v->cl.kernel = clCreateKernel(v->cl.program, "kernel_rt", &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the kernel");

	v->cl.values_number = WIDTH * HEIGHT;
	v->cl.buffers_size = v->cl.values_number * sizeof(unsigned int);

	// printf("Initialization of output data...\n");
	v->cl.output_buffer = clCreateBuffer(v->cl.context, CL_MEM_READ_WRITE,
					v->cl.buffers_size, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while initializing output data");
	opencl_init2(v);
	// cl_releasing(v);
}
