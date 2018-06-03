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
	s->win[0] = SDL_CreateWindow("RT", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	s->win[1] = SDL_CreateWindow("Object_list", 350, SDL_WINDOWPOS_CENTERED,
		300, 1000, SDL_WINDOW_OPENGL);
	s->win[2] = SDL_CreateWindow("Properties", 1920, SDL_WINDOWPOS_CENTERED,
		300, 1000, SDL_WINDOW_OPENGL);
	s->win[3] = SDL_CreateWindow("Options-Line", SDL_WINDOWPOS_CENTERED, 100,
		1000, 200, SDL_WINDOW_OPENGL);
	s->win_surface = SDL_GetWindowSurface(s->win[0]);
	s->buff = s->win_surface->pixels;
	s->exit_loop = 1;
	s->flag = 0;
	s->rr.select_flag = 0;
	s->rr.fl = (t_num){0, -1, 0, -1, -1, -1};
}

int		poll_event(t_view *s)
{
	SDL_Event e;

	while (SDL_PollEvent(&e))
		if (e.type == SDL_QUIT || (e.type == SDL_KEYDOWN &&
			e.key.keysym.sym == SDLK_ESCAPE))
				s->exit_loop = 0;
		else if (e.type == SDL_MOUSEBUTTONDOWN)
		{
			slider_click_event(e.button.button, s, e);
			select_button_up(s, e, 2);
			mouse_key_down(s, e);
		}
		else if (e.type == SDL_MOUSEMOTION && e.window.windowID == 3)
			slider_motion_event(e.button.button, s, e);
		else if (e.type == SDL_MOUSEBUTTONUP && e.window.windowID == 4)
			mouse_key_up(s);
		else if (e.window.windowID == 2)
			s->flag == 0 ? obj_highlight(s, e, s->l_obj.obj_rect) :
			light_list_highlight(s, e, s->l_light.light_rect);
		else if (e.type == SDL_KEYDOWN)
		{
			camera_move(s, e.key.keysym.scancode);
			camera_rot(s, e.key.keysym.scancode);
		}
	return (1);
}

void	camera_move(t_view *s, SDL_Scancode key)
{
	if (key ==  SDL_SCANCODE_W)
	{
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		s->space->cam->o.x += 0.5;
		opencl_init2(s);
	}
	if (key ==  SDL_SCANCODE_S)
	{
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		s->space->cam->o.x -= 0.5;
		opencl_init2(s);
	}
		if (key ==  SDL_SCANCODE_D)
	{
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		s->space->cam->o.y += 0.5;
		opencl_init2(s);
	}
	if (key ==  SDL_SCANCODE_A)
	{
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		s->space->cam->o.y -= 0.5;
		opencl_init2(s);
	}
}

void	camera_rot(t_view *s, SDL_Scancode key)
{
		if (key ==  SDL_SCANCODE_UP)
	{
		ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
		s->space->cam->v.x += 0.5;
		do_rt(s);
	}
	// if (key ==  SDL_SCANCODE_S)
	// {
	// 	ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
	// 	s->space->cam->v.x -= 0.5;
	// 	do_rt(s);
	// }
	// 	if (key ==  SDL_SCANCODE_D)
	// {
	// 	ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
	// 	s->space->cam->v.y += 0.5;
	// 	do_rt(s);
	// }
	// if (key ==  SDL_SCANCODE_A)
	// {
	// 	ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
	// 	s->space->cam->v.y -= 0.5;
	// 	do_rt(s);
	// }
}
