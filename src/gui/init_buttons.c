/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_buttons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:16:47 by arudenko          #+#    #+#             */
/*   Updated: 2018/04/26 14:16:49 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_rect(t_gui *r)
{
	r->but_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_BUTTONS);
	r->but_rect[0] = make_rect(5, 5, 60, 60);
	r->but_rect[1] = make_rect(90, 5, 60, 60);
	r->but_rect[2] = make_rect(175, 5, 60, 60);
	r->but_rect[3] = make_rect(250, 5, 60, 60);
	r->but_rect[4] = make_rect(325, 5, 60, 60);
	r->but_rect[5] = make_rect(410, 5, 60, 60);
	r->but_rect[10] = make_rect(495, 5, 60, 60);
	r->but_rect[11] = make_rect(580, 5, 60, 60);
	r->but_rect[12] = make_rect(665, 5, 60, 60);
	r->but_rect[7] = make_rect(0, 85, 60, 60);
	r->but_rect[8] = make_rect(75, 85, 60, 60);
	r->but_rect[9] = make_rect(150, 85, 60, 60);
	r->but_rect[13] = make_rect(580, 85, 60, 60);
	r->but_rect[6] = make_rect(665, 85, 60, 60);
}

void	init_buttons(t_view *s)
{
	s->rr.but_on[0] = get_tex("img/plane.png", s->rr.rend[0]);
	s->rr.but_on[1] = get_tex("img/sphere.png", s->rr.rend[0]);
	s->rr.but_on[2] = get_tex("img/cylin.png", s->rr.rend[0]);
	s->rr.but_on[3] = get_tex("img/cone.png", s->rr.rend[0]);
	s->rr.but_on[4] = get_tex("img/elips.png", s->rr.rend[0]);
	s->rr.but_on[5] = get_tex("img/parab.png", s->rr.rend[0]);
	s->rr.but_on[6] = get_tex("img/fold.png", s->rr.rend[0]);
	s->rr.but_on[7] = get_tex("img/amb.png", s->rr.rend[0]);
	s->rr.but_on[8] = get_tex("img/point.png", s->rr.rend[0]);
	s->rr.but_on[9] = get_tex("img/dir.png", s->rr.rend[0]);
	s->rr.but_on[10] = get_tex("img/cube.png", s->rr.rend[0]);
	s->rr.but_on[11] = get_tex("img/square.png", s->rr.rend[0]);
	s->rr.but_on[12] = get_tex("img/tri.png", s->rr.rend[0]);
	s->rr.but_on[13] = get_tex("img/screen.png", s->rr.rend[0]);
}

void	set_things_up(t_view *s)
{
	int i;

	i = -1;
	s->rr.but_on = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * NUM_BUTTONS);
	s->rr.rend[0] = SDL_CreateRenderer(s->win[3],
		-1, SDL_RENDERER_ACCELERATED);
	s->rr.rend[1] = SDL_CreateRenderer(s->win[1],
		-1, SDL_RENDERER_ACCELERATED);
	s->rr.rend[2] = SDL_CreateRenderer(s->win[2],
		-1, SDL_RENDERER_ACCELERATED);
	init_buttons(s);
}

void	button_staff(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[0]);
	while (i < NUM_BUTTONS)
	{
		SDL_RenderCopy(s->rr.rend[0], s->rr.but_on[i],
			NULL, &s->rr.but_rect[i]);
		i++;
	}
	SDL_SetRenderDrawColor(s->rr.rend[0], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[0]);
}

void	clean_buttons(t_view *s)
{
	int		i;

	i = -1;
	while (++i < NUM_BUTTONS)
	{
		SDL_DestroyTexture(s->rr.but_on[i]);
		s->rr.but_on[i] = NULL;
	}
}
