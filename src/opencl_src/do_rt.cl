
#include "rt_h.cl"

float			rt_lightr(float3 light, float3 normale, float3 view, float3 buf)
{
	float3		h;
	float		d;
	float 		a;

	h = sum(view, light);
	d = dot(h, normale);
	if (d > 0.0f)
	{
		a = d / fast_length(h);
		return (buf.x * pow(a, buf.y));
	}
	else
		return (0.0f);
}

t_lrt			tlrt_init(float3 ray_origin, float3 ray_vector, t_cl_figure figure, double k)
{
	t_lrt	var;

	var.intersection = get_intersection(ray_origin, ray_vector, k);
	var.normale = get_normale(var.intersection, figure);
	if (dot(var.normale, ray_vector) >= 0)
		var.normale = k_multiply(var.normale, -1.0f);
	var.bright = 0;
	var.reflected = 0;
	return (var);
}

unsigned int	do_lightrt(__global t_cl_light *lights,
						   __global t_cl_figure *figures,
						   t_cl_figure figure,
						   float3 ray_origin, float3 ray_vector, double k,
						   size_t figures_num, size_t lights_num)
{
	t_lrt	v;
	size_t 	n;
	float3 	buf;
	float3 	view;

	n = 0;
	v = tlrt_init(ray_origin, ray_vector, figure, k);
	while (n < lights_num)
	{
		if (lights[n].type == LIGHT_TYPE_AMBIENT)
			v.bright += lights[n].inten;
		else
		{
			v.vlight = subtraction(lights[n].origin, v.intersection);
			v.buf_origin = (float3)(v.intersection.x, v.intersection.y, v.intersection.z);
			v.buf_vector = (float3)(v.vlight.x, v.vlight.y, v.vlight.z);
			if (!(check_intersections(v.buf_origin, v.buf_vector, figures, figures_num, figure)))
			{
				if ((v.nl_s = dot(v.normale, v.vlight)) > 0.0f)
					v.bright += lights[n].inten * v.nl_s / fast_length(v.vlight);
				if (v.nl_s > 0.0f && figure.reflection > 0.0f)
				{
					buf = (float3)(lights[n].inten, figure.reflection, 0.0f);
					view = k_multiply(ray_vector, -1.0f);
					v.reflected += rt_lightr(v.vlight, v.normale, view, buf);
				}
			}
		}
		n++;
	}
	// if (v.bright >= 1)
	// {
	// 	printf("%f-v.bright", v.bright);
	// 	// exit(1);
	// }
	// if (v.reflected >= 1)
	// {
	// 	printf("%f-v.reflected", v.reflected);
	// 	// exit(1);
	// }
	return (set_brightness(figure.color, v.bright, v.reflected));
}

unsigned int	rt(__global t_cl_light *lights, __global t_cl_figure *figures,
					float3 ray_origin, float3 ray_vector, size_t lights_num, size_t figures_num)
{
	t_cl_figure			closest;
	float				len;
	float				lbuf;
	size_t 				n;

	n = 0;
	len = INFINITY;
	while (n < figures_num)
	{
		lbuf = check_intersection(ray_origin, ray_vector, figures[n]);
		if (lbuf >= 1.0 && lbuf < len)
		{
			len = lbuf;
			closest = figures[n];
		}
		n++;
	}
	if (len == INFINITY)
		return (0);
	else
		return (do_lightrt(lights, figures, closest, ray_origin, ray_vector, len, figures_num, lights_num));
}

unsigned int	do_rt(unsigned int x,
					  unsigned int y,
					  size_t width,
					  size_t height,
					  __global t_cl_figure *figures,
					  __global t_cl_light *lights,
					  __global float *cam_v,
					  __global float *cam_o,
					  size_t figures_num,
					  size_t lights_num)
{
	float3				ray_origin;
	float3				ray_vector;
	float3 				cam_vector;
	float3 				cam_origin;
	unsigned int 		color;

	cam_vector = (float3)(cam_v[0], cam_v[1], cam_v[2]);
	cam_origin = (float3)(cam_o[0], cam_o[1], cam_o[2]);
	ray_origin = cam_origin;
	ray_vector = (float3)(0.0f, 0.0f, 1.0f);
	color = 0;
	if (y < height && x < width)
	{
		ray_vector.x = (((x + 0.5f) / width) * 2.0f - 1.0f) * (((float)width) / height) * tan(M_PI / 360 * FOV_X);
		ray_vector.y = (1.0f - 2.0f * ((y + 0.5f) / height)) * tan(3.14 / 360 * FOV_Y);
		ray_vector.z = 1.0f;
		cam_rotate(ray_origin, cam_vector);
		color = rt(lights, figures, ray_origin, ray_vector, lights_num, figures_num);
	}
	return (color);
}
