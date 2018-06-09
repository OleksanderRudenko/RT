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

typedef void 	(*t_copy)(t_cl_figure*, t_figure*);


static t_copy 	*copy_array(void)
{
	t_copy 	*copy;

	copy = (t_copy*)malloc(sizeof(t_copy) * 10);
	copy[InfinitePlane] = &copy_plane;
	copy[Sphere] = &copy_sphere;
	copy[InfiniteCylinder] = &copy_cylinder;
	copy[InfiniteCone] = &copy_cone;
	copy[Triangle] = &copy_triangle;
	copy[Cube] = &copy_cube;
	copy[Quadrate] = &copy_quadrate;
	copy[Elipsoid] = &copy_elipsoid;
	copy[Parabaloid] = &copy_paraboloid;
	copy[Tor] = &copy_tor;
	return (copy);
}

void 			init_cam(t_view *v, cl_float3 *cam_o, cl_float3 *cam_v)
{
	cam_o->x = v->space->cam->o.x;
	cam_o->y = v->space->cam->o.y;
	cam_o->z = v->space->cam->o.z;
	cam_v->x = v->space->cam->v.x;
	cam_v->y = v->space->cam->v.y;
	cam_v->z = v->space->cam->v.z;
}

t_cl_light 		*copy_light(t_view *v)
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
		light[n].direction = copy_vector(tmp->d);
		light[n].type = tmp->type;
		tmp = tmp->next;
		n++;
	}
	return (light);
}

cl_float3 		copy_vector(t_vector vector)
{
	cl_float3 	copy;

	copy.x = vector.x;
	copy.y = vector.y;
	copy.z = vector.z;
	return (copy);
}

/* TO DELETE */
void 		printf_figures(t_view *v, t_cl_figure *figures)
{
	int n;

	n = 0;
	while (n < (int)v->figures_num)
	{
		printf("type->%i\n", figures[n].type);
		if (figures[n].type == InfinitePlane)
			printf("Plane : ");
		if (figures[n].type == Sphere)
			printf("Sphere : ");
		if (figures[n].type == InfiniteCylinder)
			printf("Cylinder : ");
		if (figures[n].type == InfiniteCone)
			printf("InfiniteCone : ");
		if (figures[n].type == Triangle)
			printf("Triangle : ");
		if (figures[n].type == Cube)
			printf("Cube : ");
		if (figures[n].type == Quadrate)
			printf("Quadrate : ");
		if (figures[n].type == Elipsoid)
			printf("Elipsoid : ");
		if (figures[n].type == Parabaloid)
			printf("Parabaloid : ");
		if (figures[n].type == Tor)
			printf("Tor : ");
		printf("color -> %#x reflection ->%f \n", figures[n].color, figures[n].reflection);
		n++;
	}
}

t_cl_figure *copy_figures(t_view *v)
{
	static t_copy 	*copy_figure = NULL;
	t_cl_figure 	*figures;
	t_figure 		*tmp;
	int 			n;

	if (copy_figure == NULL)
		copy_figure = copy_array();
	tmp = v->space->figures;
	figures = (t_cl_figure*)ft_memalloc(sizeof(t_cl_figure) * v->figures_num);
	n = 0;
	while (tmp)
	{
		figures[n].type = tmp->type;
		figures[n].color = tmp->color;
		figures[n].reflection = tmp->reflection;
		figures[n].mirror = tmp->mirror;
		copy_figure[tmp->type](&figures[n], tmp);
		tmp = tmp->next;
		n++;
	}
	// printf_figures(v, figures);
	return (figures);
}
