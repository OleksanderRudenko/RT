/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_direct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 14:05:21 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/30 14:05:24 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


void	light_dir_properties(t_view *s)
{
	s->dir.dir_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_DIR_PR);
	s->dir.dir_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_DIR_PR);
	s->dir.dir_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_DIR_PR);
	s->dir.dir_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_DIR_PR);
	s->dir.dir_rect[0] = make_rect(10, 0, 100, 32);
	s->dir.dir_tex[0] = create_text(s, "X-Origin", 2, 32);
	s->dir.dir_pr_rect[0] = make_rect(120, 0, 60, 32);
	s->dir.dir_prop[0] =  tf(s, 0, 2, 32);
	s->dir.dir_rect[1] = make_rect(10, 50, 100, 32);
	s->dir.dir_tex[1] = create_text(s, "Y-Origin", 2, 32);
	s->dir.dir_pr_rect[1] = make_rect(120, 50, 60, 32);
	s->dir.dir_prop[1] =  tf(s, 0, 2, 32);
	s->dir.dir_rect[2] = make_rect(10, 100, 100, 32);
	s->dir.dir_tex[2] = create_text(s, "Z-Origin", 2, 32);
	s->dir.dir_pr_rect[2] = make_rect(120, 100, 60, 32);
	s->dir.dir_prop[2] =  tf(s, 0, 2, 32);
	s->dir.dir_rect[3] = make_rect(10, 150, 100, 32);
	s->dir.dir_tex[3] = create_text(s, "X-Dir", 2, 32);
	s->dir.dir_pr_rect[3] = make_rect(120, 150, 60, 32);
	s->dir.dir_prop[3] =  tf(s, 0, 2, 32);
	s->dir.dir_rect[4] = make_rect(10, 200, 100, 32);
	s->dir.dir_tex[4] = create_text(s, "Y-Dir", 2, 32);
	s->dir.dir_pr_rect[4] = make_rect(120, 200, 60, 32);
	s->dir.dir_prop[4] =  tf(s, 0, 2, 32);
	s->dir.dir_rect[5] = make_rect(10, 250, 100, 32);
	s->dir.dir_tex[5] = create_text(s, "Z-Dir", 2, 32);
	s->dir.dir_pr_rect[5] = make_rect(120, 250, 60, 32);
	s->dir.dir_prop[5] =  tf(s, 0, 2, 32);
	s->dir.dir_rect[6] = make_rect(10, 300, 100, 32);
	s->dir.dir_tex[6] = create_text(s, "Inten", 2, 32);
	s->dir.dir_pr_rect[6] = make_rect(120, 300, 60, 32);
	s->dir.dir_prop[6] =  tf(s, 0, 2, 32);
}

void	init_dir_light_prop(t_view *s)
{
	s->dir.dir_prop[0] = tf(s, s->space->cl_lights[s->rr.fl.b].origin.x, 2, 32);
	s->dir.dir_prop[1] = tf(s, s->space->cl_lights[s->rr.fl.b].origin.y, 2, 32);
	s->dir.dir_prop[2] = tf(s, s->space->cl_lights[s->rr.fl.b].origin.z, 2, 32);
	s->dir.dir_prop[3] = tf(s, s->space->cl_lights[s->rr.fl.b].direction.x, 2, 32);
	s->dir.dir_prop[4] = tf(s, s->space->cl_lights[s->rr.fl.b].direction.y, 2, 32);
	s->dir.dir_prop[5] = tf(s, s->space->cl_lights[s->rr.fl.b].direction.z, 2, 32);
	s->dir.dir_prop[6] = tf(s, s->space->cl_lights[s->rr.fl.b].inten, 2, 32);
}

void	print_dir_light_prop(t_view *s)
{
	int i;

	i = 0;
	SDL_RenderClear(s->rr.rend[2]);
	while (i < NUM_DIR_PR && s->flag == 1)
	{
		SDL_RenderCopy(s->rr.rend[2], s->dir.dir_tex[i], NULL, &s->dir.dir_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->dir.dir_prop[i], NULL, &s->dir.dir_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		i++;
	}
	SDL_RenderPresent(s->rr.rend[2]);
}

void	clean_dir_light_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_DIR_PR)
	{
		if (s->dir.dir_tex[i])
		{
			SDL_DestroyTexture(s->dir.dir_tex[i]);
			s->dir.dir_tex[i] = NULL;
		}
		if (s->dir.dir_prop[i])
		{
			SDL_DestroyTexture(s->dir.dir_prop[i]);
			s->dir.dir_prop[i] = NULL;
		}
	}
}