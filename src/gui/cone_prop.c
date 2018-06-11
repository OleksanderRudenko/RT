/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_prop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:25:06 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/21 14:25:07 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static inline void	cone_prop2(t_view *s)
{
	s->con.cn_prop[4] = NULL;
	s->con.cn_rect[5] = make_rect(80, 450, 100, 32);
	s->con.cn_tex[5] = create_text(s, "Rotate-Y", 2, 32);
	s->con.cn_pr_rect[5] = make_rect(120, 450, 60, 32);
	s->con.cn_prop[5] = NULL;
	s->con.cn_rect[6] = make_rect(80, 500, 100, 32);
	s->con.cn_tex[6] = create_text(s, "Rotate-Z", 2, 32);
	s->con.cn_pr_rect[6] = make_rect(120, 500, 60, 32);
	s->con.cn_prop[6] = NULL;
	s->con.cn_rect[7] = make_rect(10, 550, 60, 32);
	s->con.cn_tex[7] = create_text(s, "Radius", 2, 32);
	s->con.cn_pr_rect[7] = make_rect(120, 550, 60, 32);
	s->con.cn_prop[7] = tf(s, 0, 2, 32);
	s->con.cn_rect[8] = make_rect(10, 600, 60, 32);
	s->con.cn_tex[8] = create_text(s, "Mirror", 2, 32);
	s->con.cn_pr_rect[8] = make_rect(120, 600, 60, 32);
	s->con.cn_prop[8] = tf(s, 0, 2, 32);
	s->con.cn_rect[9] = make_rect(10, 650, 90, 32);
	s->con.cn_tex[9] = create_text(s, "Texture-id", 2, 32);
	s->con.cn_pr_rect[9] = make_rect(120, 650, 60, 32);
	s->con.cn_prop[9] = tf(s, 0, 2, 32);
	s->con.cn_rect[10] = make_rect(10, 700, 90, 32);
	s->con.cn_tex[10] = create_text(s, "Refraction", 2, 32);
	s->con.cn_pr_rect[10] = make_rect(120, 700, 60, 32);
	s->con.cn_prop[10] = tf(s, 0, 2, 32);
}

void				cone_prop(t_view *s)
{
	s->con.cn_tex = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_CN_PR);
	s->con.cn_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_CN_PR);
	s->con.cn_pr_rect = (SDL_Rect *)malloc(sizeof(SDL_Rect) * NUM_CN_PR);
	s->con.cn_prop = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * NUM_CN_PR);
	s->con.cn_rect[0] = make_rect(10, 200, ft_strlen("Vertex-X") * 10, 32);
	s->con.cn_tex[0] = create_text(s, "Vertex-X", 2, 32);
	s->con.cn_pr_rect[0] = make_rect(120, 200, 60, 32);
	s->con.cn_prop[0] = tf(s, 0, 2, 32);
	s->con.cn_rect[1] = make_rect(10, 250, ft_strlen("Vertex-Y") * 10, 32);
	s->con.cn_tex[1] = create_text(s, "Vertex-Y", 2, 32);
	s->con.cn_pr_rect[1] = make_rect(120, 250, 60, 32);
	s->con.cn_prop[1] = tf(s, 0, 2, 32);
	s->con.cn_rect[2] = make_rect(10, 300, ft_strlen("Vertex-Z") * 10, 32);
	s->con.cn_tex[2] = create_text(s, "Vertex-Z", 2, 32);
	s->con.cn_pr_rect[2] = make_rect(120, 300, 60, 32);
	s->con.cn_prop[2] = tf(s, 0, 2, 32);
	s->con.cn_rect[3] = make_rect(10, 350, ft_strlen("Reflection") * 10, 32);
	s->con.cn_tex[3] = create_text(s, "Reflection", 2, 32);
	s->con.cn_pr_rect[3] = make_rect(120, 350, 60, 32);
	s->con.cn_prop[3] = tf(s, 0, 2, 32);
	s->con.cn_rect[4] = make_rect(80, 400, 100, 32);
	s->con.cn_tex[4] = create_text(s, "Rotate-X", 2, 32);
	s->con.cn_pr_rect[4] = make_rect(120, 400, 60, 32);
	cone_prop2(s);
}

void				init_cone_prop(t_view *s)
{
	t_col	c;

	c = col_parse(s->space->cl_figures[s->rr.fl.y].color);
	s->sl[0]->slider_rect.x = c.red;
	s->sl[0]->clr.red = s->sl[0]->slider_rect.x;
	s->sl[1]->slider_rect.x = c.green;
	s->sl[1]->clr.green = s->sl[1]->slider_rect.x;
	s->sl[2]->slider_rect.x = c.blue;
	s->sl[2]->clr.blue = s->sl[2]->slider_rect.x;
	s->con.cn_prop[0] = tf(s,
		s->space->cl_figures[s->rr.fl.y].vertex.x, 2, 32);
	s->con.cn_prop[1] = tf(s,
		s->space->cl_figures[s->rr.fl.y].vertex.y, 2, 32);
	s->con.cn_prop[2] = tf(s,
		s->space->cl_figures[s->rr.fl.y].vertex.z, 2, 32);
	s->con.cn_prop[3] = tf(s,
		s->space->cl_figures[s->rr.fl.y].reflection, 2, 32);
	s->con.cn_prop[4] = NULL;
	s->con.cn_prop[5] = NULL;
	s->con.cn_prop[6] = NULL;
	s->con.cn_prop[7] = tf(s, s->space->cl_figures[s->rr.fl.y].radius, 2, 32);
	s->con.cn_prop[8] = tf(s, s->space->cl_figures[s->rr.fl.y].mirror, 2, 32);
	s->con.cn_prop[9] = tf(s, s->space->cl_figures[s->rr.fl.y].texture, 2, 32);
	s->con.cn_prop[10] = tf(s, s->space->cl_figures[s->rr.fl.y].refract, 2, 32);
}

void				print_cone_prop(t_view *s)
{
	int i;

	i = -1;
	SDL_RenderClear(s->rr.rend[2]);
	while (++i < NUM_CN_PR && s->flag == 0)
	{
		SDL_RenderCopy(s->rr.rend[2], s->con.cn_tex[i],
			NULL, &s->con.cn_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->con.cn_prop[i],
			NULL, &s->con.cn_pr_rect[i]);
		SDL_RenderCopy(s->rr.rend[2], s->ok->b_ok, NULL, &s->ok->ok_rect);
		display_colored_rect(s);
	}
	SDL_SetRenderDrawColor(s->rr.rend[2], 10, 20, 40, 255);
	SDL_RenderPresent(s->rr.rend[2]);
}

void				clean_cone_prop(t_view *s)
{
	int	i;

	i = -1;
	while (++i < NUM_CN_PR)
	{
		if (s->con.cn_tex[i])
		{
			SDL_DestroyTexture(s->con.cn_tex[i]);
			s->con.cn_tex[i] = NULL;
		}
		if (s->con.cn_prop[i])
		{
			SDL_DestroyTexture(s->con.cn_prop[i]);
			s->con.cn_prop[i] = NULL;
		}
	}
}
