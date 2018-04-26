/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abutok <abutok@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 01:11:00 by abutok            #+#    #+#             */
/*   Updated: 2018/04/14 15:50:41 by abutok           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	view_init(t_view *view,char *filename)
{
	space_init(filename, view);
	init_rect(&view->rr);
	set_things_up(view);
	do_rt(view);
}

int			exit_x(t_view *view)
{
	exit(1);
	view = NULL;
	return (0);
}

int			main(int argc, char **argv)
{
	t_view view;

	init_sdl(&view);
	if (argc != 2)
	{
		ft_putstr("usage: RT scene_filename\n");
		return (0);
	}
	view_init(&view, argv[1]);
	while (view.exit_loop == 1)
	{
		if (!poll_event(&view))
			view.exit_loop = 0;
		SDL_RenderClear(view.rr.rend[0]);
		button_staff(&view);
		SDL_RenderPresent(view.rr.rend[0]);
		SDL_UpdateWindowSurface(view.win[0]);
		// SDL_UpdateWindowSurface(view.win[2]);
	}
	return (0);
}
