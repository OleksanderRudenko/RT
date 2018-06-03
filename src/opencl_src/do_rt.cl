
#include "rt_h.cl"

#define RAYS_PER_PIXEL 1 // antialising
#define MAX_MIRROR_ITERS 0 // MIRROR


/*
	mirror effect
*/

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

// t_ray	calc_reflect_ray(t_ray *old_ray, t_vector p, t_vector normal)
// {
// 	t_ray new_ray;
//
// 	new_ray.o = p;
// 	old_ray->v = vk_multiple(old_ray->v, -1);
// 	new_ray.v = vk_multiple(normal, 2 * vscalar_multiple(old_ray->v, normal));
// 	new_ray.v = vsub(new_ray.v, old_ray->v);
// 	return (new_ray);
// }


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

// int		add_colors(int color1, int color2)
// {
// 	t_color	color_t1;
// 	t_color	color_t2;
// 	t_color	rez;
//
// 	color_t1.color = color1;
// 	color_t2.color = color2;
// 	rez.spectrum.red = (color_t1.spectrum.red + color_t2.spectrum.red) / 2;
// 	rez.spectrum.green = (color_t1.spectrum.green + color_t2.spectrum.green) / 2;
// 	rez.spectrum.blue = (color_t1.spectrum.blue + color_t2.spectrum.blue) / 2;
// 	return (rez.color);
// }



/*
	mirror effect END
*/


float			rt_lightr(float3 light, float3 normale, float3 view, float3 buf)
{
	float3		h;
	float		d;
	float 		a;

	// h = sum(view, light);
	// d = dot(h, normale);

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
	// var.normale = get_normale(var.intersection, figure);
	var.normale = normale;
	// if (dot(var.normale, ray_vector) >= 0.0)
	// 	var.normale = k_multiply(var.normale, -1.0f);

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
						   size_t figures_num, size_t lights_num, int iters, float3 normale)
{
	t_lrt	v;
	size_t 	n;
	float3 	buf;
	float3 	view;

	// return (figure.color);
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
			v.buf_vector = (float3)(v.vlight.x, v.vlight.y, v.vlight.z);

			// v.vlight = v.intersection - lights[n].origin;
			if (!(check_intersections(v.buf_origin, v.buf_vector, figures, figures_num, figure)))
			{
				if ((v.nl_s = dot(v.normale, v.vlight)) > 0.0f)
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
	// if (iters <= 0)
		return (set_brightness(figure.color, v.bright, v.reflected));
	// ray_origin = v.intersection;
	// ray_vector = calc_reflect_ray(ray_vector, v.normale, v.intersection);
	// unsigned int buf_color = rt(lights, figures, ray_origin, ray_vector, lights_num, figures_num, iters - 1);
	// return (add_colors(buf_color, set_brightness(figure.color, v.bright, v.reflected)));
	// space->reflect_count--;
	// t_ray new_ray = calc_reflect_ray(ray, v.intersection, v.normale);
	// return (add_colors(buf_color, rt(space, &new_ray)));

	//rt(...iters - 1);
}

unsigned int	rt(__constant t_cl_light *lights, __global t_cl_figure *figures,
					float3 ray_origin, float3 ray_vector, size_t lights_num, size_t figures_num, int iters)
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
		// lbuf = check_intersection(ray_origin, ray_vector, &figures[n]);
		if (lbuf >= 1.0 && lbuf < len)
		{
			len = lbuf;
			closest = buf;
			normale = buf_normale;
		}
		n++;
	}
	if (len == INFINITY)
		return (0);
	else
		return (do_lightrt(lights, figures, closest, ray_origin, ray_vector, len, figures_num, lights_num, iters, normale));
}

// unsigned char    find_cartoon(unsigned char col)
// {
//     if (col <= 0)
//         return (0);
//     else if (col > 0 && col <= 50)
//         return (25);
//     else if (col > 50 && col <= 100)
//         return (75);
//     else if (col > 100 && col <= 200)
//         return (150);
//     else if (col > 200 && col <= 250)
//         return (225);
//     else if (col > 250)
//         return (255);
//     return (col);
// }

unsigned int		calc_middle_color(unsigned int *colors)
{
	int 		i;
	t_color		rez;
	float3	spectrs;

	i = 0;
	spectrs.x = 0;
	spectrs.y = 0;
	spectrs.z = 0;

	while (i < RAYS_PER_PIXEL)
	{
		rez.color = colors[i];
		spectrs.x += rez.chanel[1];
		spectrs.y += rez.chanel[2];
		spectrs.z += rez.chanel[3];
		++i;
	}
	rez.chanel[1] = (unsigned char)(spectrs.x / (double)RAYS_PER_PIXEL);
	rez.chanel[2] = (unsigned char)(spectrs.y / (double)RAYS_PER_PIXEL);
	rez.chanel[3] = (unsigned char)(spectrs.z / (double)RAYS_PER_PIXEL);

	// rez.chanel[1] = find_cartoon(rez.chanel[1]);
	// rez.chanel[2] = find_cartoon(rez.chanel[2]);
	// rez.chanel[3] = find_cartoon(rez.chanel[3]);
	return(rez.color);
}

/*
	with antialising
*/


unsigned int	do_rt(unsigned int x,
					  unsigned int y,
					  size_t width,
					  size_t height,
					  __global t_cl_figure *figures,
					  __constant t_cl_light *lights,
					  float3 cam_vector,
					  float3 cam_origin,
					  size_t figures_num,
					  size_t lights_num)
{
	float3				ray_origin;
	float3				ray_vector;
	unsigned int 		color;
	int						i;

	unsigned int	colors[RAYS_PER_PIXEL];
	float					step_x;
	float					step_y;
	float					size_x;
	float					size_y;
	float					buf;

	buf = (int)q_rsqrt((float)RAYS_PER_PIXEL);
	buf = 1;
	if (x == 1 && y == 0)
	{
	// 	t_cl_figure buf = figures[16];
  //
	// 	printf("%0x-COLOR\n", buf.color);
	// 	// printf ("CL\n");
	// 	// printf("%f, %f, %f-cam_o\n", cam_origin.x, cam_origin.y, cam_origin.z);
	// 	// printf("%f, %f, %f-cam_v\n", cam_vector.x, cam_vector.y, cam_vector.z);
	// }


		size_t n;
  // //
		printf("START!!!\n");

		n = 0;
		while (n < figures_num)
		{

			// size_t i;
      //
			// i = 0;
			// while (i < 6)
			// {
			// 		// figures[i].normale = count_triangle_normale(figures[i].points);
			// 		printf("CUBE sq number:CL:%d\n", i);
			// 		printf("%f, %f, %f-0\n", figures[n].c_points[i * 4 + 0].x, figures[n].c_points[i * 4 + 0].y, figures[n].c_points[i * 4 + 0].z);
			// 		printf("%f, %f, %f-1\n", figures[n].c_points[i * 4 + 1].x, figures[n].c_points[i * 4 + 1].y, figures[n].c_points[i * 4 + 1].z);
			// 		printf("%f, %f, %f-2\n", figures[n].c_points[i * 4 + 2].x, figures[n].c_points[i * 4 + 2].y, figures[n].c_points[i * 4 + 2].z);
			// 		printf("%f, %f, %f-3\n", figures[n].c_points[i * 4 + 3].x, figures[n].c_points[i * 4 + 3].y, figures[n].c_points[i * 4 + 3].z);
			// 		printf("%f, %f, %f-Normale\n", figures[n].c_normale[i].x, figures[n].c_normale[i].y, figures[n].c_normale[i].z);
			// 		++i;
			// }
			// printf("%d\n", figures[n].color)
			// printf("%f, %f, %f-q_points0\n", figures[n].q_points[0].x, figures[n].q_points[0].y, figures[n].q_points[0].z);
			// printf("%f, %f, %f-q_points1\n", figures[n].q_points[1].x, figures[n].q_points[1].y, figures[n].q_points[1].z);
			// printf("%f, %f, %f-q_points2\n", figures[n].q_points[2].x, figures[n].q_points[2].y, figures[n].q_points[2].z);
			// printf("%f, %f, %f-q_points2\n", figures[n].q_points[3].x, figures[n].q_points[3].y, figures[n].q_points[3].z);
			// printf("%f, %f, %f-normale\n", figures[n].normale.x, figures[n].normale.y, figures[n].normale.z);
      //
			// printf("%f-radius\n", figures[n].radius);
			// printf("%d-TYPE!!\n\n", figures[n].type);
			printf("%0x-COLOR!!\n\n", figures[n].color);
			// printf("%0x-COLOR_F!!\n\n", figures[n].color_f);
			// printf("%0x-COLOR_c1!!\n\n", figures[n].color_c1);
			// printf("%0x-COLOR_c2!!\n\n", figures[n].color_c2);
			// printf("%f-REFLECTION!!\n\n", figures[n].reflection);


			// printf("%f, %f, %f-vertex\n", figures[n].vertex.x, figures[n].vertex.y, figures[n].vertex.z);
			// printf("%f, %f, %f-vector\n", figures[n].vector.x, figures[n].vector.y, figures[n].vector.z);
			// printf("%f-radius\n", figures[n].radius);
			// printf("%d-TYPE!!\n\n", figures[n].type);
			// printf("%0x-COLOR!!\n\n", figures[n].color);
			// printf("%0x-COLOR_F!!\n\n", figures[n].color_f);
			// printf("%0x-COLOR_c1!!\n\n", figures[n].color_c1);
			// printf("%0x-COLOR_c2!!\n\n", figures[n].color_c2);
			// printf("%f-REFLECTION!!\n\n", figures[n].reflection);
			n++;
		}
	}
	// // 	// t_figure_type ttt = InfiniteCone;
  // //   //
	// // 	// printf("%d-ggg\n\n\n", ttt);
	// }

	// if (x != WIDTH / 2 || y != HEIGHT / 2)
	// 	return (0);

	// if (buf <= 0)
		// buf = 1;
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
		while (i < RAYS_PER_PIXEL)
		{
			ray_vector.x = (((x + 0.5f + (step_x * (i % (int)size_x))) / width) * 2.0f - 1.0f) * (((float)width) / height) * tan(M_PI / 360 * FOV_X);
			ray_vector.y = (1.0f - 2.0f * ((y + 0.5f + (step_y * (i / size_x))) / height)) * tan(3.14 / 360 * FOV_Y);
			ray_vector.z = 1.0f;
			ray_vector = cam_rotate(ray_vector, cam_vector);
			colors[i] = rt(lights, figures, ray_origin, ray_vector, lights_num, figures_num, MAX_MIRROR_ITERS);
			i++;
		}
		color = calc_middle_color(colors);
		// t_color test_col;
    //
		// test_col.color = color;
		// test_col.spectrum.blue = find_cartoon(color.spectrum.blue);
		// test_col.spectrum.green = find_cartoon(color.spectrum.green);
		// test_col.spectrum.red = find_cartoon(color.spectrum.red);
		// color = test_col.color;
		// color =
	}



	// if (x == WIDTH / 2 && y == HEIGHT / 2 )
	// {
	// 	printf("START CAMERA!!!\n");
  //
	// 	printf("%f, %f, %f-VECTOR\n", ray_vector.x, ray_vector.y, ray_vector.z);
	// 	// size_t n;
  //   //
	// 	// n = 0;
	// 	// while (n < figures_num)
	// 	// {
	// 	// 	printf("%f, %f, %f-vertex\n", figures[n].vertex.x, figures[n].vertex.y, figures[n].vertex.z);
	// 	// 	printf("%f, %f, %f-vector\n", figures[n].vector.x, figures[n].vector.y, figures[n].vector.z);
	// 	// 	printf("%f, %f, %f-normale\n", figures[n].normale.x, figures[n].normale.y, figures[n].normale.z);
	// 	// 	printf("%f-radius\n", figures[n].radius);
	// 	// 	printf("%d-TYPE!!\n\n", figures[n].type);
	// 	// 	printf("%0x-COLOR!!\n\n", figures[n].color);
	// 	// 	printf("%0x-COLOR_F!!\n\n", figures[n].color_f);
	// 	// 	printf("%0x-COLOR_c1!!\n\n", figures[n].color_c1);
	// 	// 	printf("%0x-COLOR_c2!!\n\n", figures[n].color_c2);
	// 	// 	printf("%f-REFLECTION!!\n\n", figures[n].reflection);
	// 	// 	n++;
	// 	}

	// 	// t_figure_type ttt = InfiniteCone;
  //   //
	// 	// printf("%d-ggg\n\n\n", ttt);
	// }


	return (color);
}

/*
	without antialising
*/

//
// unsigned int	do_rt(unsigned int x,
// 					  unsigned int y,
// 					  size_t width,
// 					  size_t height,
// 					  __global t_cl_figure *figures,
// 					  __constant t_cl_light *lights,
// 					  float3 cam_vector,
// 					  float3 cam_origin,
// 					  size_t figures_num,
// 					  size_t lights_num)
// {
// 	float3				ray_origin;
// 	float3				ray_vector;
// 	unsigned int 		color;
// 	int						i;
//
// 	i = 0;
// 	ray_origin = cam_origin;
// 	ray_vector = (float3)(0.0f, 0.0f, 1.0f);
// 	color = 0;
// 	if (y < height && x < width)
// 	{
// 		while (i < RAYS_PER_PIXEL)
// 		{
//
// 			ray_vector.x = (((x + 0.5f) / width) * 2.0f - 1.0f) * (((float)width) / height) * tan(M_PI / 360 * FOV_X);
// 			ray_vector.y = (1.0f - 2.0f * ((y + 0.5f) / height)) * tan(3.14 / 360 * FOV_Y);
// 			ray_vector.z = 1.0f;
// 			cam_rotate(ray_origin, cam_vector);
// 			color = rt(lights, figures, ray_origin, ray_vector, lights_num, figures_num, 0);
// 			i++;
// 		}
// 	}
// 	return (color);
// }
