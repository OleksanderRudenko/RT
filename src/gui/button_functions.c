/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:43:18 by arudenko          #+#    #+#             */
/*   Updated: 2018/04/26 14:43:20 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	button_handler(t_view *s)
{
	(int)s->rr.fl.x == 6 ? open_scene(s) : 0;
	(int)s->rr.fl.x == 1 ? default_sphere_init(s) : 0;
	(int)s->rr.fl.x == 2 ? default_cylinder_init(s) : 0;
	(int)s->rr.fl.x == 3 ? default_cone_init(s) : 0;
	(int)s->rr.fl.x == 4 ? default_elipsoid_init(s) : 0;
	(int)s->rr.fl.x == 5 ? default_paraboloid_init(s) : 0;
	(int)s->rr.fl.x == 7 ? default_am_light(s) : 0;
	(int)s->rr.fl.x == 8 ? default_point_light(s) : 0;
	(int)s->rr.fl.x == 9 ? default_dir_light(s) : 0;
	(int)s->rr.fl.x == 10 ? default_cube_init(s) : 0;
	(int)s->rr.fl.x == 11 ? default_quadrate_init(s) : 0;
	(int)s->rr.fl.x == 12 ? default_triangle_init(s) : 0;
	(int)s->rr.fl.x == 13 ? screenshot(s) : 0;
	(int)s->rr.fl.x == 0 ? default_plane_init(s) : 0;
}

static void	window_handler(t_view *s, int num, SDL_Event e, int numl)
{
	s->rr.fl.y = s->flag == 0 ? select_figure(s->l_obj.obj_rect, e, num) : -1;
	s->rr.fl.z = select_figure(s->select.sel_rect, e, 2);
	s->rr.fl.b = select_figure(s->l_light.light_rect, e, numl);
	if (s->rr.fl.z == 0)
	{
		s->flag = 0;
	}
	else if (s->rr.fl.z == 1)
	{
		s->flag = 1;
	}
	else if (s->rr.fl.z == -1)
		s->rr.fl.z = s->flag;
}

void		mouse_key_down(t_view *s, SDL_Event e)
{
	if (e.window.windowID == 4)
	{
		s->rr.fl.x = button_off_on(s->rr.but_rect, NUM_BUTTONS, e);
		button_handler(s);
	}
	if (e.window.windowID == 2)
	{
		window_handler(s, (int)s->figures_num, e, (int)s->lights_num);
	}
	if (e.window.windowID == 3)
	{
		s->rr.fl.a = select_figure(select_rect(s), e, select_num(s));
		s->rr.fl.c = select_figure(select_rect_light(s), e, select_li_num(s));
		xxx(s->rr.fl.a, s);
		xxx_light(s->rr.fl.c, s);
		if (s->rr.fl.y == -1)
			s->rr.fl.a = -1;
	}
}

int			button_off_on(SDL_Rect *rect, int num, SDL_Event e)
{
	int	id;

	id = -1;
	while (++id < num)
	{
		if (is_in_rect(rect[id], e))
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				return (id);
			}
		}
	}
	return (-1);
}
