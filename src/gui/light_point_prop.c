/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_prop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/23 13:15:16 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/23 13:15:24 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	light_properties(t_view *s)
{
	s->lp.li_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_LI_PR);
	s->lp.li_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_LI_PR);
	s->lp.li_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_LI_PR);
	s->lp.li_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_LI_PR);
	s->lp.li_rect[0] = make_rect(10, 0, 100, 32);
	s->lp.li_tex[0] = create_text(s, "X-Origin", 2, 32);
	s->lp.li_pr_rect[0] = make_rect(120, 0, 60, 32);
	s->lp.li_prop[0] = tf(s, 0, 2, 32);
	s->lp.li_rect[1] = make_rect(10, 50, 100, 32);
	s->lp.li_tex[1] = create_text(s, "Y-Origin", 2, 32);
	s->lp.li_pr_rect[1] = make_rect(120, 50, 60, 32);
	s->lp.li_prop[1] = tf(s, 0, 2, 32);
	s->lp.li_rect[2] = make_rect(10, 100, 100, 32);
	s->lp.li_tex[2] = create_text(s, "Z-Origin", 2, 32);
	s->lp.li_pr_rect[2] = make_rect(120, 100, 60, 32);
	s->lp.li_prop[2] = tf(s, 0, 2, 32);
	s->lp.li_rect[3] = make_rect(10, 150, 100, 32);
	s->lp.li_tex[3] = create_text(s, "Inten", 2, 32);
	s->lp.li_pr_rect[3] = make_rect(120, 150, 60, 32);
	s->lp.li_prop[3] = tf(s, 0, 2, 32);
}

void	init_light_prop(t_view *s)
{
	s->lp.li_prop[0] = tf(s, s->space->cl_lights[s->rr.fl.b].origin.x, 2, 32);
	s->lp.li_prop[1] = tf(s, s->space->cl_lights[s->rr.fl.b].origin.y, 2, 32);
	s->lp.li_prop[2] = tf(s, s->space->cl_lights[s->rr.fl.b].origin.z, 2, 32);
	s->lp.li_prop[3] = tf(s, s->space->cl_lights[s->rr.fl.b].inten, 2, 32);
}

void	print_light_prop(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[2]);
	while (i < NUM_LI_PR && s->flag == 1)
	{
		SDL_RenderCopy(s->rr.rend[2], s->lp.li_tex[i],
			NULL, &s->lp.li_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->lp.li_prop[i],
			NULL, &s->lp.li_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		i++;
	}
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_light_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_LI_PR)
	{
		if (s->lp.li_tex[i])
		{
			SDL_DestroyTexture(s->lp.li_tex[i]);
			s->lp.li_tex[i] = NULL;
		}
		if (s->lp.li_prop[i])
		{
			SDL_DestroyTexture(s->lp.li_prop[i]);
			s->lp.li_prop[i] = NULL;
		}
	}
}

int		select_li_num(t_view *s)
{
	int			type;

	type = s->space->cl_lights[s->rr.fl.b].type;
	if (type == LIGHT_TYPE_POINT)
		return (NUM_LI_PR);
	else if (type == LIGHT_TYPE_AMBIENT)
		return (NUM_AM_PR);
	else if (type == LIGHT_TYPE_DIRECT)
		return (NUM_DIR_PR);
	return (-1);
}
