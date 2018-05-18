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

void	clean_staff(t_view *s)
{
	SDL_FreeSurface(s->win_surface);
	clean_sphere_prop(s);
	clean_buttons(s);
	clean_list_obj(s);
	SDL_DestroyRenderer(s->rr.rend[0]);
	SDL_DestroyRenderer(s->rr.rend[1]);
	SDL_DestroyRenderer(s->rr.rend[2]);
	SDL_DestroyTexture(s->l_obj.def_tex);
	clean_light(s);
	TTF_Quit();
	SDL_Quit();
	// ft_putendl("cleaned");
	/*delete textures and so on*/
}