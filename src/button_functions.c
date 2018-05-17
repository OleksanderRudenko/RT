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

// void	key_down(SDL_Scancode key, t_view *s)
// {
// 	if (key == SDL_SCANCODE_W)
// 	{
// 		ft_bzero(s->win_surface[0]->pixels, WIDTH * HEIGHT * 4);
// 		s->figure[1].pos.x += 0.1;
// 		draw(s);
// 	}
// }

void	button_off_on(SDL_Rect *rect, SDL_Event e, t_view *s)
{
	int x;
	int y;
	int id;

	id = -1;
	while (++id < 3)
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
