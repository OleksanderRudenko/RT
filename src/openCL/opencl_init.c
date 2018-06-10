/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 12:50:43 by knovytsk          #+#    #+#             */
/*   Updated: 2018/06/10 12:12:52 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		opencl_errors(cl_int result, const char *msg)
{
	if (result != CL_SUCCESS)
	{
		ft_putendl(msg);
		exit(1);
	}
}

static char	*get_kernel(void)
{
	return (ft_strdup("\n" \
	"#include \"rt_h.cl\"\n#include \"color.cl\"\n" \
	"#include \"do_rt.cl\"\n#include \"figure.cl\"\n" \
	"#include \"space.cl\"\n#include \"vector.cl\"\n" \
	"#include \"fcylinder.cl\"\n" \
	"#include \"fplane.cl\"\n#include \"fsphere.cl\"\n" \
	"#include \"fcone.cl\"\n" \
	"#include \"felipsoid.cl\"\n" \
	"#include \"fparaboloid.cl\"\n" \
	"#include \"ftriangle.cl\"\n" \
	"#include \"fquadrate.cl\"\n" \
	"#include \"fcube.cl\"\n" \
	"#include \"kernel.cl\"\n" \
	"#include \"textures.cl\"\n"));
}

void		opencl_init2(t_view *v)
{
	set_arguments(v);
	v->cl.result = clEnqueueNDRangeKernel(v->cl.commands, v->cl.kernel,
			v->cl.max_work_dim - 1, NULL, v->cl.global_work_size,
			NULL, 0, 0, NULL);
	opencl_errors(v->cl.result, "Error while executing the kernel");
	v->cl.result = clFinish(v->cl.commands);
	opencl_errors(v->cl.result, "Failed to finish");
	if (v->server_client == Client)
		clEnqueueReadBuffer(v->cl.commands, v->cl.output_buffer,
			CL_TRUE, 0, v->cl.buffers_size / 2, v->buff, 0, NULL, NULL);
	else
		clEnqueueReadBuffer(v->cl.commands, v->cl.output_buffer,
			CL_TRUE, 0, v->cl.buffers_size, v->buff, 0, NULL, NULL);
	opencl_errors(v->cl.result, "Failed to read output buffer");
	color_effects(v);
}

void		get_devices(t_view *v)
{
	size_t ret_size;

	v->cl.platforms = (cl_platform_id*)malloc(sizeof(cl_platform_id));
	v->cl.result = clGetPlatformIDs(1, v->cl.platforms, &v->cl.num_platforms);
	opencl_errors(v->cl.result, "Error while getting available platforms");
	v->cl.device_ids = (cl_device_id*)malloc(sizeof(cl_device_id));
	v->cl.result = clGetDeviceIDs(v->cl.platforms[0], CL_DEVICE_TYPE_ALL, 1,
									v->cl.device_ids, &v->cl.num_devices);
	opencl_errors(v->cl.result, "Error while getting available devices");
	v->cl.result = clGetDeviceInfo(v->cl.device_ids[0],
		CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint),
									&v->cl.max_work_dim, &ret_size);
	opencl_errors(v->cl.result, "Error while getting device info");
	v->cl.context = clCreateContext(NULL, 1, v->cl.device_ids, NULL, NULL,
									&v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the OpenCL context");
}

void		opencl_init(t_view *v)
{
	char	*kernel_bytes;

	kernel_bytes = get_kernel();
	v->cl.buffers_size = WIDTH * HEIGHT * sizeof(unsigned int);
	v->cl.global_work_size[0] = WIDTH;
	v->cl.global_work_size[1] = HEIGHT;
	get_devices(v);
	v->cl.commands = clCreateCommandQueue(v->cl.context, v->cl.device_ids[0],
									0, &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the command queue");
	v->cl.program = clCreateProgramWithSource(v->cl.context, 1,
							(const char**)&kernel_bytes, NULL, &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the program");
	v->cl.result = clBuildProgram(v->cl.program, 0, NULL, "-I src/opencl_src",
									NULL, NULL);
	opencl_errors(v->cl.result, "Error while compiling the program");
	v->cl.kernel = clCreateKernel(v->cl.program, "kernel_rt", &v->cl.result);
	opencl_errors(v->cl.result, "Error while creating the kernel");
	v->cl.output_buffer = clCreateBuffer(v->cl.context, CL_MEM_READ_WRITE,
									v->cl.buffers_size, NULL, &v->cl.result);
	opencl_errors(v->cl.result, "Error while initializing output data");
	opencl_init2(v);
	ft_strdel(&kernel_bytes);
}
