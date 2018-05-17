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

void	mouse_key_down(t_view *s, SDL_Event e)
{
	if (e.window.windowID == 4)
		button_off_on(s->rr.but_rect, e, s);
	// if (e.window.windowID == 4)
}

void	mouse_key_up(t_view *s)
{
	int	i;

	i = 0;
	while (i < NUM_BUTTONS * 2)
	{
		s->rr.flag[i] = (s->rr.flag[i] == 0) ? 1 : 1;
		i++;
	}
}

void	button_off_on(SDL_Rect *rect, SDL_Event e, t_view *s)
{
	int x;
	int y;
	int id;

	id = -1;
	while (++id < NUM_BUTTONS)
	{
		x = e.button.x;
		y = e.button.y;
		if (x >= rect[id].x && x <= (rect[id].x + rect[id].w) && y >= rect[id].y && y <= (rect[id].y + rect[id].h))
		{
			if (e.button.button == SDL_BUTTON_LEFT)
			{
				s->rr.flag[id] = (s->rr.flag[id] == 1) ? 0 : 1;
				printf("x: %d y:%d\n", x, y); /*For debug*/
			}
		}
	}
}