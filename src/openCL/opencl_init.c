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
  "kernel void kernel_rt(     			\n" \
  "		 unsigned int width, 			\n" \
  "		 unsigned int height, 			\n" \
  "		 size_t figures_num, 			\n" \
  "		 size_t lights_num, 			\n" \
  "      __global t_cl_figure *figures, \n" \
  "      __global t_cl_light *light,    \n" \
  "      __global float *cam_v,   	    \n" \
  "      __global float *cam_o,  		\n" \
  "      __global unsigned int *output){\n" \
  " unsigned int x = get_global_id(0);  \n" \
  " unsigned int y = get_global_id(1);  \n" \
  " unsigned int color;                 \n" \
  " color = do_rt(x, y, width, height,  \n" \
  "	  figures, light, cam_v, cam_o,     \n" \
  "	  figures_num, lights_num);			\n" \
  " output[y * width + x] = color;}     \n";
  return (ft_strdup(kernel));
}

void	opencl_init2(t_view *v)
{
	v->cl.values_number = WIDTH * HEIGHT;
	v->cl.buffers_size = v->cl.values_number * sizeof(unsigned int);

	printf("Initialization of output data...\n");
	v->cl.output_buffer = clCreateBuffer(v->cl.context, CL_MEM_READ_WRITE,
						v->cl.buffers_size, NULL, &v->cl.result);

	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while initializing output data");

	printf("Setting kernel arguments...\n");
    set_arguments(v);

	printf("Execution of the kernel...\n");
	v->cl.global_work_size = v->cl.values_number;
	if ((v->cl.result = clGetKernelWorkGroupInfo(v->cl.kernel, v->cl.device_ids[0], CL_KERNEL_WORK_GROUP_SIZE,
				sizeof(v->cl.local_work_size), &v->cl.local_work_size, NULL)) != CL_SUCCESS)
		opencl_errors("Error while getting maximum work group size");
	if (v->cl.local_work_size > v->cl.values_number)
		v->cl.local_work_size  = v->cl.values_number;
	if ((v->cl.result = clEnqueueNDRangeKernel(v->cl.commands, v->cl.kernel, 1, NULL, &v->cl.global_work_size,
				&v->cl.local_work_size, 0, NULL, &v->cl.kernel_exec_event)) != CL_SUCCESS)
		opencl_errors("Error while executing the kernel");
	if ((v->cl.result = clFinish(v->cl.commands)) != CL_SUCCESS)
		opencl_errors("Failed to finish");
	printf("Getting back the results...\n");
	clEnqueueReadBuffer(v->cl.commands, v->cl.output_buffer, CL_TRUE, 0, v->cl.buffers_size,
						v->buff, 0, NULL, &v->cl.read_results_event);
}

void	opencl_init(t_view *v)
{
	char*		kernel_bytes;

	kernel_bytes = get_kernel();
	printf("Getting available platforms...\n");
	v->cl.platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id));
	if ((v->cl.result = clGetPlatformIDs(1, v->cl.platforms, &v->cl.num_platforms)) != CL_SUCCESS)
		opencl_errors("Error while getting available platforms");

	printf("Getting available GPU devices...\n");
	v->cl.device_ids = (cl_device_id*)malloc(sizeof(cl_device_id));
	if ((v->cl.result = clGetDeviceIDs(v->cl.platforms[0], CL_DEVICE_TYPE_GPU, 1, v->cl.device_ids, &v->cl.num_devices)) != CL_SUCCESS)
		opencl_errors("Error while getting available devices");

	printf("Creation of the OpenCL context...\n");
	v->cl.context = clCreateContext(NULL, 1, v->cl.device_ids, NULL, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the OpenCL context");

	printf("Creation of the command queue...\n");
	v->cl.commands = clCreateCommandQueue(v->cl.context, v->cl.device_ids[0], 0, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the command queue");

	printf("Creation of the program...\n");
	v->cl.program = clCreateProgramWithSource(v->cl.context, 1, (const char**)&kernel_bytes, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the program");

	printf("Compilation of the program...\n\n");
	if ((v->cl.result = clBuildProgram(v->cl.program, 0, NULL, "-I src/opencl_src", NULL, NULL)) != CL_SUCCESS)
		opencl_errors("Error while compiling the program");

	printf("Creation of the kernel...\n");
	v->cl.kernel = clCreateKernel(v->cl.program, "kernel_rt", &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the kernel");

	opencl_init2(v);
	cl_releasing(v);
}
