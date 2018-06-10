#include "rt_h.cl"

#define MAX_MIRROR_ITERS 5

float3	calc_reflect_ray(float3 ray_vector, float3 normale, float3 p)
{
	float3	new_ray;
	float		buff;

	ray_vector = ray_vector * -1;
	buff = ray_vector.x * normale.x + ray_vector.y * normale.y + ray_vector.z * normale.z;
	new_ray = normale * buff;
	new_ray = new_ray * 2;
	new_ray = new_ray - ray_vector;

	return (new_ray);
}

unsigned	int	add_colors(unsigned	int	color1, unsigned	int	color2)
{
	t_color	color_t1;
	t_color	color_t2;
	t_color	rez;

	color_t1.color = color1;
	color_t2.color = color2;
	rez.chanel[0] = (color_t1.chanel[0] + color_t2.chanel[0]) / 2;
	rez.chanel[1] = (color_t1.chanel[1] + color_t2.chanel[1]) / 2;
	rez.chanel[2] = (color_t1.chanel[2] + color_t2.chanel[2]) / 2;
	rez.chanel[3] = (color_t1.chanel[3] + color_t2.chanel[3]) / 2;
	return (rez.color);

}

float			rt_lightr(float3 light, float3 normale, float3 view, float3 buf)
{
	float3		h;
	float		d;
	float 		a;

	h = view + light;
	d = dot_my(h, normale);
	if (d >= 0.0f)
	{
		a = d / fast_length(h);
		return (buf.x * pow(a, buf.y));
	}
	else
		return (0.0f);
}

t_lrt			tlrt_init(float3 ray_origin, float3 ray_vector, t_cl_figure figure, double k, float3 normale)
{
	t_lrt	var;

	var.intersection = get_intersection(ray_origin, ray_vector, k);
	var.normale = normale;
	if ((figure.type == InfinitePlane ||
			figure.type == Triangle ||
				figure.type == Cube ||
					figure.type == Quadrate))
					{
						if (dot(var.normale, ray_vector) > 0.0)
							var.normale = k_multiply(var.normale, -1.0f);
					}
	else
	 	if (dot(var.normale, ray_vector) > 0.3)
			var.normale = k_multiply(var.normale, -1.0f);
	var.bright = 0.05;
	var.reflected = 0.05;
	return (var);
}

unsigned int	do_lightrt(__constant t_cl_light *lights,
						   __global t_cl_figure *figures,
						   t_cl_figure figure,
						   float3 ray_origin, float3 ray_vector, double k,
						   size_t figures_num, size_t lights_num, int iters, float3 normale, __global unsigned int *tex)
{
	t_lrt	v;
	size_t 	n;
	float3 	buf;
	float3 	view;

	n = 0;
	v = tlrt_init(ray_origin, ray_vector, figure, k, normale);
	while (n < lights_num)
	{
		if (lights[n].type == LIGHT_TYPE_AMBIENT)
			v.bright += lights[n].inten;
		else
		{
			if (lights[n].type == LIGHT_TYPE_POINT)
				v.vlight = lights[n].origin - v.intersection;
			else
				v.vlight = lights[n].direction * -1;
			v.buf_origin = v.intersection;
			// v.buf_vector = (float3){v.vlight.x, v.vlight.y, v.vlight.z};
			v.buf_vector = v.vlight * 1;
			if (!(check_intersections(v.buf_origin, v.buf_vector, figures, figures_num, figure)))
			{
				if ((v.nl_s = dot_my(v.normale, v.vlight)) > 0.0f)
					v.bright += lights[n].inten * v.nl_s / fast_length(v.vlight * 1);
				if (v.nl_s >= 0.0f && figure.reflection > 0.0f)
				{
					buf = (float3)(lights[n].inten, figure.reflection, 0.0f);
					view = k_multiply(ray_vector, -1.0f);
					v.reflected += rt_lightr(v.vlight, v.normale, view, buf);
				}
			}
		}
		n++;
	}
	if (iters <= 0 || figure.mirror == 0)
		return (set_brightness(figure.color, v.bright, v.reflected));
	ray_origin = v.intersection;
	ray_vector = calc_reflect_ray(ray_vector, v.normale, v.intersection);
	unsigned int buf_color = rt(lights, figures, ray_origin, ray_vector, lights_num, figures_num, iters - 1, tex);
	return (add_colors(buf_color, set_brightness(figure.color, v.bright, v.reflected)));
}

unsigned int	rt(__constant t_cl_light *lights, __global t_cl_figure *figures,
					float3 ray_origin, float3 ray_vector, size_t lights_num, size_t figures_num, int iters, __global unsigned int *tex)
{
	t_cl_figure			closest;
	t_cl_figure			buf;
	float				len;
	float				lbuf;
	size_t 				n;
	float3			buf_normale;
	float3			normale;

	n = 0;
	len = INFINITY;
	while (n < figures_num)
	{
		buf = figures[n];
		lbuf = check_intersection(ray_origin, ray_vector, &buf, 0, &buf_normale);
		if (lbuf >= 1.0 && lbuf < len)
		{
			len = lbuf;
			closest = buf;
			normale = buf_normale;
		}
		n++;
	}
	if (closest.texture > 0)
		closest.color = global_texture(normale, tex, closest, len, ray_origin, ray_vector);
	if (len == INFINITY)
		return (0);
	else
		return (do_lightrt(lights, figures, closest, ray_origin, ray_vector, len, figures_num, lights_num, iters, normale, tex));
}

unsigned int		calc_middle_color(unsigned int *colors, int antialising)
{
	int 		i;
	t_color		rez;
	float3	spectrs;

	i = 0;
	spectrs.x = 0;
	spectrs.y = 0;
	spectrs.z = 0;

	while (i < antialising)
	{
		rez.color = colors[i];
		spectrs.x += rez.chanel[1];
		spectrs.y += rez.chanel[2];
		spectrs.z += rez.chanel[3];
		++i;
	}
	rez.chanel[1] = (unsigned char)(spectrs.x / (float)antialising);
	rez.chanel[2] = (unsigned char)(spectrs.y / (float)antialising);
	rez.chanel[3] = (unsigned char)(spectrs.z / (float)antialising);
	return(rez.color);
}

unsigned int	do_rt(unsigned int x,
					  unsigned int y,
					  size_t width,
					  size_t height,
					  __global t_cl_figure *figures,
					  __constant t_cl_light *lights,
					  float3 cam_vector,
					  float3 cam_origin,
					  size_t figures_num,
					  size_t lights_num,
						int antialising,
						__global unsigned int *tex)
{
	float3				ray_origin;
	float3				ray_vector;
	unsigned int 		color;
	int						i;

	unsigned int	colors[antialising * antialising];
	float					step_x;
	float					step_y;
	float					size_x;
	float					size_y;
	float					buf;

	buf = antialising;
	antialising *= antialising;
	size_x = buf;
	size_y = buf;
	step_x = 1 / (float)size_x;
	step_y = 1 / (float)size_y;
	i = 0;
	ray_origin = cam_origin;
	ray_vector = (float3)(0.0f, 0.0f, 1.0f);
	color = 0;
	if (y < height && x < width)
	{
		while (i < antialising)
		{
			ray_vector.x = (((x + 0.5f + (step_x * (i % (int)size_x))) / width) * 2.0f - 1.0f) * (((float)width) / height) * tan(M_PI / 360 * FOV_X);
			ray_vector.y = (1.0f - 2.0f * ((y + 0.5f + (step_y * (i / size_x))) / height)) * tan(3.14 / 360 * FOV_Y);
			ray_vector.z = 1.0f;
			ray_vector = cam_rotate(ray_vector, cam_vector);
			colors[i] = rt(lights, figures, ray_origin, ray_vector, lights_num, figures_num, MAX_MIRROR_ITERS, tex);
			i++;
		}
		color = calc_middle_color(colors, antialising);
	}
	return (color);
}
