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

void	object_init(t_view *s)
{
	int			i;
	int			y;
	int			num;
	t_figure	*fig;
	TTF_Font	*font;

	if (!(font = TTF_OpenFont("Roboto-Regular.ttf", 32)))
		sdl_ttf_err();
	fig = s->space->figures;
	num = s->figures_num;
	i = 0;
	y = 100;
	s->l_obj.obj_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * num);
	s->l_obj.obj_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * num);
	while (fig)
	{
		s->l_obj.obj_rect[i] = make_rect(10, y,
			text_width(font, figure_type(fig->type)), 32);
		s->l_obj.obj_tex[i] = create_text(s, figure_type(fig->type), 1, 32);
		++i;
		y += 32;
		fig = fig->next;
	}
	TTF_CloseFont(font);
}

void	obj_highlight(t_view *s, SDL_Event e, SDL_Rect *rect)
{
	int			id;
	int			num;

	id = -1;
	num = s->figures_num;
	SDL_RenderClear(s->rr.rend[1]);
	while (++id < num && s->flag == 0)
	{
		if (is_in_rect(rect[id], e))
			SDL_SetRenderDrawColor(s->rr.rend[1], 255, 255, 255, 255);
		SDL_RenderFillRect(s->rr.rend[1], &s->l_obj.obj_rect[id]);
		SDL_RenderDrawRect(s->rr.rend[1], &s->l_obj.obj_rect[id]);
		SDL_RenderCopy(s->rr.rend[1], s->l_obj.obj_tex[id],
			NULL, &s->l_obj.obj_rect[id]);
		SDL_SetRenderDrawColor(s->rr.rend[1], 10, 20, 40, 255);
	}
	draw_select_button(s);
	SDL_RenderPresent(s->rr.rend[1]);
}

int		select_figure(SDL_Rect *rect, SDL_Event e, int num)
{
	int			id;

	id = -1;
	if (rect != NULL && num != -1)
	{
		while (++id < num)
		{
			if (is_in_rect(rect[id], e))
			{
				if (e.button.button == SDL_BUTTON_LEFT)
					return (id);
			}
		}
	}
	return (-1);
}

void	clean_list_obj(t_view *s)
{
	int			num;
	int			i;

	i = 0;
	num = s->figures_num;
	while (i < num)
	{
		if (s->l_obj.obj_tex[i] != NULL)
		{
			SDL_DestroyTexture(s->l_obj.obj_tex[i]);
			s->l_obj.obj_tex[i] = NULL;
		}
		i++;
	}
	free(s->l_obj.obj_tex);
	free(s->l_obj.obj_rect);
}
