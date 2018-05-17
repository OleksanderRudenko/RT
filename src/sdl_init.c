/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:37:15 by arudenko          #+#    #+#             */
/*   Updated: 2018/04/26 13:37:17 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_sdl(t_view *s)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		sdl_init_err();
	if (TTF_Init() < 0)
		sdl_ttf_err();
	s->win[0] = SDL_CreateWindow("RTv1", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);

	s->win[1] = SDL_CreateWindow("Object_list", 550, SDL_WINDOWPOS_CENTERED, 200, 1000, SDL_WINDOW_OPENGL);
	s->win[2] = SDL_CreateWindow("Properties", 1800, SDL_WINDOWPOS_CENTERED, 150, 1000, SDL_WINDOW_OPENGL);
	s->win[3] = SDL_CreateWindow("Options-Line", SDL_WINDOWPOS_CENTERED, 0, 1000, 200, SDL_WINDOW_OPENGL);
	s->win_surface[0] = SDL_GetWindowSurface(s->win[0]);
	s->win_surface[2] = SDL_GetWindowSurface(s->win[2]);
	s->buff = s->win_surface[0]->pixels;
	s->exit_loop = 1;
}

int		poll_event(t_view *s)
{
	SDL_Event e;
	
	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
			e.key.keysym.sym == SDLK_ESCAPE))
				s->exit_loop = 0;
		/*Just example: we do not redraw if dont needed*/
		/*Can be rotation here or whatever*/
		// else if (e.type == SDL_KEYDOWN)
		// {
		// 	key_down(e.key.keysym.scancode, s);
		// }
		else if (e.type == SDL_MOUSEBUTTONDOWN && e.window.windowID == 4)
		{
				button_off_on(s->rr.button, e, s);
		}
	return (1);
}