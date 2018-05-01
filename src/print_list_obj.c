/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list_obj.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 12:18:15 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/01 12:18:17 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Rect	make_rect(int x, int y, int w, int h)
{
	SDL_Rect rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

int		text_width(TTF_Font *f, char *str)
{
	/*function which estimates a rect width for a text*/
	char		*buf;
	int			width;
	int			len;

	len = ft_strlen(str);
	if (len > MAX_TEXT_LEN)
		len = 99;
	buf = ft_strnew(MAX_TEXT_LEN);
	ft_strncpy(buf, str, len);
	TTF_SizeUTF8(f, buf, &width, NULL);
	free(buf);
	return(width);
}

void			object_init(t_view *s)
{
	int			i;
	int			y;
	int			num;
	t_figure	*fig;
	TTF_Font	*font;

	if (!(font = TTF_OpenFont("Roboto-Black.ttf", 32)))
		sdl_ttf_err();
	fig = s->space->figures;
	num = num_figures(s);
	i = 0;
	y = 0;
	s->l_obj.obj_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * num);
	s->l_obj.obj_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * num);
	while (fig)
	{
		s->l_obj.obj_rect[i] = make_rect(10, y, text_width(font,figure_type(fig->type)), 32);
		s->l_obj.obj_tex[i] = create_text(s, figure_type(fig->type), 1);
		++i;
		y+=32;
		fig = fig->next;
	}
}

void	button_highlight(t_view *s, SDL_Event e, SDL_Rect *rect)
{
	int			x;
	int			y;
	int			id;
	int			num;

	id = -1;
	num = num_figures(s);
	SDL_RenderClear(s->rr.rend[1]);
	while (++id < num)
	{
		x = e.button.x;
		y = e.button.y;
		if (x >= rect[id].x && x <= (rect[id].x + rect[id].w) &&
			y >= rect[id].y && y <= (rect[id].y + rect[id].h))
				SDL_SetRenderDrawColor(s->rr.rend[1], 255, 255, 255, 255);
		else
			SDL_SetRenderDrawColor(s->rr.rend[1], 0, 0, 0, 255);
		SDL_RenderFillRect(s->rr.rend[1], &s->l_obj.obj_rect[id]);
		SDL_RenderDrawRect(s->rr.rend[1], &s->l_obj.obj_rect[id]);
		SDL_RenderCopy(s->rr.rend[1], s->l_obj.obj_tex[id], NULL, &s->l_obj.obj_rect[id]);
		SDL_SetRenderDrawColor(s->rr.rend[1], 0, 0, 0, 255);
	}
	SDL_RenderPresent(s->rr.rend[1]);
}