/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:45:16 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/14 18:45:18 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_slider(t_view *s)
{
	if (!(s->sl = (t_slider **)malloc(sizeof(t_slider*) * 3)))
		ft_putendl("LOL");
	s->sl[0] = (t_slider *)malloc(sizeof(t_slider));
	s->sl[1] = (t_slider *)malloc(sizeof(t_slider));
	s->sl[2] = (t_slider *)malloc(sizeof(t_slider));
	
	s->sl[0]->line = get_tex("img/line.bmp", s->rr.rend[2]);
	s->sl[0]->slider_but = get_tex("img/1.bmp", s->rr.rend[2]);
	s->sl[0]->line_rect = make_rect(10, 10, 250, 10);
	s->sl[0]->slider_rect = make_rect(10, 5, 10, 20);
	
	s->sl[1]->line = get_tex("img/line.bmp", s->rr.rend[2]);
	s->sl[1]->slider_but = get_tex("img/1.bmp", s->rr.rend[2]);
	s->sl[1]->line_rect = make_rect(10, 50, 250, 10);
	s->sl[1]->slider_rect = make_rect(10, 45, 10, 20);

	s->sl[2]->line = get_tex("img/line.bmp", s->rr.rend[2]);
	s->sl[2]->slider_but = get_tex("img/1.bmp", s->rr.rend[2]);
	s->sl[2]->line_rect = make_rect(10, 100, 250, 10);
	s->sl[2]->slider_rect = make_rect(10, 95, 10, 20);
}

void	display_colored_rect(t_view *s)
{
	SDL_Rect	tr;

	tr = make_rect(50, 120, 150, 50);

	SDL_SetRenderDrawColor(s->rr.rend[2], s->sl[0]->clr.red, s->sl[1]->clr.green, s->sl[2]->clr.blue, 255);
	SDL_RenderFillRect(s->rr.rend[2], &tr);
	SDL_RenderDrawRect(s->rr.rend[2], &tr);
	SDL_SetRenderDrawColor(s->rr.rend[2], 0, 0, 0, 255);
	SDL_RenderCopy(s->rr.rend[2], s->sl[0]->line, NULL, &s->sl[0]->line_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[0]->slider_but, NULL, &s->sl[0]->slider_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[1]->line, NULL, &s->sl[1]->line_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[1]->slider_but, NULL, &s->sl[1]->slider_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[2]->line, NULL, &s->sl[2]->line_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[2]->slider_but, NULL, &s->sl[2]->slider_rect);

}

void	slider_click_event(SDL_Keycode key, t_view *s, SDL_Event e)
{
	if (key == 1)
	{
		if (is_in_rect(s->sl[0]->line_rect, e) && s->sl[0]->slider_rect.x >= 0 && s->sl[0]->slider_rect.x <= 265 )
		{
			s->sl[0]->slider_rect.x = e.button.x;
			s->sl[0]->clr.red = s->sl[0]->slider_rect.x - 10;
		}
		if (is_in_rect(s->sl[1]->line_rect, e) && s->sl[1]->slider_rect.x >= 0 && s->sl[1]->slider_rect.x <= 265 )
		{
			s->sl[1]->slider_rect.x = e.button.x;
			s->sl[1]->clr.green = s->sl[1]->slider_rect.x - 10;
		}
		if (is_in_rect(s->sl[2]->line_rect, e) && s->sl[2]->slider_rect.x >= 0 && s->sl[2]->slider_rect.x <= 265 )
		{
			s->sl[2]->slider_rect.x = e.button.x;
			s->sl[2]->clr.blue= s->sl[2]->slider_rect.x - 10;
		}
	}
}

void	slider_motion_event(t_view *s, SDL_Event e)
{	
	if (is_in_rect(s->sl[0]->line_rect, e) && s->sl[0]->slider_rect.x >= 0 && s->sl[0]->slider_rect.x <= 265
		&& e.button.button == 1)
	{
		s->sl[0]->slider_rect.x = e.button.x;
		s->sl[0]->clr.red = s->sl[0]->slider_rect.x - 10;
	}
	if (is_in_rect(s->sl[1]->line_rect, e) && s->sl[1]->slider_rect.x >= 0 && s->sl[1]->slider_rect.x <= 265
		&& e.button.button == 1)
	{
		s->sl[1]->slider_rect.x = e.button.x;
		s->sl[1]->clr.green = s->sl[1]->slider_rect.x - 10;
	}
	if (is_in_rect(s->sl[2]->line_rect, e) && s->sl[2]->slider_rect.x >= 0 && s->sl[2]->slider_rect.x <= 265
		&& e.button.button == 1)
	{
		s->sl[2]->slider_rect.x = e.button.x;
		s->sl[2]->clr.blue = s->sl[2]->slider_rect.x - 10;
	}
}