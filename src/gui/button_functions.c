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
	(int)s->rr.fl.x == 3 ? open_scene(s) : 0;
}

static void	window_handler(t_view *s, int num, SDL_Event e)
{
		s->rr.fl.y = select_figure(s->l_obj.obj_rect, e, num);//a
		s->rr.fl.z = select_figure(s->select.sel_rect, e, 2);//b
		if (s->rr.fl.z == 0)
			s->flag = 0;
		else if (s->rr.fl.z == 1)
			s->flag = 1;
		else if (s->rr.fl.z == -1)
			s->rr.fl.z = s->flag;
		printf("id win2: %D\n",s->rr.fl.y);/*for debug*/
}

void		mouse_key_down(t_view *s, SDL_Event e)
{
	int	num;

	num = num_figures(s);
	if (e.window.windowID == 4)
	{
		s->rr.fl.x = button_off_on(s->rr.but_rect, s->rr.flag, NUM_BUTTONS, e);
		printf("id win 4: %D\n",s->rr.fl.x); /*for debug*/
		button_handler(s);
	}
	else if (e.window.windowID == 2)
	{
		window_handler(s, num, e);
	}
	else if (e.window.windowID == 3)
	{
		s->rr.fl.a = select_figure(s->prop.pr_rect, e, NUM_SPH_PROP);
		xxx(s->rr.fl.a, s);
		ok_button_function(s, e);
		printf("sphere prop: %d\n",s->rr.fl.a);
	}
}

void	mouse_key_up(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_BUTTONS * 2)
	{
		s->rr.flag[i] = (s->rr.flag[i] == 1) ? 1 : 1;
	}
}

void	select_button_up(t_view *s, SDL_Event e, int num)
{
	int	i;
	int n;

	i = -1;
	while (++i < num)
	{
		if (is_in_rect(s->select.sel_rect[i], e))
		{
				s->select.s_flag[i] = (s->select.s_flag[i] == 1) ? 0 : 1;
				n = -1;
				while (++n < num)
				{
					if (n != i)
						s->select.s_flag[n] = (s->select.s_flag[n] == 1) ? 0 : 1;
				}
		}
	}
}

int		button_off_on(SDL_Rect *rect, int *flag, int num, SDL_Event	e)
{
	int			id;

	id = -1;
	while (++id < num)
	{
		if (is_in_rect(rect[id], e))
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				flag[id] = (flag[id] == 1) ? 0 : 1;
				return (id);
			}
		}
	}
	return (-1);
}