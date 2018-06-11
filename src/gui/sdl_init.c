/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvinogra <vvinogra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 13:37:15 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/09 19:39:45 by vvinogra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_sdl(t_view *s)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0 || TTF_Init() < 0)
		sdl_init_err();
	if (IMG_Init(IMG_INIT_PNG) < 0)
		sdl_img_err();
	s->win[0] = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	s->win[1] = SDL_CreateWindow("Object_list", 470, SDL_WINDOWPOS_CENTERED,
		300, 1000, SDL_WINDOW_OPENGL);
	s->win[2] = SDL_CreateWindow("Properties", 1790, SDL_WINDOWPOS_CENTERED,
		270, 1000, SDL_WINDOW_OPENGL);
	s->win[3] = SDL_CreateWindow("Options-Line", SDL_WINDOWPOS_CENTERED, 100,
		1000, 200, SDL_WINDOW_OPENGL);
	if (!(s->rr.logo = IMG_Load("img/rt_logo.png")))
		sdl_img_err();
	SDL_SetWindowIcon(s->win[1], s->rr.logo);
	s->win_surface = SDL_GetWindowSurface(s->win[0]);
	s->buff = s->win_surface->pixels;
	s->exit_loop = 1;
	s->flag = 0;
	s->rr.select_flag = 0;
	s->rr.fl = (t_num){0, -1, 0, -1, -1, -1};
}

static void	eventess(t_view *s)
{
	SDL_HideWindow(s->win[1]);
	SDL_HideWindow(s->win[2]);
	SDL_HideWindow(s->win[3]);
	if (s->server_client == Server)
		SDL_HideWindow(s->win[0]);
}

int			poll_event(t_view *s)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
			e.key.keysym.sym == SDLK_ESCAPE))
				s->exit_loop = 0;
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			slider_click_event(e.button.button, s, e);
			mouse_key_down(s, e);
		}
		else if (e.type == SDL_MOUSEMOTION && e.window.windowID == 3)
			slider_motion_event(e.button.button, s, e);
		else if (e.window.windowID == 2)
			s->flag == 0 ? obj_highlight(s, e, s->l_obj.obj_rect) :
			light_list_highlight(s, e, s->l_light.light_rect);
		else if (e.type == SDL_KEYDOWN)
		{
			camera_move(s, e.key.keysym.scancode);
			camera_rot(s, e.key.keysym.scancode);
			if (s->server_client == Client)
				client_send_get_info(s);
		}
	}
	if (s->server_client != Normal)
		eventess(s);
	scroll_down(s, e);
	return (1);
}
