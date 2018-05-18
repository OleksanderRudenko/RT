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

int num_figures(t_view *s)
{
	int			i;
	t_figure	*fig;

	fig = s->space->figures;
	i = 0;
	if (fig == NULL)
		return (0);
	while (fig)
	{
		i++;
		fig = fig->next;
	}
	return (i);
}

int num_lights(t_view *s)
{
	int			i;
	t_light		*light;

	light = s->space->lights;
	i = 0;
	if (light == NULL)
		return (0);
	while (light)
	{
		i++;
		light = light->next;
	}
	return (i);
}

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
		return ("InfinitePlane");
	else if (num == 1)
		return ("Sphere");
	else if (num == 2)
		return ("InfiniteCylinder");
	else if (num == 3)
		return ("InfiniteCylinder");
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
		space_init(name, s);
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		do_rt(s);
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

// void	data_init(t_view *s, t_figure *f)
// {
// 	s->data = (t_data*)malloc(sizeof(t_data));
// 	s->data->center = (t_vector){0, 0, 0};
// 	s->data->radius = 0.0;
// 	s->data->reflection = 0.0;
// 	s->data->col = (t_col){0, 0, 0};
// }