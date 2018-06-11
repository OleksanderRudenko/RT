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

char	*figure_type(t_figure_type num)
{
	if (num == 0)
		return ("Plane");
	else if (num == 1)
		return ("Sphere");
	else if (num == 2)
		return ("Cylinder");
	else if (num == 3)
		return ("Cone");
	else if (num == 4)
		return ("Triangle");
	else if (num == 5)
		return ("Cube");
	else if (num == 6)
		return ("Quadrate");
	else if (num == 7)
		return ("Elipsoid");
	else if (num == 8)
		return ("Parabaloid");
	return ("LOL WAT");
}

int		is_in_rect(SDL_Rect rect, SDL_Event e)
{
	int x;
	int y;

	x = e.button.x;
	y = e.button.y;
	if (x >= rect.x && x <= (rect.x + rect.w)
		&& y >= rect.y && y <= (rect.y + rect.h))
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
	clean_list_obj(s);
	clean_light(s);
	delete_init_cl(s);
	del_list(s);
	space_init(name, s);
	object_init(s);
	light_list_init(s);
	opencl_init2(s);
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
