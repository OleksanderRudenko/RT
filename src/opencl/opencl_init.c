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

typedef struct __attribute__ ((packed)) _st_foo
{
    cl_float	x;
	cl_float	y;
	cl_float	z;
}										st_foo;

void	opencl_errors(const char *msg)
{
	ft_putendl(msg);
	exit(1);
}

static char	*read_kernel(char **data)
{
	char	*to_del;
	char	*line;
	int		fd;
	int		ret;

	fd = open("./rt_kernel.cl", O_RDONLY);
	*data = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(*data))
			data = ft_strdup(line);
		else
		{
			to_del = *data;
			*data = ft_strjoin(to_del, line);
			ft_strdel(&to_del);
		}
		ft_strdel(&line);
	}
	if (ret == -1)
	{
		ft_putendl("Kernel file error");
		exit(0);
	}
	close(fd);
}

void	getting_results(t_view *v)
{
	//	printf("Getting back the results...\n");

	int *result_array;

	result_array = (int*)malloc(sizeof(int) * WIDTH * HEIGHT);
	//Execution
	clEnqueueReadBuffer(v->cl.commands, v->cl.output_buffer, CL_TRUE, 0, v->cl.buffers_size,
					result_array, 0, NULL, &v->cl.read_results_event);
	/*=======results====*/

	printf("Releasing...\n");

	clReleaseMemObject(v->cl.output_buffer);
	clReleaseKernel(v->cl.kernel);
	clReleaseProgram(v->cl.program);
	clReleaseCommandQueue(v->cl.commands);
	clReleaseContext(v->cl.context);
}

void	opencl_init2(t_view *v)
{
	v->cl.values_number = HEIGHT * WIDTH;
	v->cl.buffers_size = numberOfValues * sizeof(int);

//	printf("Initialization of output data...\n");
	v->cl.outputBuffer = clCreateBuffer(v->cl.context, CL_MEM_WRITE_ONLY,
						v->cl.buffers_size, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while initializing output data");

//	printf("Setting kernel arguments...\n");
	v->cl.result = 0;
	v->cl.result |= clSetKernelArg(v->cl.kernel, 0, sizeof(cl_mem), &outputBuffer);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while setting kernel arguments");

//	printf("Execution of the kernel...\n");
	v->cl.global_work_size = v->cl.values_number;	
	if ((v->cl.result = clGetKernelWorkGroupInfo(v->cl.kernel, v->cl.device_ids[0], CL_KERNEL_WORK_GROUP_SIZE,
				sizeof(v->cl.local_work_size), &v->cl.local_work_size, NULL)) != CL_SUCCESS)
		opencl_errors("Error while getting maximum work group size");
	if (v->cl.local_work_size > v->cl.values_number)
		v->cl.local_work_size  = v->cl.values_number;
	if ((v->cl.result = clEnqueueNDRangeKernel(v->cl.commands, v->cl.kernel, 1, NULL, v->cl.global_work_size,
				&v->cl.local_work_size, 0, NULL, &v->cl.kernel_exec_event)) != CL_SUCCESS)
		opencl_errors("Error while executing the kernel");
	if ((v->cl.result= clFinish(commands)) != CL_SUCCESS)
		opencl_errors("Failed to finish");
}

void	opencl_init(t_view *v)
{
	char*		kernelBytes;

	read_kernel(&kernelBytes);
//	printf("Getting available platforms...\n");
	v->cl.platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id));
	if ((v->cl.result = clGetPlatformIDs(1, v->cl.platforms, &v->cl.numPlatforms)) != CL_SUCCESS)
		opencl_errors("Error while getting available platforms");

//	printf("Getting available GPU devices...\n");
	v->cl.device_ids = (cl_device_id*)malloc(sizeof(cl_device_id));
	if ((v->cl.result = clGetDeviceIDs(v->cl.platforms[0], CL_DEVICE_TYPE_GPU, 1, v->cl.device_ids, &v->cl.num_devices)) != CL_SUCCESS)
		opencl_errors("Error while getting available devices");

//	printf("Creation of the OpenCL context...\n");
	v->cl.context = clCreateContext(NULL, 1, v->cl.device_ids, NULL, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the OpenCL context");

//	printf("Creation of the command queue...\n");
	v->cl.commands = clCreateCommandQueue(v->cl.context, deviceIDs[0], 0, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the command queue");

	printf("Creation of the program...\n");
	printf("source:\n%s\n", kernelBytes);
// 	v->cl.program = clCreateProgramWithSource(v->cl.context, 1, (const char**)&kernelBytes, NULL, &v->cl.result);
// 	if (v->cl.result != CL_SUCCESS)
// 		opencl_errors("Error while creating the program");

// //	printf("Compilation of the program...\n");
// 	if ((v->cl.result = clBuildProgram(v->cl.program, 0, NULL, NULL, NULL, NULL)) != CL_SUCCESS)
// 		opencl_errors("Error while compiling the program");

// //	printf("Creation of the kernel...\n");
// 	v->cl.kernel = clCreateKernel(v->cl.program, "rt", &v->cl.result);
// 	if (v->cl.result != CL_SUCCESS)
// 		opencl_errors("Error while creating the kernel");

// 	opencl_init2(v);
// 	getting_results(v);
} 

