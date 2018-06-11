/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:40:27 by arudenko          #+#    #+#             */
/*   Updated: 2018/05/02 12:40:30 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static	void	clear_staff2(t_view *s)
{
	SDL_DestroyRenderer(s->rr.rend[0]);
	SDL_DestroyRenderer(s->rr.rend[1]);
	SDL_DestroyRenderer(s->rr.rend[2]);
	SDL_DestroyTexture(s->l_obj.def_tex);
	clean_light(s);
	SDL_DestroyTexture(s->select.sel_tex_on[0]);
	SDL_DestroyTexture(s->select.sel_tex_on[1]);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void			clean_staff(t_view *s)
{
	SDL_FreeSurface(s->win_surface);
	clean_buttons(s);
	clean_list_obj(s);
	clean_sphere_prop(s);
	clean_ic_prop(s);
	clean_plane_prop(s);
	clean_triangle_prop(s);
	clean_cone_prop(s);
	clean_cube_prop(s);
	clean_quadraate_prop(s);
	clean_elips_prop(s);
	clean_parab_prop(s);
	clean_light_prop(s);
	clean_am_light_prop(s);
	clean_dir_light_prop(s);
	clear_staff2(s);
}
