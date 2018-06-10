/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arudenko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:20:23 by arudenko          #+#    #+#             */
/*   Updated: 2018/06/10 14:20:25 by arudenko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	camera_move(t_view *s, SDL_Scancode key)
{
	if (key == SDL_SCANCODE_W)
	{
		s->space->cam->o.y += 0.5;
	}
	else if (key == SDL_SCANCODE_S)
	{
		s->space->cam->o.y -= 0.5;
	}
	else if (key == SDL_SCANCODE_A)
	{
		s->space->cam->o.x -= 0.5;
	}
	else if (key == SDL_SCANCODE_D)
	{
		s->space->cam->o.x += 0.5;
	}
	else if (key == SDL_SCANCODE_Z)
	{
		s->space->cam->o.z -= 0.5;
	}
	else if (key == SDL_SCANCODE_C)
	{
		s->space->cam->o.z += 0.5;
	}
	redraw(s);
}

void	camera_rot(t_view *s, SDL_Scancode key)
{
	if (key == SDL_SCANCODE_KP_8)
	{
		s->space->cam->v.x += 0.5;
	}
	else if (key == SDL_SCANCODE_KP_2)
	{
		s->space->cam->v.x -= 0.5;
	}
	else if (key == SDL_SCANCODE_KP_4)
	{
		s->space->cam->v.y -= 0.5;
	}
	else if (key == SDL_SCANCODE_KP_6)
	{
		s->space->cam->v.y += 0.5;
	}
	else if (key == SDL_SCANCODE_KP_7)
	{
		s->space->cam->v.z += 0.5;
	}
	else if (key == SDL_SCANCODE_KP_3)
	{
		s->space->cam->v.z -= 0.5;
	}
	redraw(s);
}
