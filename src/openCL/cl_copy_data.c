/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_copy_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knovytsk <knovytsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 14:43:52 by knovytsk          #+#    #+#             */
/*   Updated: 2018/05/19 14:44:08 by knovytsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void init_cam(t_view *v, float *cam_o, float *cam_v)
{
	cam_o[0] = v->space->cam->o.x;
	cam_o[1] = v->space->cam->o.y;
	cam_o[2] = v->space->cam->o.z;
	cam_v[0] = v->space->cam->v.x;
	cam_v[1] = v->space->cam->v.y;
	cam_v[2] = v->space->cam->v.z;
}

t_cl_light *copy_light(t_view *v)
{
	t_cl_light  *light;
	t_light 	*tmp;
	int 		n;

	tmp = v->space->lights;
	light = (t_cl_light*)malloc(sizeof(t_cl_light) * v->lights_num);
	n = 0;
	while (tmp)
	{
		light[n].origin.x = tmp->o.x;
		light[n].origin.y = tmp->o.y;
		light[n].origin.z = tmp->o.z;
		light[n].inten = tmp->inten;
		light[n].type = tmp->type;
		tmp = tmp->next;
		n++;
	}
	return (light);
}

cl_float3 	copy_vector(t_vector vector)
{
	cl_float3 	copy;

	copy.x = vector.x;
	copy.y = vector.y;
	copy.z = vector.z;
	return (copy);
}



t_cl_figure *copy_figures(t_view *v)
{
	t_cl_figure *figures;
	t_figure 	*tmp;
	int 		n;
	int 		i;

	tmp = v->space->figures;
	figures = (t_cl_figure*)malloc(sizeof(t_cl_figure) * v->figures_num);
	n = 0;
	while (tmp)
	{
		figures[n].type = tmp->type;
		figures[n].color = tmp->color;
		figures[n].reflection = tmp->reflection;

		//1.PLANE
		if (tmp->type == InfinitePlane)
		{
			figures[n].normale = copy_vector(((t_iplane*)tmp->figure)->normale);
			figures[n].point = copy_vector(((t_iplane*)tmp->figure)->point);
		}
		//2.SPHERE
		if (tmp->type == Sphere)
		{
			figures[n].center = copy_vector(((t_sphere*)tmp->figure)->center);
			figures[n].radius = ((t_sphere*)tmp->figure)->radius;
		}
		//3.CYLINDER
		if (tmp->type == InfiniteCylinder)
		{
			figures[n].start = copy_vector(((t_icylinder*)tmp->figure)->start);
			figures[n].vector = copy_vector(((t_icylinder*)tmp->figure)->vector);
			figures[n].radius = ((t_icylinder*)tmp->figure)->radius;
		}
		//4.CONE
		if (tmp->type == InfiniteCone)
		{
			figures[n].vertex = copy_vector(((t_icone*)tmp->figure)->vertex);
			figures[n].vector = copy_vector(((t_icone*)tmp->figure)->vector);
			figures[n].radius = ((t_icone*)tmp->figure)->radius;
		}
		//5.TRIANGLE
		if (tmp->type == Triangle)
		{
			i = -1;
			while (++i < 3)
				figures[n].t_points[i] = copy_vector(((t_triangle*)tmp->figure)->points[i]);
			figures[n].normale = copy_vector(((t_triangle*)tmp->figure)->normale);
		}
		//6.CUBE
		if (tmp->type == Cube)
		{
			int j = -1;
			i = 0;
			while (++j < 24)
			{
				figures[n].c_points[j] = copy_vector(((t_cube*)tmp->figure)->planes[j / 4].points[i++]);
				if (i == 4)
					i = 0;
			}
			i = -1;
			while (++i < 4)
				figures[n].c_normale[i] = copy_vector(((t_cube*)tmp->figure)->planes[i].normale);
			figures[n].position = copy_vector(((t_cube*)tmp->figure)->position);
			figures[n].rotation = copy_vector(((t_cube*)tmp->figure)->rotation);
			figures[n].scale = copy_vector(((t_cube*)tmp->figure)->scale);
		}
		//7.QUADRATE
		if (tmp->type == Quadrate)
		{
			i = -1;
			while (++i < 4)
				figures[n].q_points[i] = copy_vector(((t_squard*)tmp->figure)->points[i]);
			figures[n].normale = copy_vector(((t_squard*)tmp->figure)->normale);
		}
		//8.ELIPSOID
		if (tmp->type == Elipsoid)
		{
			figures[n].position = copy_vector(((t_elipsoid*)tmp->figure)->position);
			figures[n].rotation = copy_vector(((t_elipsoid*)tmp->figure)->rotation);
			figures[n].radius = ((t_elipsoid*)tmp->figure)->radius;
			figures[n].rdistance = ((t_elipsoid*)tmp->figure)->rdistance;
		}
		//9.PARABALOID
		if (tmp->type == Parabaloid)
		{
			figures[n].position = copy_vector(((t_parabaloid*)tmp->figure)->position);
			figures[n].rotation = copy_vector(((t_parabaloid*)tmp->figure)->rotation);
			figures[n].radius = ((t_parabaloid*)tmp->figure)->radius;
		}
		//10.TOR
		if (tmp->type == Tor)
		{
			figures[n].radius_s = ((t_itor*)tmp->figure)->r;
			figures[n].radius_b = ((t_itor*)tmp->figure)->r_b;
			figures[n].center = copy_vector(((t_itor*)tmp->figure)->center);
		}
		tmp = tmp->next;
		n++;
	}
	// n = 0;
	// while (n < (int)v->figures_num)
	// {
	// 	printf("type->%i\n", figures[n].type);
	// 	if (figures[n].type == InfinitePlane)
	// 		printf("Plane : ");
	// 	if (figures[n].type == Sphere)
	// 		printf("Sphere : ");
	// 	if (figures[n].type == InfiniteCylinder)
	// 		printf("Cylinder : ");
	// 	printf("color -> %#x reflection ->%f \n", figures[n].color, figures[n].reflection);
	// 	n++;
	// }
	return (figures);
}
