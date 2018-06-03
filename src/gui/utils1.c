/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 18:30:21 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/01 18:30:23 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Rect	make_rect(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

char *figure_type(t_figure_type num)
{
	if (num == 0)
		return ("Infinite Plane");
	else if (num == 1)
		return ("Sphere");
	else if (num == 2)
		return ("Infinite Cylinder");
	else if (num == 3)
		return ("Infinite Cylinder");
	else if (num == 4)
		return ("Triangle");
	else if (num == 5)
		return ("Cube");
	return ("LOL WAT");
}

char	*light_type(char num)
{
	if (num == 0)
		return ("AMBIENT");
	else if (num == 1)
		return ("POINT");
	return ("DIRECTIONAL");
}

int		is_in_rect(SDL_Rect rect, SDL_Event e)
{
	int x;
	int y;

	x = e.button.x;
	y = e.button.y;
	if (x >= rect.x && x <= (rect.x + rect.w) && y >= rect.y && y <= (rect.y + rect.h))
		return (1);
	return (0);
}

void	open_scene(t_view *s)
{
		char const *type[2] = { "*.txt", "*.json" };
		char const *name = tinyfd_openFileDialog("", "", 2, type, NULL, 0);

		if (name == NULL)
		{
			ft_putendl("U dont choose anything");
			return ;
		}
		
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		delete_init_cl(s);
		del_list(s);
		space_init(name, s);
		object_init(s);
		// view_init(s, name);
		
		// opencl_init(s);
		opencl_init2(s);
		// get_init_prop(s);
		// get_properties(s);
		// detect_type_of_figure(s);
		// what_to_print(s);
		/*NEED to delete all malloc before redrawing all!*/
}

char	*ft_ftoa(double value)
{
	int		nb;
	char	*arr;
	char	*arr2;
	int		point_part;
	char	*tmp;

	nb = (int)value;
	arr = ft_itoa(nb);
	ft_strcat(arr, ".");
	point_part = (value - nb) * 100;
	point_part = point_part < 0 ? point_part * -1 : point_part;
	arr2 = ft_itoa(point_part);
	tmp = arr;
	arr = ft_strjoin(arr, arr2);
	free(arr2);
	free(tmp);
	return (arr);
}

t_col	col_parse(int col)
{
	t_col	c;

	c.red = col >> 16;
	c.green = col >> 8;
	c.blue = col & 0xFF;
	return (c);
}

int		color_unite(int r, int g, int b)
{
	return ((r << 16 | g << 8 | b));
}

SDL_Rect	*select_rect(t_view *s)
{
	int			type;
	
	type = s->space->cl_figures[s->rr.fl.y].type;
	if (type == InfinitePlane)
		return(s->pl.pl_pr_rect);
	else if (type == Sphere)
		return (s->prop.pr_rect);
	else if (type == InfiniteCylinder)
		return (s->ic.ic_pr_rect);
	else if (type == InfiniteCone)
		return (s->con.cn_pr_rect);
	else if (type == Triangle)
		return (s->tri.tri_pr_rect);
	else if (type == Cube)
		return (s->cub.cu_pr_rect);
	else if (type == Quadrate)
		return (s->qua.qu_pr_rect);
	else if (type == Elipsoid)
		return (s->elp.el_pr_rect);
	else if (type == Parabaloid)
		return (s->par.pr_pr_rect);
	return (NULL);
}

int			select_num(t_view *s)
{
	int			type;
	
	type = s->space->cl_figures[s->rr.fl.y].type;
	if (type == InfinitePlane)
		return(NUM_PL_PR);
	else if (type == Sphere)
		return (NUM_SP_PR);
	else if (type == InfiniteCylinder)
		return (NUM_IC_PR);
	else if (type == InfiniteCone)
		return (NUM_CN_PR);
	else if (type == Triangle)
		return (NUM_TR_PR);
	else if (type == Cube)
		return (NUM_CU_PR);
	else if (type == Quadrate)
		return (NUM_QUA_PR);
	else if (type == Elipsoid)
		return (NUM_EL_PR);
	else if (type == Parabaloid)
		return (NUM_PR_PR);
	return (-1);
}

// int			rt_figure(t_view *s, int x, int y)
// {
// 	t_figure	*iterator;
// 	double		len;
// 	double		lbuf;
// 	t_ray		*ray;
// 	int			i;
// 	int			a = 0;

// 	ray = ray_init(s->space->cam->o, (t_vector){0, 0, 1});
// 	ray->v.x = (((x + 0.5) / WIDTH) * 2 - 1) * (((double)WIDTH) / HEIGHT) *
// 					tan(M_PI / 360 * FOV_X);
// 	ray->v.y = (1 - 2 * ((y + 0.5) / HEIGHT)) *
// 			tan(M_PI / 360 * FOV_Y);
// 	ray->v.z = 1;
// 	cam_rotate(ray, s->space->cam->v);
// 	len = INFINITY;
// 	iterator = s->space->figures;
// 	i = 0;
// 	while (iterator != NULL)
// 	{
// 		lbuf = check_intersection(ray, iterator);
// 		if (lbuf >= 1.0 && lbuf < len)
// 		{
// 			len = lbuf;
// 			a = i;
// 		}
// 		iterator = iterator->next;
// 		i++;
// 	}
// 	free(ray);
// 	if (len == INFINITY)
// 		return (-1);
// 	return (a);
// }

void	delete_init_cl(t_view *s)
{
	free(s->space->cl_figures);
	free(s->space->cl_lights);
}

void	del_list(t_view *s)
{
	t_figure	*fig;
	t_figure	*lol;

	fig = s->space->figures;
	while (fig)
	{
		lol = fig->next;
		free(fig);
		fig = lol;
	}
	s->space->figures = NULL;
}