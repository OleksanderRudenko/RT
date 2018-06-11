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
	s->sl[0]->line = get_tex("img/red.png", s->rr.rend[2]);
	s->sl[0]->slider_but = get_tex("img/1.png", s->rr.rend[2]);
	s->sl[0]->line_rect = make_rect(0, 10, 255, 10);
	s->sl[0]->slider_rect = make_rect(0, 5, 11, 20);
	s->sl[1]->line = get_tex("img/green.png", s->rr.rend[2]);
	s->sl[1]->slider_but = get_tex("img/1.png", s->rr.rend[2]);
	s->sl[1]->line_rect = make_rect(0, 50, 255, 10);
	s->sl[1]->slider_rect = make_rect(10, 45, 11, 20);
	s->sl[2]->line = get_tex("img/line.bmp", s->rr.rend[2]);
	s->sl[2]->slider_but = get_tex("img/1.png", s->rr.rend[2]);
	s->sl[2]->line_rect = make_rect(0, 90, 255, 11);
	s->sl[2]->slider_rect = make_rect(0, 85, 10, 20);
}

void	display_colored_rect(t_view *s)
{
	SDL_Rect	tr;

	tr = make_rect(50, 120, 150, 50);
	SDL_SetRenderDrawColor(s->rr.rend[2], s->sl[0]->clr.red,
		s->sl[1]->clr.green, s->sl[2]->clr.blue, 255);
	SDL_RenderFillRect(s->rr.rend[2], &tr);
	SDL_RenderDrawRect(s->rr.rend[2], &tr);
	SDL_SetRenderDrawColor(s->rr.rend[2], 0, 0, 0, 255);
	SDL_RenderCopy(s->rr.rend[2], s->sl[0]->line, NULL, &s->sl[0]->line_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[0]->slider_but,
		NULL, &s->sl[0]->slider_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[1]->line, NULL, &s->sl[1]->line_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[1]->slider_but,
		NULL, &s->sl[1]->slider_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[2]->line, NULL, &s->sl[2]->line_rect);
	SDL_RenderCopy(s->rr.rend[2], s->sl[2]->slider_but,
		NULL, &s->sl[2]->slider_rect);
}

void	slider_click_event(SDL_Keycode key, t_view *s, SDL_Event e)
{
	if (key == 1 && s->flag == 0)
	{
		if (is_in_rect(s->sl[0]->line_rect, e)
			&& s->sl[0]->slider_rect.x <= 255)
		{
			s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
			s->sl[0]->slider_rect.x = e.button.x;
			redraw(s);
		}
		else if (is_in_rect(s->sl[1]->line_rect, e)
			&& s->sl[1]->slider_rect.x <= 255)
		{
			s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
			s->sl[1]->slider_rect.x = e.button.x;
			redraw(s);
		}
		else if (is_in_rect(s->sl[2]->line_rect, e)
			&& s->sl[2]->slider_rect.x <= 255)
		{
			s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
			s->sl[2]->slider_rect.x = e.button.x;
			redraw(s);
		}
	}
}

void	slider_motion_event(SDL_Keycode key, t_view *s, SDL_Event e)
{
	if (key == 1 && s->flag == 0)
	{
		if (is_in_rect(s->sl[0]->line_rect, e)
			&& s->sl[0]->slider_rect.x <= 255)
		{
			s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
			s->sl[0]->slider_rect.x = e.button.x;
			redraw(s);
		}
		else if (is_in_rect(s->sl[1]->line_rect, e)
			&& s->sl[1]->slider_rect.x <= 255)
		{
			s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
			s->sl[1]->slider_rect.x = e.button.x;
			redraw(s);
		}
		else if (is_in_rect(s->sl[2]->line_rect, e)
			&& s->sl[2]->slider_rect.x <= 255)
		{
			s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
			s->sl[2]->slider_rect.x = e.button.x;
			redraw(s);
		}
	}
}
