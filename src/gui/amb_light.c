/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   amb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 13:47:17 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/30 13:47:20 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	light_am_properties(t_view *s)
{
	s->am.aml_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_AM_PR);
	s->am.aml_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_AM_PR);
	s->am.aml_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_AM_PR);
	s->am.aml_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_AM_PR);
	s->am.aml_rect[0] = make_rect(10, 10, 100, 32);
	s->am.aml_tex[0] = create_text(s, "Intensity", 2, 32);
	s->am.aml_pr_rect[0] = make_rect(120, 10, 60, 32);
	s->am.aml_prop[0] = tf(s, 0, 2, 32);
}

void	init_am_light_prop(t_view *s)
{
	s->am.aml_prop[0] = tf(s, s->space->cl_lights[s->rr.fl.b].inten, 2, 32);
}

void	print_am_light_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_AM_PR && s->flag == 1)
	{
		SDL_RenderCopy(s->rr.rend[2], s->am.aml_tex[i],
			NULL, &s->am.aml_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->am.aml_prop[i],
			NULL, &s->am.aml_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_am_light_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_AM_PR)
	{
		if (s->am.aml_tex[i])
		{
			SDL_DestroyTexture(s->am.aml_tex[i]);
			s->am.aml_tex[i] = NULL;
		}
		if (s->am.aml_prop[i])
		{
			SDL_DestroyTexture(s->am.aml_prop[i]);
			s->am.aml_prop[i] = NULL;
		}
	}
}
