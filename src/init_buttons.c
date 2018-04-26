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

char	*name_of_file(char *str, int num)
{
	char *buf;
	char *tmp;

	buf = ft_strnew(50);

	ft_strcpy(buf, str);
	tmp = (ft_itoa(num));
	ft_strcat(buf, tmp);
	ft_strcat(buf, ".bmp");
	ft_strdel(&tmp);
	return (buf);
}

void	init_rect(t_gui *r)
{
	r->button = (SDL_Rect *)malloc(sizeof(SDL_Rect) * 3);

	r->button[0].x = 50;
	r->button[0].y = 50;
	r->button[0].w = 50;
	r->button[0].h = 50;

	
	r->button[1].x = 105;
	r->button[1].y = 50;
	r->button[1].w = 50;
	r->button[1].h = 50;


	r->button[2].x = 160;
	r->button[2].y = 50;
	r->button[2].w = 50;
	r->button[2].h = 50;
}

void	set_things_up(t_view *s)
{
	int i;
	char *str;
	char *str2;

	i = -1;
	s->rr.but_on = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 3);
	s->rr.but_off = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 3);
	s->rr.flag = (Uint32 *)malloc(sizeof(Uint32) * 6);
	s->rr.rend = SDL_CreateRenderer(s->win[3], -1, SDL_RENDERER_ACCELERATED);
	while (++i < 3)
	{
		s->rr.flag[i] = 1;
		str = name_of_file("img/button_on", i);
		str2 = name_of_file("img/button_off", i);
		s->rr.but_on[i] = get_tex(str, s->rr.rend);
		s->rr.but_off[i] = get_tex(str2, s->rr.rend);
		free(str);
	}
}


void	button_staff(t_view *s)
{
	int i;

	i = 0;
	while (i < 3)
	{
		if (s->rr.flag[i] == 1)
			SDL_RenderCopy(s->rr.rend, s->rr.but_on[i],NULL, &s->rr.button[i]);
		else
			SDL_RenderCopy(s->rr.rend, s->rr.but_off[i],NULL, &s->rr.button[i]);
		i++;
	}
}
