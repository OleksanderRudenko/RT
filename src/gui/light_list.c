/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 18:13:29 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/04 18:13:31 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	select_init(t_view *s)
{
	s->select.sel_tex_on = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 2);
	s->select.sel_tex_off = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 2);
	s->select.sel_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * 2);
	s->select.s_flag = (int *)malloc(sizeof(int) * 2);
	s->select.sel_tex_on[0] = get_tex("img/obj_on.bmp", s->rr.rend[1]);
	s->select.sel_tex_off[0] = get_tex("img/obj_off.bmp", s->rr.rend[1]);
	s->select.sel_tex_on[1] = get_tex("img/light_on.bmp", s->rr.rend[1]);
	s->select.sel_tex_off[1] = get_tex("img/light_off.bmp", s->rr.rend[1]);
	s->select.sel_rect[0] = make_rect(50, 0, 100, 50);
	s->select.sel_rect[1] = make_rect(150, 0, 100, 50);
	s->select.s_flag[0] = 0;
	s->select.s_flag[1] = 1;
}


void	draw_select_button(t_view *s)
{
	int	id;

	id = -1;
	while (++id < 2)
	{
		if (s->select.s_flag[id] == 1)
			SDL_RenderCopy(s->rr.rend[1], s->select.sel_tex_on[id], NULL, &s->select.sel_rect[id]);
		else 
			SDL_RenderCopy(s->rr.rend[1], s->select.sel_tex_off[id], NULL, &s->select.sel_rect[id]);
	}
}

void			light_list_highlight(t_view *s, SDL_Event e, SDL_Rect *rect)
{
	int			id;
	int			num;

	id = -1;
	num = s->lights_num;
	SDL_RenderClear(s->rr.rend[1]);
	while (++id < num && s->flag == 1)
	{
		if (is_in_rect(rect[id], e))
			SDL_SetRenderDrawColor(s->rr.rend[1], 255, 255, 255, 255);
		SDL_RenderFillRect(s->rr.rend[1], &s->l_light.light_rect[id]);
		SDL_RenderDrawRect(s->rr.rend[1], &s->l_light.light_rect[id]);
		SDL_RenderCopy(s->rr.rend[1], s->l_light.light_tex[id], NULL, &s->l_light.light_rect[id]);
		SDL_SetRenderDrawColor(s->rr.rend[1], 10, 20, 40, 255);
	}
	draw_select_button(s);
	SDL_RenderPresent(s->rr.rend[1]);
}

void			light_list_init(t_view *s)
{
	int			i;
	int			y;
	int			num;
	t_light		*light;
	TTF_Font	*font;

	if (!(font = TTF_OpenFont("Roboto-Black.ttf", 32)))
		sdl_ttf_err();
	light = s->space->lights;
	num = s->lights_num;
	i = 0;
	y = 50;
	s->l_light.light_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * num);
	s->l_light.light_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * num);
	while (light)
	{
		s->l_light.light_rect[i] = make_rect(10, y, text_width(font, light_type(light->type)), 32);
		s->l_light.light_tex[i] = create_text(s, light_type(light->type), 1, 32);
		++i;
		y+=32;
		light = light->next;
	}
	TTF_CloseFont(font);
}

void	clean_light(t_view *s)
{
	int		num;
	int		i;

	i = 0;
	num = s->lights_num;
	while (i < num)
	{
		SDL_DestroyTexture(s->l_light.light_tex[i]);
		s->l_light.light_tex[i] = NULL;
		i++;
	}
}

