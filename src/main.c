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

void	view_init(t_view *view, const char *filename)
{
	space_init(filename, view);
	init_rect(&view->rr);
	set_things_up(view);
	object_init(view);
	init_slider(view);
	sphere_prop(view);
	ic_prop(view);
	plane_prop(view);
	triangle_prop(view);
	cone_prop(view);
	cube_prop(view);
	quadraate_prop(view);
	elips_prop(view);
	parab_prop(view);
	light_properties(view);
	light_am_properties(view);
	light_dir_properties(view);
	object_default_init(view);
	select_init(view);
	light_list_init(view);
	ok_button_init(view);
}


int			exit_x(t_view *view)
{
	exit(1);
	view = NULL;
	return (0);
}

int			main(int argc, char **argv)
{
	t_view	view;

	if (argc != 2)
	{
		ft_putstr("usage: RT scene_filename\n");
		return (0);
	}
	init_sdl(&view);
	view_init(&view, argv[1]);
	opencl_init(&view);
	while (view.exit_loop == 1)
	{
		if (!poll_event(&view))
			view.exit_loop = 0;
		button_staff(&view);
		what_to_print(&view);
		SDL_UpdateWindowSurface(view.win[0]);
	}
	cl_releasing(&view);
	clean_staff(&view); /*TODO: make it good w/o segfault*/
	system("leaks RT");

	/*destroy texture..., cleaning staff HERE*/
	return (0);
}
