/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 19:25:07 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/30 19:25:09 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		default_helper_figures(t_view *view, t_figure *figure)
{
	size_t	i;

	i = 0;
	while (i < view->figures_num)
	{
		view->space->cl_figtmp[i] = view->space->cl_figures[i];
		i++;
	}
	clean_list_obj(view);
	add_figure(figure, view);
	if (view->space->cl_figures)
	{
		free(view->space->cl_figures);
	}
	view->space->cl_figures = copy_figures(view);
	i = 0;
	while (i < (view->figures_num - 1))
	{
		view->space->cl_figures[i] = view->space->cl_figtmp[i];
		i++;
	}
	free(view->space->cl_figtmp);
	view->space->cl_figtmp = copy_figures(view);
	object_init(view);
	opencl_init2(view);
}

void		default_sphere_init(t_view *view)
{
	t_figure *new_figure;
	t_sphere *sphere;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = Sphere;
	sphere = (t_sphere*)ft_memalloc(sizeof(t_sphere));
	new_figure->figure = sphere;
	sphere->center = (t_vector){0.0, 0.0, 2.0};
	sphere->radius = 0.4;
	new_figure->color = 0xff;
	new_figure->reflection = 0;
	new_figure->refract = -1;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void		default_plane_init(t_view *view)
{
	t_figure *new_figure;
	t_iplane *plane;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = InfinitePlane;
	plane = (t_iplane*)ft_memalloc(sizeof(t_iplane));
	new_figure->figure = plane;
	plane->normale = vnormalize((t_vector){0.0, 1.0, 0.0});
	plane->point = (t_vector){1.0, 1.0, 1.0};
	new_figure->color = 0xff;
	new_figure->reflection = 0;
	new_figure->refract = -1;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void		default_cylinder_init(t_view *view)
{
	t_figure	*new_figure;
	t_icylinder	*cylinder;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = InfiniteCylinder;
	cylinder = (t_icylinder*)ft_memalloc(sizeof(t_icylinder));
	new_figure->figure = cylinder;
	cylinder->start = (t_vector){-1.0, 0.0, 2.0};
	cylinder->vector = vnormalize((t_vector){0.0, 1.0, 0.0});
	cylinder->radius = 0.5;
	new_figure->color = 0xff;
	new_figure->refract = -1;
	cylinder->c_distances[0] = -INFINITY;
	cylinder->c_distances[1] = INFINITY;
	new_figure->reflection = 0;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}

void		default_cone_init(t_view *view)
{
	t_figure	*new_figure;
	t_icone		*cone;

	new_figure = (t_figure*)ft_memalloc(sizeof(t_figure));
	new_figure->type = InfiniteCone;
	cone = (t_icone*)ft_memalloc(sizeof(t_icone));
	new_figure->figure = cone;
	cone->vertex = (t_vector){0.0, 0.0, 0.0};
	cone->radius = 0.2;
	new_figure->color = 0x0000ff;
	new_figure->reflection = 10;
	new_figure->refract = -1;
	cone->vector = vnormalize((t_vector){0.0, 1.0, 0.0});
	new_figure->figure = cone;
	new_figure->next = NULL;
	default_helper_figures(view, new_figure);
}
