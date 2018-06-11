/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 19:17:58 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/06 19:18:00 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*light_type(char num)
{
	if (num == 0)
		return ("AMBIENT");
	else if (num == 1)
		return ("POINT");
	return ("DIRECTIONAL");
}

void		screenshot(t_view *s)
{
	const char	*file;
	const char	*format[1] = { "*.bmp" };
	SDL_Surface *screen;

	file = tinyfd_saveFileDialog("", "file.bmp", 1, format, NULL);
	if (file == NULL)
		return ;
	SDL_LockSurface(s->win_surface);
	screen = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
	ft_memcpy(screen->pixels,
		s->win_surface->pixels, screen->h * screen->pitch);
	SDL_SaveBMP(screen, file);
	SDL_UnlockSurface(s->win_surface);
	SDL_FreeSurface(screen);
}

void		redraw(t_view *s)
{
	s->space->cl_figures[s->rr.fl.y].color =
	color_unite(s->sl[0]->clr.red, s->sl[1]->clr.green, s->sl[2]->clr.blue);
	ft_bzero(s->win_surface->pixels, HEIGHT * WIDTH * 4);
	opencl_init2(s);
}

void		scroll_down(t_view *s, SDL_Event e)
{
	size_t	i;

	i = 0;
	if (s->l_obj.obj_rect)
	{
		if (e.wheel.y < 0 && e.type == SDL_MOUSEWHEEL)
		{
			while (i < s->figures_num)
			{
				s->l_obj.obj_rect[i].y -= 5;
				i++;
			}
		}
		else if (e.wheel.y > 0 && e.type == SDL_MOUSEWHEEL
			&& s->l_obj.obj_rect[0].y < 900)
		{
			while (i < s->figures_num)
			{
				s->l_obj.obj_rect[i].y += 5;
				i++;
			}
		}
	}
}

SDL_Rect	make_rect(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}
