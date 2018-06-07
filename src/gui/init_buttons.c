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

	r->but_rect[0] = make_rect(0, 0, 75, 75);
	r->but_rect[1] = make_rect(75, 0, 75, 75);
	r->but_rect[2] = make_rect(150, 0, 75, 75);
	r->but_rect[3] = make_rect(225, 0, 75, 75);
	r->but_rect[4] = make_rect(300, 0, 75, 75);
	r->but_rect[5] = make_rect(375, 0, 75, 75);
	r->but_rect[6] = make_rect(450, 0, 75, 75);
	r->but_rect[10] = make_rect(525, 0, 75, 75);
	r->but_rect[11] = make_rect(600, 0, 75, 75);
	r->but_rect[12] = make_rect(675, 0, 75, 75);
	/*New line*/
	r->but_rect[7] = make_rect(0, 85, 75, 75);
	r->but_rect[8] = make_rect(75, 85, 75, 75);
	r->but_rect[9] = make_rect(150, 85, 75, 75);
}

void	init_buttons(t_view *s)
{
	s->rr.but_on[0] = get_tex("img/plane_on.bmp", s->rr.rend[0]);
	s->rr.but_off[0] = get_tex("img/plane_off.bmp", s->rr.rend[0]);
	s->rr.but_on[1] = get_tex("img/sphere_on.bmp", s->rr.rend[0]);
	s->rr.but_off[1] = get_tex("img/sphere_off.bmp", s->rr.rend[0]);
	s->rr.but_on[2] = get_tex("img/cylinder_on.bmp", s->rr.rend[0]);
	s->rr.but_off[2] = get_tex("img/cylinder_off.bmp", s->rr.rend[0]);
	s->rr.but_on[3] = get_tex("img/cone_on.bmp", s->rr.rend[0]);
	s->rr.but_off[3] = get_tex("img/cone_off.bmp", s->rr.rend[0]);
	s->rr.but_on[4] = get_tex("img/elips_on.bmp", s->rr.rend[0]);
	s->rr.but_off[4] = get_tex("img/elips_off.bmp", s->rr.rend[0]);
	s->rr.but_on[5] = get_tex("img/parab_on.bmp", s->rr.rend[0]);
	s->rr.but_off[5] = get_tex("img/parab_off.bmp", s->rr.rend[0]);
	s->rr.but_on[6] = get_tex("img/fold.bmp", s->rr.rend[0]);
	s->rr.but_off[6] = get_tex("img/fold.bmp", s->rr.rend[0]);
	s->rr.but_on[7] = get_tex("img/amb_on.bmp", s->rr.rend[0]);
	s->rr.but_off[7] = get_tex("img/amb_off.bmp", s->rr.rend[0]);
	s->rr.but_on[8] = get_tex("img/point_on.bmp", s->rr.rend[0]);
	s->rr.but_off[8] = get_tex("img/point_off.bmp", s->rr.rend[0]);
	s->rr.but_on[9] = get_tex("img/dir_on.bmp", s->rr.rend[0]);
	s->rr.but_off[9] = get_tex("img/dir_off.bmp", s->rr.rend[0]);
	s->rr.but_on[10] = get_tex("img/cube_on.bmp", s->rr.rend[0]);
	s->rr.but_off[10] = get_tex("img/cube_off.bmp", s->rr.rend[0]);
	s->rr.but_on[11] = get_tex("img/quad_on.bmp", s->rr.rend[0]);
	s->rr.but_off[11] = get_tex("img/quad_off.bmp", s->rr.rend[0]);
	s->rr.but_on[12] = get_tex("img/tri_on.bmp", s->rr.rend[0]);
	s->rr.but_off[12] = get_tex("img/tri_off.bmp", s->rr.rend[0]);
}

void	set_things_up(t_view *s)
{
	int i;

	i = -1;
	s->rr.but_on = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * NUM_BUTTONS);
	s->rr.but_off = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * NUM_BUTTONS);
	s->rr.flag = (int *)malloc(sizeof(int) * NUM_BUTTONS * 2);
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
	SDL_SetRenderDrawColor(s->rr.rend[0], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[0]);
}

void	clean_buttons(t_view *s)
{
	int		i;

	i = 0;
	while (i < NUM_BUTTONS)
	{
		SDL_DestroyTexture(s->rr.but_on[i]);
		s->rr.but_on[i] = NULL;
		SDL_DestroyTexture(s->rr.but_off[i]);
		s->rr.but_off[i] = NULL;
		i++;
	}
}
