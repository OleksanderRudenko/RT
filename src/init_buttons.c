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

SDL_Texture *get_tex(char *file, SDL_Renderer *ren_tar)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = SDL_LoadBMP(file);
	if (surface == NULL)
	{
		ft_putendl(SDL_GetError());
		exit(0);
		/*Maybe need to clear everything, dunno*/
	}
	texture = SDL_CreateTextureFromSurface(ren_tar, surface);
	if (texture == NULL)
	{
		ft_putendl(SDL_GetError());
		exit(0);
		/*Maybe need to clear everything as well, dunno*/
	}
	SDL_FreeSurface(surface);
	return (texture);
}

void	init_rect(t_gui *r)
{
	r->but_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * 3);

	r->but_rect[0].x = 0;
	r->but_rect[0].y = 0;
	r->but_rect[0].w = 75;
	r->but_rect[0].h = 75;

	r->but_rect[1].x = 75;
	r->but_rect[1].y = 0;
	r->but_rect[1].w = 75;
	r->but_rect[1].h = 75;
}

void	init_buttons(t_view *s)
{
	s->rr.but_on[0] = get_tex("img/plane_on.bmp", s->rr.rend[0]);
	s->rr.but_off[0] = get_tex("img/plane_off.bmp", s->rr.rend[0]);
	s->rr.but_on[1] = get_tex("img/sphere_on.bmp", s->rr.rend[0]);
	s->rr.but_off[1] = get_tex("img/sphere_off.bmp", s->rr.rend[0]);
}

void	set_things_up(t_view *s)
{
	int i;

	i = -1;
	s->rr.but_on = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * NUM_BUTTONS);
	s->rr.but_off = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * NUM_BUTTONS);
	s->rr.flag = (Uint32 *)malloc(sizeof(Uint32) * NUM_BUTTONS * 2);
	s->rr.rend[0] = SDL_CreateRenderer(s->win[3], -1, SDL_RENDERER_ACCELERATED);/*options*/
	s->rr.rend[1] = SDL_CreateRenderer(s->win[1], -1, SDL_RENDERER_ACCELERATED);/*have to be list of figures*/
	s->rr.rend[2] = SDL_CreateRenderer(s->win[2], -1, SDL_RENDERER_ACCELERATED);/*have to be list of properties*/
	while (++i < NUM_BUTTONS * 2)
		s->rr.flag[i] = 1;
	init_buttons(s);
}

void	button_staff(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[0]);
	while (i < NUM_BUTTONS)
	{
		if (s->rr.flag[i] == 1)
			SDL_RenderCopy(s->rr.rend[0], s->rr.but_on[i],NULL, &s->rr.but_rect[i]);
		else
			SDL_RenderCopy(s->rr.rend[0], s->rr.but_off[i],NULL, &s->rr.but_rect[i]);
		i++;
	}
	SDL_RenderPresent(s->rr.rend[0]);
}
