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

#ifdef cl_khr_fp64
	#pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
	#pragma OPENCL EXTENSION cl_amd_fp64 : enable
#endif

void	opencl_errors(const char *msg)
{
	ft_putendl(msg);
	exit(1);
}

static char 	*get_kernel(void)
{
  const char  *kernel = "\n" \
  "#include \"rt_h.cl\"\n#include \"color.cl\"\n" \
  "#include \"do_rt.cl\"\n#include \"figure.cl\"\n" \
  "#include \"space.cl\"\n#include \"vector.cl\"\n" \
  "#include \"fcone.cl\"\n#include \"fcylinder.cl\"\n" \
  "#include \"fplane.cl\"\n#include \"fsphere.cl\"\n" \
  "#include \"ftriangle.cl\"\n"
  "kernel void kernel_rt(     					\n" \
	"			 unsigned int width, 						\n" \
	"			 unsigned int height, 					\n" \
  "      __global t_figure *figure,     \n" \
  "      __global t_cl_light *light,    \n" \
  "      __global float *cam_v,   	    \n" \
  "      __global float *cam_o,  		    \n" \
  "      __global unsigned int *output){\n" \
  " unsigned int x = get_global_id(0);  \n" \
  " unsigned int y = get_global_id(1);  \n" \
	// " x = x % width; 											\n" \
	// " y = x / width; 											\n" \
  // " size_t width = get_global_size(0);  \n" \
  // " size_t height = get_global_size(1); \n"
  " unsigned int color;                 \n" \
  " color = do_rt(x, y, width, height, figure, light, cam_v, cam_o);\n" \
  " output[y * width + x] = color;}     \n";
  return (ft_strdup(kernel));
}

void	getting_results(t_view *v)
{
		printf("Getting back the results...\n");

	unsigned int *result_array;

	result_array = (unsigned int*)malloc(sizeof(unsigned int) * WIDTH * HEIGHT);

	// double *result_array;

	// 	result_array = (double*)malloc(sizeof(double) * WIDTH * HEIGHT);
	//Execution
	clEnqueueReadBuffer(v->cl.commands, v->cl.output_buffer, CL_TRUE, 0, v->cl.buffers_size,
					v->buff, 0, NULL, &v->cl.read_results_event);
	/*=======results====*/
	// int i = 0;
	// while (i < WIDTH)
	// {
	// 	printf("%#x\n", v->buff[i]);
	// 	i++;
	// }

	printf("Releasing...\n");

	clReleaseMemObject(v->cl.output_buffer);
	clReleaseKernel(v->cl.kernel);
	clReleaseProgram(v->cl.program);
	clReleaseCommandQueue(v->cl.commands);
	clReleaseContext(v->cl.context);
}

void 	cl_set_arg(t_view *v, void *arg, size_t arg_size, cl_uint index)
{
	cl_mem arg_to_set;

	arg_to_set = clCreateBuffer(v->cl.context, CL_MEM_WRITE_ONLY, arg_size, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while initializing argument");
	v->cl.result = clEnqueueWriteBuffer (v->cl.commands, arg_to_set, CL_TRUE, 0,
		arg_size, arg, 0, NULL, NULL);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating buffer");
	v->cl.result = clSetKernelArg(v->cl.kernel, index, sizeof(cl_mem), &arg_to_set);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while setting kernel argument");
}

t_cl_light *copy_light(t_view *v)
{
	t_cl_light *light;
	// int n;
	t_cl_light *head;
	t_light 	*tmp;

	tmp = v->space->lights;
	light = (t_cl_light*)malloc(sizeof(t_cl_light));
	// n = 0;
	// while (tmp)
	// {
	// 	light[n].origin.x = tmp->o.x;
	// 	light[n].origin.y = tmp->o.y;
	// 	light[n].origin.z = tmp->o.z;
	// 	light[n].inten = tmp->inten;
	// 	light[n].type = tmp->type;
	// 	tmp = tmp->next;
	// 	n++;
	// }
	// n = 0;
	// while (n < 2)
	// {
	// 	printf("inten -> %f origin (%f %f %f) type->%i\n", light[n].inten, light[n].origin.x,
	// 										light[n].origin.y, light[n].origin.z, light[n].type);
	// 	n++;
	// }
	head = light;
	light->origin.x = tmp->o.x;
	light->origin.y = tmp->o.y;
	light->origin.z = tmp->o.z;
	light->inten = tmp->inten;
	light->type = tmp->type;
	light->next = NULL;
	tmp = tmp->next;
	while (tmp)
	{
		light = head;
		while (light->next)
			light = light->next;
		light->next = (t_cl_light*)malloc(sizeof(t_cl_light));
		light->next->origin.x = tmp->o.x;
		light->next->origin.y = tmp->o.y;
		light->next->origin.z = tmp->o.z;
		light->next->inten = tmp->inten;
		light->next->type = tmp->type;
		light->next->next = NULL;
		tmp = tmp->next;
	}
	// t_cl_light *temp;
	// temp = light;
	// while (temp)
	// {
	// 	printf("inten -> %f origin (%f %f %f) type->%i\n", temp->inten, temp->origin.x,
	// 									temp->origin.y, temp->origin.z, temp->type);
	// 	temp = temp->next;
	// }
	return (light);
}

void set_arguments(t_view *v)
{
	t_cl_light *light;
	unsigned int width;
	unsigned int height;
	float cam_o[3];
	float cam_v[3];

	light = copy_light(v);
	cam_o[0] = v->space->cam->o.x;
	cam_o[1] = v->space->cam->o.y;
	cam_o[2] = v->space->cam->o.z;
	cam_v[0] = v->space->cam->v.x;
	cam_v[1] = v->space->cam->v.y;
	cam_v[2] = v->space->cam->v.z;
	// printf("cam origin (%f %f %f) cam vector (%f %f %f) \n", cam_o.x, cam_o.y, cam_o.z,
	// 																							cam_v.x, cam_v.y, cam_v.z);
	width = (unsigned int)WIDTH;
	height = (unsigned int)HEIGHT;
	v->cl.result = clSetKernelArg(v->cl.kernel, 0, sizeof(unsigned int), &width);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while setting kernel arguments");
	v->cl.result = clSetKernelArg(v->cl.kernel, 1, sizeof(unsigned int), &height);
		if (v->cl.result != CL_SUCCESS)
			opencl_errors("Error while setting kernel arguments");
	// cl_set_arg(v, &width, sizeof(unsigned int), 0);
	// cl_set_arg(v, &height, sizeof(unsigned int), 1);
	cl_set_arg(v, v->space->figures, sizeof(t_figure) * v->figures_num, 2);
	cl_set_arg(v, light, sizeof(t_cl_light) * v->lights_num, 3);
	cl_set_arg(v, &cam_v, sizeof(float) * 3, 4);
	cl_set_arg(v, &cam_o, sizeof(float) * 3, 5);
	v->cl.result = clSetKernelArg(v->cl.kernel, 6, sizeof(cl_mem), &v->cl.output_buffer);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while setting kernel arguments");
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
	if ((v->cl.result= clFinish(v->cl.commands)) != CL_SUCCESS)
		opencl_errors("Failed to finish");
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
	// printf("source:\n%s\n", kernel_bytes);
	v->cl.program = clCreateProgramWithSource(v->cl.context, 1, (const char**)&kernel_bytes, NULL, &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the program");

	printf("Compilation of the program...\n\n");
	// if ((v->cl.result = clBuildProgram(v->cl.program, 0, NULL, NULL, NULL, NULL)) != CL_SUCCESS)
	// 	opencl_errors("Error while compiling the program");
	v->cl.result = clBuildProgram(v->cl.program, 0, NULL, "-I src/opencl", NULL, NULL);
	cl_int result = v->cl.result;
  	/* DEBBUGING */
  	// char *log = (char*)malloc(sizeof(char) * 1000000);
  	// size_t ret;
  	// // cl_build_status stat = 0;

  	// clGetProgramBuildInfo(v->cl.program, v->cl.device_ids[0], CL_PROGRAM_BUILD_LOG, sizeof(char) * 1000000, (void*)log, &ret);
  //	clGetProgramBuildInfo(v->cl.program, v->cl.device_ids[0], CL_PROGRAM_BUILD_STATUS, sizeof(size_t), &stat, &ret);
 	// printf("\nlog: \n%s\n\n", log);
 	// if (stat == CL_BUILD_NONE)
 	// 	ft_putendl("CL_BUILD_NONE");
 	// if (stat == CL_BUILD_ERROR)
 	// 	ft_putendl("CL_BUILD_ERROR");
 	// if (stat == CL_BUILD_SUCCESS)
 	// 	ft_putendl("CL_BUILD_SUCCESS");
 	// if (stat == CL_BUILD_IN_PROGRESS)
 	// 	ft_putendl("CL_BUILD_IN_PROGRESS");
	if (result != CL_SUCCESS)
	{
	//	ft_putendl("Error while compiling the program");
		if (result == CL_INVALID_PROGRAM)
			ft_putendl("CL_INVALID_PROGRAM");
		if (result == CL_INVALID_VALUE)
			ft_putendl("CL_INVALID_VALUE");
		if (result == CL_INVALID_DEVICE)
			ft_putendl("CL_INVALID_DEVICE");
		if (result == CL_INVALID_BUILD_OPTIONS)
			ft_putendl("CL_INVALID_BUILD_OPTIONS");
		if (result == CL_INVALID_OPERATION)
			ft_putendl("CL_INVALID_OPERATION");
		if (result == CL_COMPILER_NOT_AVAILABLE)
			ft_putendl("CL_COMPILER_NOT_AVAILABLE");
		if (result == CL_BUILD_PROGRAM_FAILURE)
			ft_putendl("CL_BUILD_PROGRAM_FAILURE");
		if (result == CL_OUT_OF_RESOURCES)
			ft_putendl("CL_OUT_OF_RESOURCES");
		if (result == CL_OUT_OF_HOST_MEMORY)
			ft_putendl("CL_OUT_OF_HOST_MEMORY");
		ft_putendl("");
		exit(1);
	}


	printf("Creation of the kernel...\n");
	v->cl.kernel = clCreateKernel(v->cl.program, "kernel_rt", &v->cl.result);
	if (v->cl.result != CL_SUCCESS)
		opencl_errors("Error while creating the kernel");

	opencl_init2(v);
	getting_results(v);
}
